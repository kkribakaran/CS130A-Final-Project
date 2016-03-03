#include "Btree.h"
#include <string>
using namespace std;

void Btree::insert(string name, int index)
{
  if (root = NULL)
  {
    Node* leafnode = new Node();
    Person *p = new Person();
    p->name = name;
    p->index = index; 
  }
  Node * temp = root;
  while (!temp->isLeaf) {
    if (name > temp->key[temp->keycount]) {
      temp = temp->children[temp->keycount + 1]
	}
    else { 
      for (int i = -1; i <temp->keycount; i++) {
	if (name < temp->key[i]) {
	  temp = temp->children[i]
	    break;
	}
      }
    }
  }
  Person *p = new Person();
  p->name = name;
  p->index = index;
  if (temp->leafCount ==3) {
    Node *n = new Node();
    n->isLeaf = true;
    n->
      }
  else {
    
    if (name < leaf[0].name) {
      leaf[2] = leaf[1];
      leaf[1] = leaf[0];
      leaf[0] = p;
    } else if (name < leaf[1].name) {
      leaf[2] = leaf[1];
      leaf[1] = p;
    } else {
      leaf[2] = p;
    }
  }
}



void Btree::rangeQuery(string a, string b)
{
  //TODO
}




void Btree::siftUp(Node * x, string name, Node * n) {
  if (x == NULL) {
    Node *k = new Node();
    k->isLeaf = false;

  }
  Node *p = x->parent;
  int i;
  for (i = 0; i < x->keycount; i++) {
    if (name < x->keys[i]) {
      break;
    }
  }
  for (int j = keycount + 1; j > i; j--) {
    x->children[j+1] = x->children[j];
    x->keys[j+1] = x->keys[j];
  }
  keycount++;
  if (keycount == 5) {
    Node *k = new Node();
    k->isLeaf = false;
    for (int j = 0; j < 2; j++) {
      k->children[j] = x->children[j+3];
      k->keys[j] = x->keys[j+3];
    }
    k->children[2] = x->children[5];
    k->keycount = 2;
    x->keycount = 2;
    if (p == NULL) {
      Node *parent = new Node();
      parent->isLeaf = false;
      x->parent = parent;
      k->parent = parent;
      parent->children[0] = x;
      parent->children[1] = k;
      parent->keys[0] = x->keys[2]
	root = parent;
    } else {
      string parentname = x->keys[2];

      siftUp(p,parentname,k);
    }

  }
}
