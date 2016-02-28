#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "AdjListObject.h"
#include <string>

#define TABLE_SIZE 211
#define OVERALL_OFFSET 53
#define AGE_OFFSET 20
#define OCCUPATION_OFFSET 23

//This class represents the adjacency list
class AdjacencyList 
{
 public:
  AdjacencyList();
  void insert(std::string name, int age, std::string occupation, std::string *friends, int friendarraysize);
  int hash(std::string str, int seed = 0);
  void search(std::string name);
  void print(int index);
  
 private:
  int numElements;
  AdjListObject* array;
};
#endif
