#include "AdjacencyList.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

//constructor
AdjacencyList::AdjacencyList()
{
  array = new AdjListObject[TABLE_SIZE]; 
  numElements = 0;
}
void AdjacencyList::insert(string name, int age, string occupation, string *friends, int friendarraysize)
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
      if (index + 1 == TABLE_SIZE)
	  index = 0;
      else 
	  index++;
    }
  AdjListObject newEntry = new AdjListObject(name);
  array[index] = newEntry;
  //write to profile data
  FILE * pFile;
  pFile = fopen("ProfileData.txt", "w");
  /**
     Go to the next emtpy spot in the file by
     multiplying the overall offset by the
     number of elements
  **/
  int offset = OVERALL_OFFSET * numElements;
  //write the name in
  fseek(pFile,offset,SEEK_SET);
  fputs(name.c_str(),pFile);
  //write the age in
  fseek(pFile,offset + AGE_OFFSET,SEEK_SET);
  Cstring tempstr;
  tempstr.Format("%d",age);
  fputs(tempstr,pFile);
  //write the occupation in
  fseek(pFile,offset + OCCUPATION_OFFSET,SEEK_SET);
  fputs(occupation.c_str(),pFile);
  fclose(pFile);
  //write to hashtable 
  //TODO
  
}
//the hash function
int AdjacencyList::hash(string str, int seed) {
  int hash = seed;
  for (int i = 0;i < (int) str.length();i++)
      hash = hash * 101 + str[i];
  
  return hash % TABLE_SIZE;
}

void AdjacencyList::search(string name) {
  //TODO
}
void AdjacencyList::print(int index) {
  //TODO
}
