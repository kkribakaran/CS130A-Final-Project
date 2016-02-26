#include "AdjacencyList.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

AdjacencyList::AdjacencyList()
{
  array = new AdjListObject[211]; 
  filled = 0;
  TABLE_SIZE = 211;
}
void AdjacencyList::insert(string name, int age, string occupation, string *friends, int friendarraysize)  //determine array index
{
  index = hash(name);
  while (array[index].name != "")
    {
      if (array[index].name == name) 
	{
	  cout<<"user already exists in system"<<endl;
	  return;
	}
      if (index + 1 == TABLE_SIZE)
	{
	  index = 0;
	} else 
	{
	  index++;
	}
    }
  //write to profile data
  FILE * pFile;
  pFile = fopen("ProfileData.txt", "w");
  int offset = 53 * filled;
  fseek(pFile,offset,SEEK_SET);
  fputs(name.c_str(),pfile);
  fseek(pFile,offset + 20,SEEK_SET);
  CString tempstr;
  tempstr.Format("%d",age);
  fputs(tempstr,pfile);
  fseek(pFile,offset + 23,SEEK_SET);
  fputs(occupation.c_str(),pfile);
  fclose(pFile);
  //write to hashtable 
  //TODO
  
}
int AdjacencyList::hash(string str, int seed = 0) {
  int hash = seed;
  for (int i = 0;i < str.length();i++)
    {
      hash = hash * 101 + str[i];
    }
  return hash % TABLE_SIZE;
}

void AdjacencyList::search(string name) {
  //TODO
}
void AdjacencyList::print(int index) {
  //TODO
}
