#include "Btree.h"
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

Btree::Btree()
{
  root = NULL;
  filled = 0;
}

void Btree::insert(string name)
{
  //if Btree is empty, create new leaf node, put person in first index
  if (root == NULL)
  {
    Node* leafNode = new Node();
    leafNode->isLeaf = true;
    leafNode->leaf = new Person[4];
    leafNode->leaf[0].name = name;
    leafNode->leaf[0].index = filled;
    leafNode->leafCount = 1;
    root = leafNode;
    filled++;
    return;
  }
  //go to the leafNode that has the name
  Node* currentNode = traverseToLeaf(name);
  
  //find out where new person goes in leaf array
  int i;
  for (i = 0; i < currentNode->leafCount; i++)
    {
      if (name < currentNode->leaf[i].name)
        break;
    }
  //shift people in leaf array to make room for new person
  for (int j = currentNode->leafCount; j > i; j--)
    {
      currentNode->leaf[j] = currentNode->leaf[j-1];
    }
  //insert person
  currentNode->leaf[i].name = name;
  currentNode->leaf[i].index = filled;
  currentNode->leafCount++;
  filled++;

  //if leaf is full
  if (currentNode->leafCount ==4)
    {
      
      //create new leaf Node and splitNode
      Node* splitNode = new Node();
      splitNode->isLeaf = true;
      splitNode->leaf = new Person[4];

      //take last 2 elements of currentNode and
      //place them in the first two spots of splitNode
      splitNode->leaf[0] = currentNode->leaf[2];
      splitNode->leaf[1] = currentNode->leaf[3];

      //update leafCoount and parent
      splitNode->leafCount = 2;
      currentNode->leafCount = 2;
      splitNode->parent = currentNode->parent;

      //make splitNode point to currentNode's next leaf
      //and have currentNode's next leaf point to splitNode
      splitNode->next = currentNode->next;
      currentNode->next = splitNode;
      
      //if parent of currentNode is NULL, create a parent Node
      if (!(currentNode->parent))
	{
	  Node *parent = new Node();
	  parent->isLeaf = false;
	  parent->keys = new string[5];
	  parent->children = new Node*[6];
	  
	  parent->keys[0] = splitNode->leaf[0].name;
	  parent->keyCount = 1;
	  parent->children[0] = currentNode;
	  parent->children[1] = splitNode;
	  currentNode->parent = parent;
	  splitNode->parent = parent;
	  root = parent;
      }
      
      //otherwise call siftup and recurse upwards 
      else 
	{ 
	  siftUp(currentNode->parent,splitNode->leaf[0].name,splitNode);
	}
    }
}

void Btree::print(int index)
{
  //open ProfileData.txt
  FILE * profileData;
  profileData = fopen("ProfileData.txt", "r");

  //calculate offset based on profiledata index
  int offset = OVERALL_OFFSET * index;
  char name[20];
  char age[4];
  char occupation[30];

  //seek and read data to variables.
  fseek(profileData,offset,SEEK_SET);
  fgets(name,20,profileData);
  fseek(profileData,offset + AGE_OFFSET,SEEK_SET);
  fgets(age,4,profileData);
  fseek(profileData,offset + OCCUPATION_OFFSET,SEEK_SET);
  fgets(occupation,30,profileData);
  //print variables
  cout<<name<<","<<age<<","<<occupation<<endl;
}

void Btree::removeName(string name)
{
  //go to the leaf Node with name
  Node* currentNode = traverseToLeaf(name);
  
  int index = -1;
  for (int i = 0; i < currentNode->leafCount; i++)
    {
      if (name == currentNode->leaf[i].name)
        {
          index = i;
          break;
        }
    }
  if (index == -1)
    return;
  currentNode->leaf[index].isDeleted = true;
}

//prints out information of all people from nameLowerBound to nameUpperBound
void Btree::rangeQuery(string nameLowerBound, string nameUpperBound)
{
  //go to the leafNode with nameLowerBound
  Node* currentNode = traverseToLeaf(nameLowerBound);
  
  //find the index where lower bound is located
  int i;
  for (i = 0; i < currentNode->leafCount; i++)
    {
      if (nameLowerBound <= currentNode->leaf[i].name)
	{
	  break;
	}
    }
  
  //print out people starting at lower bound
  while (i < currentNode->leafCount)
    {
      //if it hits upper bound in same leaf
      if (nameUpperBound < currentNode->leaf[i].name)
	{
	  return;
	}
      if (!(currentNode->leaf[i].isDeleted)) 
	print(currentNode->leaf[i].index);
      i++;
    }
  //call helper function with currentNode->next until it reaches upper bound
  rangeQueryHelper(currentNode->next, nameUpperBound);
}


/**
   Recurseive rangeQuery helper function, prints out all
   Person objects in leaf until it hits upper bound 
**/
void Btree::rangeQueryHelper(Node* currentNode, string nameUpperBound) 
{
  //if null, then return
  if (!currentNode)
    return;
  
  //iterate through all the Person objects in the leaf
  for (int i = 0; i < currentNode->leafCount;i++)
    {
      //if upper bound reached, then return
      if (nameUpperBound < currentNode->leaf[i].name)
        {
          return;
        }
      //call print with profile indexx
      if (!(currentNode->leaf[i].isDeleted))
	print(currentNode->leaf[i].index);
    }
  
  //recurse with currentNode->next
  rangeQueryHelper(currentNode->next,nameUpperBound);
}


void Btree::siftUp(Node * currentNode, string keyInsert, Node * nodeInsert) 
{
  //find out where keyInsert goes in currentNode
  int i;
  for (i = 0; i < currentNode->keyCount; i++)
    {
      if (keyInsert < currentNode->keys[i]) 
	break;
    }
  
  //shift keys and children pointers to make room for new key and child
  for (int j = currentNode->keyCount; j > i; j--) 
    {
      currentNode->children[j+1] = currentNode->children[j];
      currentNode->keys[j] = currentNode->keys[j-1];
    }
  
  //insert child and key
  currentNode->children[i+1] = nodeInsert;
  currentNode->keys[i] = keyInsert;
  currentNode->keyCount++;

  //if currentNode is full, split it
  if (currentNode->keyCount == 5) 
    {
      Node *splitNode = new Node();
      splitNode->isLeaf = false;
      splitNode->keys = new string[5];
      splitNode->children = new Node*[6];
      splitNode->parent = currentNode->parent;
   
      /**
	 currentNode currently has 5 keys and 6 children
	 Need to copy last 2 keys of currentNode into splitNode
	 Need to copy last 3 children of currentNode into splitNode
       **/
      for (int j = 0; j < 2; j++)
	{
	  splitNode->children[j] = currentNode->children[j+3];
	  splitNode->keys[j] = currentNode->keys[j+3];
	}
      //copy the last child
      splitNode->children[2] = currentNode->children[5];

      //update keyCounts
      splitNode->keyCount = 2;
      currentNode->keyCount = 2;
      
      //make sure all children point to their respective parents
      for (int j = 0; j <= 2; j++)
	{
	  currentNode->children[j]->parent = currentNode;
	  splitNode->children[j]->parent = splitNode;
	}

      //if parent of currentNode is null, create new parent node
      if (currentNode->parent == NULL)
	{
	  Node *parent = new Node();
	  parent->isLeaf = false;
	  parent->keys = new string[5];
	  parent->children = new Node*[6];
	  currentNode->parent = parent;
	  splitNode->parent = parent;
	  parent->children[0] = currentNode;
	  parent->children[1] = splitNode;
	  parent->keys[0] = currentNode->keys[2];
	  root = parent;
	  parent->keyCount = 1;
	}
      //if parent is not null, recurse to parent node
      else 
	{
	  siftUp(currentNode->parent,currentNode->keys[2],splitNode);
	}
    }
}
//returns a pointer to the leafNode with name in its leafArray
Node* Btree::traverseToLeaf(string name)
{
  //traverse Btree to leaf to insert
  Node* currentNode = root;
  while (!(currentNode->isLeaf))
    {
      //if name is greater than the greatest key in Node, traverse to last child
      if (name >= currentNode->keys[currentNode->keyCount - 1])
	{
	  currentNode = currentNode->children[currentNode->keyCount];
	}
      //find out which child to traverse to
      else
	{
	  for (int i = 0; i <currentNode->keyCount; i++)
	    {
	      if (name < currentNode->keys[i])
		{
		  currentNode = currentNode->children[i];
		  break;
		}
	    }
	}
    }
  return currentNode;
}













  
  
  
  
  
  
  
      
  
  
  
