#include <iostream>
#include "hash.h"
#include "donut.h"


// Prototype for 16 bit cyclic hash function; implementation is after      
// main().                                                                 
unsigned cyclic_hash16(string key);
unsigned myHash(string key);

int main() {

  // Create a vector of donuts to insert in the hash table                 
  vector<Donut> donuts;

  donuts.push_back(Donut("A", 1, "super donut"));
  donuts.push_back(Donut("B", 2, "super donut"));
  donuts.push_back(Donut("C", 3, "super donut"));
  donuts.push_back(Donut("D", 14, "super donut"));
  donuts.push_back(Donut("E", 5, "super donut"));
  donuts.push_back(Donut("F", 6, "super donut"));
  donuts.push_back(Donut("G", 7, "super donut"));
  donuts.push_back(Donut("H", 8, "super donut"));
  donuts.push_back(Donut("I", 9, "super donut"));
  donuts.push_back(Donut("J", 10, "super donut"));
  donuts.push_back(Donut("A", 50, "super donut"));
  donuts.push_back(Donut("A", 14, "super donut"));
  donuts.push_back(Donut("A", 15, "super donut"));
  donuts.push_back(Donut("A", 2, "super donut"));
  donuts.push_back(Donut("A", 70, "super donut"));
  donuts.push_back(Donut("A", 10, "super donut"));
  donuts.push_back(Donut("J", 10, "super donut"));
  donuts.push_back(Donut("J", 9, "super donut"));
  donuts.push_back(Donut("J", 2, "super donut"));
  donuts.push_back(Donut("J", 12, "super donut"));
  donuts.push_back(Donut("J", 1, "super donut"));
  donuts.push_back(Donut("J", 7, "super donut"));
  donuts.push_back(Donut("A", 100, "super donut"));
  donuts.push_back(Donut("A", 170, "super donut"));
  donuts.push_back(Donut("A", 7, "super donut"));
  donuts.push_back(Donut("A", 3, "super donut"));
  
  // Create the hash table of length 10 using cyclic_hash function         
  HashTable<Donut> ht(10, myHash);

  // Insert the donut orders                                               
  for (auto d : donuts) {
    ht.insert(d);
  }

  cout << "\nDump of ht:\n";
  ht.dump();

  Donut d;

  /*
  ht.getNext("A", d);
  ht.getNext("A", d);
  ht.getNext("A", d);
  ht.getNext("A", d);
  ht.getNext("A", d);
  */
  
  ht.getNext("J", d);
  ht.getNext("J", d);
  ht.getNext("J", d);
  ht.getNext("J", d);
  ht.getNext("J", d);
  

  cout << endl;
  cout << "\nDump of new ht:\n";
  ht.dump();
  return 0;
}

unsigned myHash(string key) {
  unsigned h = 0;

  h = 5;

  return h;
}
