#include "AdjListObject.h"
#include "AdjacencyList.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
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
  ifstream f;
  f.open(argv[1], ios::in);
  
  if(!f) cerr << "File not found" << endl;
  else
    {
      string line;
      while(std::getline(f, line))
	{
	  vector<string> words = split(line, ',');
	  vector<string> friends;
	  for(int i = 3; i < (int)words.size(); i++)
	    friends.push_back(words.at(i));
	  list.insert(words.at(0),words.at(1),words.at(2),friends,(int)friends.size());
	}
    }
  return 0;
}
