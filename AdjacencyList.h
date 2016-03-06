#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "AdjListObject.h"
#include <string>
#include <vector>

#define TABLE_SIZE 211
#define OVERALL_OFFSET 53
#define AGE_OFFSET 20
#define OCCUPATION_OFFSET 23

//This class represents the adjacency list
class AdjacencyList 
{
 public:
  //constructor
  AdjacencyList();

  //Inserts a new entry into the list and the profile data
  void initInsert(std::string name, std::string age, std::string occupation,std::vector<std::string> friends, int friendArraySize);
  
  void insert(std::string, std::string age, std::string occupation);
  //the hash function
  int hash(std::string str, int seed = 0);
  void search(std::string name);
  void print(std::string name);
  void listFriendsInfo(std::string name);

  void addFriend(std::string friend1, std::string friend2);
  void printAll();

 private:
  int numElements;
  AdjListObject* array;

  int getHashedIndex(std::string name);
};
#endif
