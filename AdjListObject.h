#ifndef ADJLISTOBJECT_H
#define ADJLISTOBJECT_H
#include <string>


//This class represents a single entry of the Adjacency List
class AdjListObject 
{
  
 public:
  
  // This node represents a friend in the linked list
  struct FriendNode 
  {
    std::string name;
    FriendNode* next;
  };
  //constructors
  AdjListObject();
  AdjListObject(std::string name, int profileDataIndex);
  
  //getters and setters
  std::string getName();
  int getProfileDataIndex();
  FriendNode* getRoot();
  void setName(std::string name);
  void setProfileDataIndex(int index);

  //adds a friend to the linked list
  void addFriend(std::string friendName);
  
 private:

  /**
     Each entry has a name, a number to represent its index in
     the profile Data, and a pointer to the root of its linked list 
     of friends
  **/
  std::string name;
  int profileDataIndex;
  FriendNode* root;
};

#endif
