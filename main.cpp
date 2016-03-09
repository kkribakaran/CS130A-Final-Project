#include "AdjListObject.h"
#include "AdjacencyList.h"
#include "Btree.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

vector<string> split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);       // turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	}

	return internal;
}

int main(int argc, char* argv[])
{
  if(argc < 2)
    {
      cout<<"Please input a text file"<<endl;
      return 0;
    }
  
  AdjacencyList list;
  Btree tree;

  //if ProfileData already exists, delete it. 
  FILE* profileData;
  profileData = fopen("ProfileData.txt","r");
  if (profileData)
    std::remove("ProfileData.txt");


  ifstream f;

  f.open(argv[1], ios::in);


  if(!f)
    cerr << "File not found" << endl;
  else
    {
      //counter for btree index
      int btreeIndexCounter = 0;
      string line;
      while(std::getline(f, line))
	{
	  vector<string> words = split(line, ',');
	  vector<string> friends;
	  for(int i = 3; i < (int) words.size(); i++)
	    friends.push_back(words.at(i));
	  list.initInsert(words.at(0),words.at(1),words.at(2),friends,(int)friends.size());
	  tree.insert(words.at(0),btreeIndexCounter);
	  btreeIndexCounter++;
	}
    }
  while (true) 
    {
      std::string input = "";
      std::string command = "";
      getline(cin,input);
      istringstream iss(input);
      iss>>command;
      vector<string> parameters;
      string currentParam = "";
      while (iss>>currentParam)
	parameters.push_back(currentParam);
      
      if (command == "Insert")
	{
	  string name = parameters.at(0);
	  string age = parameters.at(1);
	  string occupation = "";
	  //number of space dilineated words in occupation
	  int wordCount = (int)parameters.size();
	  
	  occupation += parameters.at(2);
	  for (int i = 3; i < wordCount; i++)
	    {
	      occupation += " ";
	      occupation += parameters.at(i);
	    }
	  occupation = occupation.substr(1,occupation.length()-2);
	  list.insert(name,age,occupation);			   
	 
	} 
      else if (command == "AddFriend") 
	{
	  string friend1 = parameters.at(0);
	  string friend2 = parameters.at(1);
	  list.addFriend(friend1,friend2);
	}
      else if (command == "ListFriendsInfo")
        {
          string name  = parameters.at(0);
          list.listFriendsInfo(name);
	}
      else if (command == "PrintAll")
        {
	  list.printAll();
	}
      else if (command == "ListInfo")
        {
          tree.rangeQuery(parameters.at(0),parameters.at(1));
        }
      else if (command == "Delete")
        {
          list.deleteName(parameters.at(0));
	  tree.removeName(parameters.at(0));
        }
      else
	{
	  cout<<"Invalid Command."<<endl;  
	}
    }
    return 0;
}
