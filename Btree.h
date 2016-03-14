#ifndef BTREE_H
#define BTREE_H
#include <string>
#define OVERALL_OFFSET 54
#define AGE_OFFSET 20
#define OCCUPATION_OFFSET 24

//This struct reperesents a Person in the B-tree, has name and index in ProfileData 
struct Person
{
  std::string name;
  int index;
  bool isDeleted;
  Person() 
  {
    name = "";
    index = -1;
  }
};

//This Struct represents a Node in the B-tree, can be leaf or internal node
struct Node
{
  bool isLeaf; 
  Node* parent; //pointer to parent
  //if Node is a leaf, these parameters apply:
  Person *leaf; //pointer to Person objects
  int leafCount; //number of Person objects in leaf
  Node* next; //pointer to next leafNode
  //ifInternalNode
  Node** children; //6 pointers to children nodes (5 + 1 because we accomodate extra space for splitting)
  std::string* keys; //5 string pointers, each string represents a key (4+1)
  int keyCount; //number of keys in node
  Node()//constructor for node
    {
      leafCount = 0;
      keyCount = 0;
      parent = NULL;
      next = NULL;
      
    } 
};

class Btree{
 public:
  Btree();
  void insert(std::string name); //inserts new person with given name into b tree 
  void rangeQuery(std::string nameLowerBound, std::string nameUpperBound); //prints out names of all users from a to b
  void removeName(std::string name);
 private:
  Node* root;
  int filled;
  void print(int index);
  void rangeQueryHelper(Node* currentNode, std::string nameUpperBound);
  //helper function for insert
  //currentNode is the node we are currently at
  //keyInsert is the new key we need to add
  //nodeInsert is the newly split node we need to add, will eventually
  //become a child of currentNode
  void siftUp(Node *currentNode, std::string keyInsert, Node *nodeInsert);
  

};

#endif
