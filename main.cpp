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
int main()
{
  AdjacencyList list;

  ifstream f;
  f.open("input.txt", ios::in);
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
	  list.insert(words[0],words[1],words[2],friends,friends.size());
	}
    }
  return 0;
}
