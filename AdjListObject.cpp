#include "AdjListObject.h"
#include <string>

AdjListObject::AdjListObject()
{
  name = "";
  profileDataIndex = -10;
  root = NULL;
}

std::string AdjListObject::getName()
{
  return name;
}

int AdjListObject::getProfileDataIndex() 
{
  return int;
}

void AdjListObject::setName(std::string name) 
{
  this->name = name; 
}

void AdjListObject::setProfileDataIndex(int index) 
{
  this->profileDataIndex = index;
}

void AdjListObject::addFriend(std::string friend) 
{
  Node* temp = root;
  Node* friendNode;
  friendNode.name = friend;
  friendNode.next = NULL; 
  while (temp->next) 
    {
      temp = temp->next;
    }
  temp->next = friendNode;
}

