#ifndef __BSTSET_H__
#define __BSTSET_H__
#include "set.h"

template<typename T>
class BstSet : public Set<T>
{
 private:
  class Node
  {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & key) : key(key), left(NULL), right(NULL) {}
  };
  Node * root;
  void copyTree(Node ** root, const Node * rhsroot) {
    if (rhsroot != NULL) {
      *root = new Node(rhsroot->key);
      copyTree(&(*root)->left, rhsroot->left);
      copyTree(&(*root)->right, rhsroot->right);
    }
  }

  void freeTree(Node * root) {
    if (root != NULL) {
      freeTree(root->left);
      freeTree(root->right);
      delete root;
    }
  }

 public:
  BstSet() : root(NULL) {}

  BstSet(const BstSet & rhs) : root(NULL) { copyTree(&root, rhs.root); }

  virtual ~BstSet() { freeTree(root); }

  const BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet temp(rhs);
      Node * t = root;
      root = temp.root;
      temp.root = t;
    }
    return *this;
  }

  virtual void add(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key == (*curr)->key) {
        return;
      }
      else if (key > (*curr)->key) {
        curr = &(*curr)->right;
      }
      else {
        curr = &(*curr)->left;
      }
    }
    *curr = new Node(key);
  }

  virtual bool contains(const T & key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return true;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    return false;
  }

  virtual void remove(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key == (*curr)->key) {
        break;
      }
      else if (key > (*curr)->key) {
        curr = &(*curr)->right;
      }
      else {
        curr = &(*curr)->left;
      }
    }
    if (*curr == NULL) {
      return;
    }

    Node * temp = *curr;
    if ((*curr)->right == NULL) {
      (*curr) = (*curr)->left;
    }
    else if ((*curr)->left == NULL) {
      (*curr) = (*curr)->right;
    }
    else {
      Node ** nearest = &(*curr)->right;
      while ((*nearest)->left != NULL) {
        nearest = &(*nearest)->left;
      }
      (*curr)->key = (*nearest)->key;
      temp = *nearest;
      *nearest = (*nearest)->right;
    }
    delete temp;
  }
};

#endif
