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
void AdjacencyList::insert(string name, string age, string occupation,vector< string> friends, int friendArraySize)
{
  //determine original index that name is hashed to
  int index = hash(name);

  /**
     If original spot is filled, keep updating index until you 
     find an empty spot or if the name is already in the list
  **/
  while (numElements != 0 && array[index].getName() != "")
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
  AdjListObject newEntry(name, offset);
  array[index] = newEntry;
  numElements++;

  //add all the friends
  for(int i = 0; i <(int)friendArraySize; i++) 
    array[index].addFriend(friends.at(i));
}

//the hash function
int AdjacencyList::hash(string str, int seed)
{
  int hash = seed;
  for (int i = 0;i < (int) str.length();i++)
    hash = (hash * 101 + str[i]) % TABLE_SIZE;
  
  return hash;
}

void AdjacencyList::listFriendsInfo(string name) {
  
  int index = getHashedIndex(name);
  
  /**
     If the original hashed index is empty, it means
     the name isn't in the network
  **/
  if(index == -1)
    {
      cout<<"Name not found"<<endl;
      return; 
    }
  
  //print the friends' info
  AdjListObject currentObject = array[index];
  FriendNode* friendsList = currentObject.getRoot();
  for(FriendNode* p = friendsList; p != NULL; p = p->next)
    print(p->getName());
}
//Print the name, age, and occupation of the given name
void AdjacencyList::print(string name) {
  int index = getHashedIndex(name);
  AdjacencyListObject printedObject = array[index];
  FILE * profileData;
  profileData = fopen("ProfileData.txt", "r");
  fseek(profileData,printedObject.getProfileDataIndex,SEEK_SET);
  
}
int AdjacenyList::getHashedIndex(string name)
{
  int originalIndex = hash(name);
  if(array[originalIndex].getName() == "")
    return -1;
  
  //use linear probing if name at original index doesn't match
  while (array[originalIndex].getName() != "")
    {
      //loop around array if it reaches the end
      if (originalIndex + 1 == TABLE_SIZE)
	  originalIndex = 0;
      else 
	  originalIndex++;
    }
  return originalIndex;
}
