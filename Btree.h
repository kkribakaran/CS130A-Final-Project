#ifndef BTREE_H
#define BTREE_H
#include <string>

//This struct reperesents a Person in the B-tree, has name and index in ProfileData 
Struct Person
{
  string name;
  int index;
  Person() 
  {
    name = "";
    index = -1;
  }
}

//This Struct represents a Node in the B-tree, can be leaf or internal node
Struct Node
{
  bool isLeaf; 
  Node* parent; //pointer to parent
  //if Node is a leaf, these parameters apply:
  Person *leaf; //pointer to Person objects
  int leafCount; //number of Person objects in leaf
  Node* next; //pointer to next leafNode
  //ifInternalNode
  Node* children[6]; //6 pointers to children nodes (5 + 1 because we accomodate extra space for splitting)
  String* keys; //5 string pointers, each string represents a key (4+1)
  int keycount; //number of keys in node
  Node()//constructor for node
  {
    String keys = new String[5];
    int leafCount = 0;
    int keyCount = 0;
    parent = NULL;
    for (int i = 0; i < 5; i++)
    {
      keys[i] = "";
    }
  } 
}

class Btree{
  public:
    void insert(string name, int index); //inserts new person with given name and index in to b tree 
    void rangequery(string a, string b); //prints out names of all users from a to b
        
  private:
    Node* root;
    void siftup(Node *x, string name, Node *n); //helper function for insert, x is is Node we are trying to insert to, name is the new key we need to add, n is the node we need to add


};

#endif
