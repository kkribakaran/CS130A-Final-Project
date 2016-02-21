#include "AdjListObject.h"
#include <string>

AdjListObject::AdjListObject() {
name = "";
profileDataIndex = -10;
root = NULL;
}

std::string getName() {
return name;
}

int getProfileDataIndex() {
return int;
}
void setName(std::string name) {
this->name = name; 
}
void setProfileDataIndex(int index) {
this->profileDataIndex = index;
}
void addFriend(std::string friend) {
Node* temp = root;
Node* friendNode;
friendNode.name = friend;
friendNode.next = NULL; 
while (temp->next) {
temp = temp->next;
}
temp->next = friendNode;
}

