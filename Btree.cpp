#include "Btree.h"
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

void Btree::insert(string name, int index)
{
  //if Btree is empty, create new leaf node, put person in first index
  if (root == NULL)
  {
    Node* leafNode = new Node();
    leafNode->isLeaf = true;
    leafNode->leaf = new Person[4];
    leafNode->leaf[0].name = name;
    leafNode->leaf[0].index = index;
    leafNode->leafCount = 1;
    root = leafNode;
  }

  //traverse Btree to leaf to insert
  Node* currentNode = root;
  while (!(currentNode->isLeaf))
    {
      //if name is greater than the greatest key in Node, traverse to last child
      if (name > currentNode->keys[currentNode->keyCount - 1])
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
  
  //if leaf is full
  if (currentNode->leafCount ==3)
    {
      //find out which index new person should be inserted
      int i;
      for (i = 0; i < 3; i++)
	{
	  if (name < currentNode->leaf[i].name)
	    {
	      break;
	    }
	}
      //if name is greater than any of the values
      if (i==3) 
	{
	  currentNode->leaf[3].name = name;
	  currentNode->leaf[3].index = index;
	} 
      else 
	{
	  for (int j = 3; j > i; j--)
	    {
	      currentNode->leaf[j] = currentNode->leaf[j-1];
	    }
	  currentNode->leaf[i].name = name;
	  currentNode->leaf[i].index = index;
	}

      //create new leaf Node and split
      Node* split = new Node();
      split->isLeaf = true;
      split->leaf = new Person[4];

      split->leaf[0] = currentNode->leaf[2];
      split->leaf[1] = currentNode->leaf[3];
      split->leafCount = 2;
      currentNode->leafCount = 2;
      split->parent = currentNode->parent;
      split->next = currentNode->next;
      currentNode->next = split;
      
      //if parent of currentNode is NULL, create a parent Node
      if (!(currentNode->parent))
	{
	  Node *parent = new Node();
	  parent->isLeaf = false;
	  parent->keys = new string[5];
	  parent->children = new Node*[6];
	  
	  parent->keys[0] = split->leaf[0].name;
	  parent->keyCount = 1;
	  parent->children[0] = currentNode;
	  parent->children[1] = split;
	  currentNode->parent = parent;
	  split->parent = parent;
	  root = parent;
      } 
      else  //otherwise call siftup and recurse upwards 
	{ 
	  
	  siftUp(currentNode->parent,split->leaf[0].name,split);
	}
      
    }
  //current leaf node isn't full, so insert person directly, no splitting
  else {
    if (currentNode->leafCount == 1)
      {
	currentNode->leaf[1].name = name;
	currentNode->leaf[1].index = index;
      }
    else if (name < currentNode->leaf[1].name) 
      {
	currentNode->leaf[2] = currentNode->leaf[1];
	currentNode->leaf[1].name = name;
	currentNode->leaf[1].index = index;
      }
    else 
      {
	currentNode->leaf[2].name = name;
	currentNode->leaf[2].index = index;
      }
    currentNode->leafCount++;
    
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
  char age[3];
  char occupation[30];

  //seek and read data to variables.
  fseek(profileData,offset,SEEK_SET);
  fgets(name,20,profileData);
  fseek(profileData,offset + AGE_OFFSET,SEEK_SET);
  fgets(age,3,profileData);
  fseek(profileData,offset + OCCUPATION_OFFSET,SEEK_SET);
  fgets(occupation,30,profileData);
  //print variables
  cout<<name<<","<<age<<","<<occupation<<endl;
}

//prints out information of all people from nameLowerBound to nameUpperBound
void Btree::rangeQuery(string nameLowerBound, string nameUpperBound)
{
  //traverse to leaf node that contains nameLowerBound
  Node* currentNode = root;
  while (!(currentNode->isLeaf))
    {
      //if name is greater than the greatest key in Node, traverse to last child
      if (nameLowerBound >= currentNode->keys[currentNode->keyCount - 1])
        {
          currentNode = currentNode->children[currentNode->keyCount];
        }
      //find out which child to traverse to
      else
        {
          for (int i = 0; i <currentNode->keyCount; i++)
            {
              if (nameLowerBound < currentNode->keys[i])
                {
                  currentNode = currentNode->children[i];
                  break;
                }
            }
        }
    }
  //find the index where lower bound begins
  int index = 0;
  for (int i = 0; i < currentNode->leafCount; i++)
    {
      if (nameLowerBound <= currentNode->leaf[i].name)
	{
	  index = i;
	  break;
	}
    }
  //print out people starting at lower bound
  while (index < currentNode->leafCount)
    {
      //if it hits upper bound in same leaf
      if (nameUpperBound < currentNode->leaf[index].name)
	{
	  return;
	}
      print(currentNode->leaf[index].index);
      index++;
    }
  //call helper function with currentNode->next until it reaches upper bound
  rangeQueryHelper(currentNode->next, nameUpperBound);
}


/*recurseive rangequery helper function, prints out all
  Person objects in leaf until it hits upper bound */
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
      //call print with profile index
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
  //shift keys and children to make room for new key and child
  for (int j = currentNode->keyCount; j > i; j--) 
    {
      currentNode->children[j+1] = currentNode->children[j];
      currentNode->keys[j] = currentNode->keys[j-1];
    }
  //insert child and key
  currentNode->children[i+1] = nodeInsert;
  currentNode->keys[i] = keyInsert;
  currentNode->keyCount++;
  
  //if Node is full
  if (currentNode->keyCount == 5) 
    {
      Node *splitNode = new Node();
      splitNode->isLeaf = false;
      splitNode->keys = new string[5];
      splitNode->children = new Node*[6];
      
      
      //copy latter half of currentNode to splitNode
      for (int j = 0; j < 2; j++)
	{
	  splitNode->children[j] = currentNode->children[j+3];
	  splitNode->keys[j] = currentNode->keys[j+3];
	}
      splitNode->children[2] = currentNode->children[5];
      
      splitNode->keyCount = 2;
      currentNode->keyCount = 2;
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
