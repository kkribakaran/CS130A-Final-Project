#include "AdjListObject.h"
#include <string>

using namespace std;

//constructor
AdjListObject::AdjListObject()
{
  name = "";
  profileDataIndex = -10;
  root = NULL;
}
AdjListObject::AdjListObject(string name, int profileDataIndex)
{
  this->name = name;
  this->profileDataIndex = profileDataIndex;
  root = NULL;
}
//getter for name
string AdjListObject::getName()
{
  return name;
}
//getter for profileDataIndex
int AdjListObject::getProfileDataIndex() 
{
  return profileDataIndex;
}
AdjListObject::FriendNode* AdjListObject::getRoot()
{
  return root;
}
//setter for name
void AdjListObject::setName(string name) 
{
  this->name = name; 
}
//setter for profileDataIndex
void AdjListObject::setProfileDataIndex(int index) 
{
  this->profileDataIndex = index;
}
//Adds a friend to this person
void AdjListObject::addFriend(string friendName) 
{
  //create the friend node
  FriendNode* friendNode = new FriendNode();
  friendNode->name = friendName;
  friendNode->next = NULL;

  /**
     Iterate through linked list until we get to the end
     and put the friend at the end
  **/
  FriendNode* temp = root;
  //if there are currently no friends, add the first friend
  if(!temp)
    root = friendNode;
  else
    {
      while (temp->next) 
	{
	  temp = temp->next;
	}
      temp->next = friendNode;
    }
}

