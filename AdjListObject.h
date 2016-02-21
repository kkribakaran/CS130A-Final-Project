#ifndef ADJLISTOBJECT_H
#define ADJLISTOBJECT_H
#include <string>

struct Node {
  std::string Name;
  Node* next;
};

class AdjListObject {
 public:
  AdjListObject{};
  std::string getName();
  int getProfileDataIndex();
  std::string setName();
  int setProfileDataIndex();
  void addFriend(std::string friend);
 private:
  std::string name;
  int profileDataIndex;
  Node* root;
};

#endif
