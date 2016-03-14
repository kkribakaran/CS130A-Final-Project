#include "AdjListObject.h"
#include <string>
using namespace std;

//constructor

AdjListObject::AdjListObject()
{
  name = "";
  profileDataIndex = -10;
  root = NULL;
  isDeleted = false;
}

AdjListObject::AdjListObject(string name, int profileDataIndex)
{
  this->name = name;
  this->profileDataIndex = profileDataIndex;
  root = NULL;
  isDeleted = false;
}


//getter for name
string AdjListObject::getName()
{
  return name;
}
//getter for isDeleted
bool AdjListObject::isPersonDeleted()
{
  return isDeleted;
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
//sets isDeleted to true
void AdjListObject::setDeleted()
{
  isDeleted = true;
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
      while (temp->next && temp->next->name != friendName) 
	{
	  temp = temp->next;
	}
      temp->next = friendNode;
    }
}

void AdjListObject::removeFriend(string friendName)
{
  /**
     Iterate through linked list until we get to the 
     friend we want to delete
  **/

  FriendNode* currentNode = root;
  //if there are currently non friends, return
  if(!currentNode)
    return;
  //if root is the friend we are trying to delete, delete it and reassign the root
  if (currentNode->name == friendName)
    {
      root = currentNode->next;
      delete currentNode;
      return;
    }
  
  while (currentNode->next)
    {
      if (currentNode->next->name == friendName)
	{
	  FriendNode* temp = currentNode->next;
	  currentNode->next = currentNode->next->next;
	  delete temp;
	  return;
	}
      currentNode = currentNode->next;
    }
}




