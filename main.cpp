#include "AdjListObject.h"
#include <iostream>
using namespace std;

int main()
{
  AdjListObject steve("Steve", 5);
  steve.addFriend("Dave");
  steve.addFriend("Tammy");
  steve.addFriend("Bob");

  for(AdjListObject::FriendNode* p = steve.getRoot(); p!= NULL; p = p->next)
    cout<<p->name<<endl;

  return 0;
}
