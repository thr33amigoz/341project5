// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment 
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************

  // searches to see if the key already exists in the HashTable
  bool exist(int index, const string key){

    int indexInitial = index;
    int counter = 0;

    // iterate over the length of the HashTable, if necessary
    while (counter < int(_N)){

      // while we hit empty heaps
      while (_table[index].empty()){
	// count how many times we increment
	index++;
	counter++;
	
	// pass index in by reference, and possibly reset to 0 if needed,
        // or return false if the whole table has been searched
	if( indexReset(index, int(_N), indexInitial) == false ){
	  return false;
	}
	
      }
      
      // if the key for the bucket is not equal to the desired in key
      while (_table[index].size() > 0 && _table[index].readTop().key() != key ){
	// count how many times we increment
	index++;
	counter++;

	// pass index in by reference, and possibly reset to 0 if needed,
	// or return false if the whole table has been searched
	if( indexReset(index, int(_N), indexInitial) == false ){
	  return false;
	}
      }

      // if you hit a never before used HashTable bucket                   
      if (_table[index].empty() == true && _table[index].used() == false){
	return false;
      }
      
      // if a bucket with the key is found                                 
      if (_table[index].empty() == false &&
	  _table[index].readTop().key() == key){
	return true;
      }
    }
    return false;
  }
  
  // pass index in by reference, and possibly reset to 0 if needed,
  // or return false if the whole table has been searched
  bool indexReset(int &index, int maxSize, int indexInitial){
    // reset index if not found initially                              
    if (index == maxSize){
      index = 0;
      return true;
    }
    // if you get back to the initial index, the element was not found
    if (index == indexInitial){
      return false;
    }
    return true;
  }

  // increases _n if necessary
  void increaseEntries(int index){
    // if its a new block, increase the number of entries  
    if (_table[index].empty()){
      _n++;
    }
  }

  // decreases _n if necessary
  void decreaseEntries(int index){
    // if the block is now empty, decrease the number of entries
    if (_table[index].empty()){
      _n--;
    }
  }

  // increments index and counter until a valid bucket is found, and if one is not
  // return false
  bool indexIncrement(int &index, int &counter, const string key, const int indexInitial){
    // while the the index's buckets are empty & have been used               
    while ( _table[index].empty() && _table[index].used()
	    && exist(index, key) ){
      // count how many times we increment                                    
      index++;
      counter++;
      
      // pass index in by reference, and possibly reset to 0 if needed,       
      // or return false if the whole table has been searched                 
      if( indexReset(index, int(_N), indexInitial) == false ){
	return false;
      }
    }
    
    // while the keys dont match, move index up one
    while ( (_table[index].size() > 0
	     && _table[index].readTop().key() != key) ){
      // count how many times we increment                                    
      index++;
      counter++;
      
      // pass index in by reference, and possibly reset to 0 if needed,       
      // or return false if the whole table has been searched                 
      if( indexReset(index, int(_N), indexInitial) == false ){
	return false;
      }
    }
    return true;
  }
  
};

// *****************************************
// Templated function definitions go here! *
// *****************************************

template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash){
  _N = size;
  _n = 0;
  _hash = hash;
  _table = new Heap<T>[_N];
}

template <class T>
HashTable<T>::~HashTable(){
  delete[] _table;
  _table = nullptr;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht){
  _N = ht._N;
  _n = ht._n;
  _hash = ht._hash;
  _table = new Heap<T>[_N];

  // iterate over ht and assign the _table index to equal ht's _table index
  for(unsigned int i = 0; i < ht._N; i++){
    _table[i] = ht._table[i];
  }
}

template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht){
  // delete the _table of the HashTable "=" was called on
  delete[] this->_table;
  
  _N = ht._N;
  _n = ht._n;
  _hash = ht._hash;
  _table = new Heap<T>[_N];

  // iterate over ht and assign the _table index to equal ht's _table index
  for(unsigned int i = 0; i < ht._N; i++){
    _table[i] = ht._table[i];
  }
  
  return *this;
}

template <class T>
bool HashTable<T>::insert(const T& object){

  // insert at index based on hash function % table size
  int index = (_hash(object.key())) % _N;
  int indexInitial = index;
  int counter = 0;

  // if the Hash Table is not already full or the index already exists in the table
  if (lambda() < 1 || ( lambda() == 1 && exist(index, object.key()) )){
  
    // iterate over the length of the HashTable, if absolutely necessary
    while(counter < int(_N)) {

      // increment through the Hash Table if you haven't found a valid bucket to
      // insert into
      if (indexIncrement(index, counter, object.key(), indexInitial) ==  false){
	return false;
      }
      
      // if the bucket is empty, and has never been used, insert to bucket  
      if ( _table[index].empty() && _table[index].used() == false ){
        // increase _n if needed                                            
        increaseEntries(index);
        // insert object                                                    
        _table[index].insert(object);

        return true;
      }

      // if the index is empty, and its been used before                    
      // but the key is unique in the HashTable                             
      if ( _table[index].empty() && _table[index].used()
           && exist(index, object.key()) == false ){
        // increase _n if needed                                            
        increaseEntries(index);
        // insert object                                                    
        _table[ index ].insert(object);

        return true;
      }
      
      // if the corresponding bucket for the key is found, insert it  
      if (_table[index].size() > 0
	  && _table[index].readTop().key() == object.key()){
	// increase _n if needed                                      
	increaseEntries(index);
	// insert object                                              
	_table[ index ].insert(object);
	
	return true;
      }

    }
    return false;
  }
  
  return false;
}

template <class T>
bool HashTable<T>::getNext(string key, T& obj){
  // calculate and hold the initial index
  int index = _hash(key) % _N;
  int indexInitial = index;
  int counter = 0;

  // if the key doesnt exist in the HashTable, return false
  if (exist(index, key) == false){
    return false;
  }

  // iterate over the length of the HashTable, if absolutely necessary
  while(counter < int(_N)) {
    
    // increment through the Hash Table if you haven't found a valid index,
    // that the key could be at
    if (indexIncrement(index, counter, key, indexInitial) == false){
      return false;
    }
    
    // if the corresponding bucket for the key was found, delete it and return true
    if (_table[index].size() > 0 && _table[index].readTop().key() == key){
      // set the object equal to the highest priority element in the heap
      obj = _table[index].readTop();
      // remove the highest priority element  
      _table[index].removeTop();

      // decrease _n if necessary
      decreaseEntries(index);
      
      return true;
    }
  }
  return false;
}

template <class T>
void HashTable<T>::dump() const{
  // iterate over the HashTable and print out each index
  for(unsigned int i = 0; i < _N; i++){
    cout << "[" << i << "]:" << endl;
    _table[i].dump();
  }
}

#endif
