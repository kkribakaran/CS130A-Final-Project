#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "AdjListObject.h"
#include <string>

class AdjacencyList 
{
 public:
  AdjacencyList();
  void AdjacencyList::insert(std::string name, int age, std::string occupation, std::string *friends, int friendarraysize);
  int hash(std::string str, int seed = 0);
  void search(std::string name);
  void print(int index);
  
 private:
  int filled;
  int TABLE_SIZE;
  AdjListObject* array;
};
#endif
