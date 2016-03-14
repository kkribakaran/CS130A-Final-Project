#include "AdjacencyList.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

//constructor
AdjacencyList::AdjacencyList()
{
  array = new AdjListObject[TABLE_SIZE]; 
  numElements = 0;
}

void AdjacencyList::initInsert(string name, string age, string occupation,vector<string> friends, int friendArraySize)
{
  insert(name,age,occupation);
  //add all the friends
  int index = getHashedIndex(name);
  for(int i = 0; i <(int)friendArraySize; i++) {
    array[index].addFriend(friends.at(i));
  }

}
void AdjacencyList::insert(string name, string age, string occupation)
{
  //determine original index that name is hashed to
  int index = hash(name);
  /**
     If original spot is filled, keep updating index until you 
     find an empty spot or if the name is already in the list
  **/
  while (array[index].getName() != "")
    {
      if (array[index].getName() == name) 
	{
	  cout<<"user already exists in system"<<endl;
	  return;
	}
      //loop around the array if it reaches the end
      if (index + 1 == TABLE_SIZE)
	  index = 0;
      else 
	  index++;
    }

  
  //write to profile data
  FILE * profileData;
  profileData = fopen("ProfileData.txt", "r+");
  if(!profileData)
    profileData = fopen("ProfileData.txt", "w");
  
  /**
     Go to the next emtpy spot in the file by
     multiplying the overall offset by the
     number of elements
  **/
  int offset = OVERALL_OFFSET * numElements;
  //write the name in
  fseek(profileData,offset,SEEK_SET);
  fputs(name.c_str(),profileData);
  //write the age in
  fseek(profileData,offset + AGE_OFFSET,SEEK_SET);
  fputs(age.c_str(),profileData);
  //write the occupation in
  fseek(profileData,offset + OCCUPATION_OFFSET,SEEK_SET);
  fputs(occupation.c_str(),profileData);
  fclose(profileData);
  
  //add to hashtable
  array[index].setName(name);
  array[index].setProfileDataIndex(numElements);

  numElements++;
}

//the hash function
int AdjacencyList::hash(string str, int seed)
{
  int hash = seed;
  for (int i = 0;i < (int) str.length();i++)
    hash = (hash * 101 + str[i]) % TABLE_SIZE;
  return hash;
}

//List the info of all of name's friends
void AdjacencyList::listFriendsInfo(string name) {
  int index = getHashedIndex(name);
  /**
     If the original hashed index is empty, it means
     the name isn't in the network
  **/
  if(index == -1 || array[index].isPersonDeleted())
    {
      cout<<"Name not found"<<endl;
      return; 
    }
 
  //print the friends' info
  AdjListObject currentObject = array[index];
  AdjListObject::FriendNode* friendsList = currentObject.getRoot();
  for(AdjListObject::FriendNode* p = friendsList; p != NULL; p = p->next)
    {
      //call print function on friend's name
      print(p->name);
      cout<<endl;
    }
}

//Print the name, age, and occupation of the given name
//Precondition: All of friends are in Adjacency List
void AdjacencyList::print(string name) {
  int index = getHashedIndex(name);

  AdjListObject printedObject = array[index];
 
  //open ProfileData.txt
  FILE * profileData;
  profileData = fopen("ProfileData.txt", "r");
  
  //calculate offset based on profiledata index
  int offset = OVERALL_OFFSET * printedObject.getProfileDataIndex();
  char age[4];
  char occupation[30];

  //seek and read data to variables.
  fseek(profileData,offset + AGE_OFFSET,SEEK_SET);
  fgets(age,4,profileData);
  fseek(profileData,offset + OCCUPATION_OFFSET,SEEK_SET);
  fgets(occupation,30,profileData);

  cout<<name<<","<<age<<","<<occupation;  
}

//precondition: friend1 and friend1 are in the list
void AdjacencyList::addFriend(string friend1, string friend2)
{
  
  //get indexes of each friend
  int friend1index = getHashedIndex(friend1);
  int friend2index = getHashedIndex(friend2);
  
  if (array[friend1index].isPersonDeleted() || array[friend2index].isPersonDeleted())
    return;

  array[friend1index].addFriend(friend2);
  array[friend2index].addFriend(friend1);
  
}
//gets the index name is hashed to in the array
int AdjacencyList::getHashedIndex(string name)
{
  int originalIndex = hash(name);
  if(array[originalIndex].getName() == "")
    return -1;
  
  //use linear probing if name at original index doesn't match
  while (array[originalIndex].getName() != name)
    {
      if (array[originalIndex].getName() == "") 
	return -1;
      //loop around array if it reaches the end
      if (originalIndex + 1 == TABLE_SIZE)
	  originalIndex = 0;
      else 
	  originalIndex++;
    }
  if (array[originalIndex].isPersonDeleted())
    return -1;
  return originalIndex;
}

void AdjacencyList::printAll() 
{
  for (int i = 0; i < 211; i++)
    {
      if (array[i].getName() != "" && !array[i].isPersonDeleted()) 
	{
	  print(array[i].getName());
	  AdjListObject::FriendNode* currentFriend = array[i].getRoot();
	  while (currentFriend)
	    {
	      cout<<","<<currentFriend->name;
	      currentFriend=currentFriend->next;
	    }
	  cout<<endl;
	}
    }
}

void AdjacencyList::deleteName(string name)
{
  int index = getHashedIndex(name);
  if (index == -1 || array[index].isPersonDeleted())
    return;
  array[index].setDeleted();
  for (AdjListObject::FriendNode* currentFriend = array[index].getRoot(); currentFriend!=NULL; currentFriend=currentFriend->next)
    {
      int friendIndex = getHashedIndex(currentFriend->name);
      array[friendIndex].removeFriend(name);
    }
}
