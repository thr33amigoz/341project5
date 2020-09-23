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

  // Create the hash table of length 10 using cyclic_hash function    
  HashTable<Donut> ht(10, myHash);

  // Insert the donut orders                                          
  for (auto d : donuts) {
    ht.insert(d);
  }
  
  cout << "\nDump of ht:\n";
  ht.dump();
  
  Donut d;
  
  ht.getNext("C", d);
  ht.getNext("E", d);
  ht.getNext("H", d);
  
  vector<Donut> donuts2;
  
  donuts2.push_back(Donut("K", 1, "shack of donuts"));
  donuts2.push_back(Donut("C", 2, "shack of donuts"));
  donuts2.push_back(Donut("I", 3, "shack of donuts"));
  donuts2.push_back(Donut("A", 4, "shack of donuts"));
  donuts2.push_back(Donut("Z", 5, "shack of donuts"));
  /*
  donuts2.push_back(Donut("F", 3, "shack of donuts"));
  donuts2.push_back(Donut("G", 3, "shack of donuts"));
  donuts2.push_back(Donut("H", 3, "shack of donuts"));  
  donuts2.push_back(Donut("I", 3, "shack of donuts"));
  donuts2.push_back(Donut("J", 3, "shack of donuts"));  
  donuts2.push_back(Donut("K", 3, "shack of donuts"));
  donuts2.push_back(Donut("J", 15, "shack of donuts"));
  donuts2.push_back(Donut("I", 7, "shack of donuts"));
  donuts2.push_back(Donut("H", 20, "shack of donuts"));
  */
  
  //donuts2.push_back(Donut("D", 4, "shack of donuts"));
  //donuts2.push_back(Donut("E", 6, "shack of donuts"));

  for (auto d2 : donuts2) {
    ht.insert(d2);
  }
  
  cout << endl;
  cout << "new ht" << endl;
  ht.dump();

  ht.getNext("F", d);
  ht.getNext("G", d);
  ht.getNext("I", d);
  ht.getNext("Z", d);
  ht.getNext("J", d);
  ht.getNext("A", d);
  ht.getNext("B", d);
  ht.getNext("K", d);
  ht.getNext("D", d);
  ht.getNext("C", d);
  ht.getNext("I", d);
  ht.getNext("A", d);

  cout << endl;
  cout << "emptied ht" << endl;
  ht.dump();
  
  vector<Donut> donuts3;

  donuts3.push_back(Donut("A", 1, "super donut"));
  donuts3.push_back(Donut("B", 2, "super donut"));
  donuts3.push_back(Donut("C", 3, "super donut"));
  donuts3.push_back(Donut("D", 14, "super donut"));
  donuts3.push_back(Donut("E", 5, "super donut"));
  donuts3.push_back(Donut("F", 6, "super donut"));
  donuts3.push_back(Donut("G", 7, "super donut"));
  donuts3.push_back(Donut("H", 8, "super donut"));
  donuts3.push_back(Donut("I", 9, "super donut"));
  donuts3.push_back(Donut("J", 10, "super donut"));
  
  for (auto d3 : donuts3) {
    ht.insert(d3);
  }

  
  ht.getNext("C", d);
  ht.getNext("E", d);
  ht.getNext("H", d);

  vector<Donut> donuts4;
  
  donuts4.push_back(Donut("K", 1, "shack of donuts"));
  donuts4.push_back(Donut("C", 2, "shack of donuts"));
  donuts4.push_back(Donut("I", 3, "shack of donuts"));
  donuts4.push_back(Donut("A", 4, "shack of donuts"));
  donuts4.push_back(Donut("Z", 5, "shack of donuts"));
  donuts4.push_back(Donut("Z", 30, "shack of donuts"));
  donuts4.push_back(Donut("Z", 1, "shack of donuts"));
  donuts4.push_back(Donut("Z", 10, "shack of donuts"));
  donuts4.push_back(Donut("Z", 11, "shack of donuts"));
  donuts4.push_back(Donut("Z", 14, "shack of donuts"));
  donuts4.push_back(Donut("Z", 50, "shack of donuts"));
  donuts4.push_back(Donut("Z", 3, "shack of donuts"));
  donuts4.push_back(Donut("Z", 0, "shack of donuts"));
  donuts4.push_back(Donut("Z", 75, "shack of donuts"));
  donuts4.push_back(Donut("Z", 100, "shack of donuts"));
  
  for (auto d4 : donuts4) {
    ht.insert(d4);
  }
  
  cout << endl;
  cout << "new ht" << endl;
  ht.dump();

  ht.getNext("Z", d);
  ht.getNext("Z", d);

  cout << endl;
  cout << "new new ht" << endl;
  ht.dump();
  
  return 0;
}

unsigned myHash(string key) {
  unsigned h = 0;

  h = 5;
  
  return h;
}
