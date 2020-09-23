// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.
  
  // *********************************************
  // Private helper function declarations go here!
  // *********************************************

  // function to reheap down after deleting from the max-heap
  void reheapDown(int parent){

    // set the greatest element, left child, and right child
    int greatestEle = parent;
    int leftChild = 2*parent;
    int rightChild = 2*parent + 1;

    // if the left child (inside the bounds of the heap) is the greatest element
    if ( int(_heap.size()) > leftChild &&
	 _heap.at( leftChild ).priority() > _heap.at( greatestEle ).priority() ){
      greatestEle = leftChild;
    }
    // if the right child (inside the bounds of the heap) is the greatest element
    if ( int(_heap.size()) > rightChild &&
	 _heap.at( rightChild ).priority() > _heap.at( greatestEle ).priority() ){
      greatestEle = rightChild;
    }
    // if the parent isnt the greatest element
    if (greatestEle != parent){
      // swap the parent and greatest element
      swap(_heap.at(parent), _heap.at(greatestEle));
      // recursively call with new root
      reheapDown(greatestEle);
    }
    
  }
  
};

// ***************************************
// Templated function definitions go here!
// ***************************************

template <class T>
Heap<T>::Heap(){
  // insert a place holder for index 0
  T placeHolder;
  _heap.push_back(placeHolder);
  _used = false;
}

template <class T>
void Heap<T>::insert(const T& object){

  // add the object, and mark _used true
  _heap.push_back(object);
  _used = true;

  // create the index after pushing to the back of the vector
  int index = _heap.size() - 1;

  // while the parents prio is less than the childs, swap them
  while (_heap.at(index/2).priority() < _heap.at(index).priority() && index/2 != 0){
    swap(_heap.at(index), _heap.at(index/2));

    // change index
    index = index/2;
  }

}

template <class T>
T Heap<T>::readTop() const{
  // throw a range_error exception if the heap is empty
  if (empty()){
    throw range_error("Heap<T>::readTop(): called with an empty heap");
  }
  return _heap.at(ROOT);
}

template <class T>
void Heap<T>::removeTop(){
  // throw a range_error exception if the heap is empty
  if (empty()){
    throw range_error("Heap<T>::removeTop(): called with an empty heap");
  }
  else{ 
    // hold the last element
    T lastElement = _heap.at( _heap.size() - 1);
    // delete the last element in the heap
    _heap.pop_back();

    // if the _heap is now empty, just return
    if (empty()){
      return;
    }
    
    // if the heap isnt empty
    // replace the deleted root with last element
    _heap.at(ROOT) = lastElement;

    // heap down to maintain max-heap priority
    reheapDown(ROOT);
  }
}

template <class T>
void Heap<T>::dump() const{
  // iterate through the heap, and print its elements
  for (unsigned int i = ROOT; i < _heap.size(); i++){
    cout << _heap.at(i) << endl;
  }
}

#endif
