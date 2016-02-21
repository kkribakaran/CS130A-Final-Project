#include "AdjacencyList.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cstring>

AdjacencyList::AdjacencyList() {
  array = new AdjListObject[201]; 
  filled = 0;
  TABLE_SIZE = 201;
}
void AdjacencyList::insert(std::string name, int age, std::string occupation, std::string *friends, int friendarraysize) {
  //determine array index
  index = hash(name);
  while (array[index].name != "") {
    if (array[index].name == name) {
      cout<<"user already exists in system"<<endl;
      return;
    }
    if (index + 1 == TABLE_SIZE) {
      index = 0;
    } else {
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
int AdjacencyList::hash(std::string str, int seed = 0) {
  int hash = seed;
  for (int i = 0;i < str.length();i++) {
    hash = hash * 101 + str[i];
  }
  return hash % TABLE_SIZE;
}

void AdjacencyList::search(std::string name) {
  //TODO
}
void AdjacencyList::print(int index) {
  //TODO
}
