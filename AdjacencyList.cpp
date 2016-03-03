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
      if (index + 1 == TABLE_SIZE)
	  index = 0;
      else 
	  index++;
    }



  ofstream profileData;
  profileData.open("ProfileData.txt");
  int offset = OVERALL_OFFSET * numElements;
  profileData.seekp(offset);
  profileData.write(name.c_str(),name.size());
  profileData.seekp(offset + AGE_OFFSET);
  profileData.write(age.c_str(),age.size());
  profileData.seekp(offset + OCCUPATION_OFFSET);
  profileData.write(occupation.c_str(),occupation.size());
  profileData.close();
  //write to profile data
  /**
  FILE * pFile;
  pFile = fopen("ProfileData.txt", "r+");
  if(!pFile)
    pFile = fopen("ProfileData.txt", "w");
  
 
     Go to the next emtpy spot in the file by
     multiplying the overall offset by the
     number of elements
  
  int offset = OVERALL_OFFSET * numElements;
  //write the name in
  fseek(pFile,offset,SEEK_SET);
  fputs(name.c_str(),pFile);
  //write the age in
  fseek(pFile,offset + AGE_OFFSET,SEEK_SET);
  fputs(age.c_str(),pFile);
  //write the occupation in
  fseek(pFile,offset + OCCUPATION_OFFSET,SEEK_SET);
  fputs(occupation.c_str(),pFile);
  fclose(pFile);
  **/
  //add to hashtable
  AdjListObject newEntry(name, offset);
  array[index] = newEntry;
  numElements++;

  //add all the friends
  for(int i = 0; i <(int)friendArraySize; i++) 
    array[index].addFriend(friends.at(i));
}

//the hash function
int AdjacencyList::hash(string str, int seed) {
  int hash = seed;
  for (int i = 0;i < (int) str.length();i++)
    hash = (hash * 101 + str[i]) % TABLE_SIZE;
  
  return hash;
}

void AdjacencyList::search(string name) {
  //TODO
}
void AdjacencyList::print(int index) {
  //TODO
}
