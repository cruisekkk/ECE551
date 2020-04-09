#include <exception>
#include <iostream>

#include "map.h"

template<typename K, typename V>
  class BstMap : public Map<K, V>{
 private:
  class Node{
  public:
    K key;
    V value;
    Node * left;
    Node * right;
  Node(const K & key, const V & value): key(key), value(value),left(NULL),right(NULL){};
  };
  Node * root;
 public:
 BstMap(): root(NULL){};
  virtual ~BstMap<K,V>(){
    destroy(root);
    root = NULL;
  }

  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }
  // recursion
  Node * add(const K & key, const V & value, Node * root){
    Node * curr = root;
    if(curr==NULL){ // base case
      curr = new Node(key, value);
    }
    else if(key > curr->key){
      curr->right = add(key,value,curr->right);   
    }
    else if(key < curr->key){
      curr->left = add(key,value,curr->left); 
    }
    else{
      curr->value = value;
    }
    return curr;
  }
  
  virtual void add(const K & key, const V & value){
    root = add(key, value, root);
  }
  
  // pointer to pointer
  /*
   virtual void add(const K & key, const V & value){
    Node ** curr = &root;
    while (*curr != NULL){
      if (key > (*curr)->key){
	curr = &(*curr)->right;
      }
      else if (key < (*curr)->key){
	curr = &(*curr)->left;
      }
      else{
	(*curr)->value = value;
	return;
      }
    }
    *curr = new Node(key,value);
  }
  */
  
  virtual const V & lookup(const K& key) const throw (std::invalid_argument){
    Node * curr = root;
    while (curr != NULL){
      if (curr->key < key){
	curr = curr->right;
      }
      else if (curr->key > key){
	curr = curr->left;
      }
      else {
	//curr = curr->right
	return curr->value;
      }
    }
    throw std::invalid_argument("The key is not found!");
  }
  
  Node * remove(const K& key, Node * root){
    if (root == NULL){
      return NULL;
    }
    if (key == root->key){
      if (root->left == NULL){
	Node * temp = root->right;
	delete root;
	root = temp;
      }
      else if (root->right == NULL){
	Node * temp = root->left;
	delete root;
	root = temp;
      }
      else {
	Node * find_big = root->left;
	while(find_big->right != NULL){
	  find_big = find_big->right;
	}
	root->key = find_big->key;
	root->value = find_big->value;	
	root->left = remove(find_big->key, root->left); // qian muti
      }
    }
    else if (key > root->key){
      root->right = remove(key,root->right);
    }
    else if (key < root->key){
      root->left = remove(key,root->left);
    }
    return root;
  }

  virtual void remove(const K& key){
    root = remove(key, root);
  }

  void inorder_printer() {inorder_printer(root);}
  
  void inorder_printer(Node * root){
    if (root!=NULL){
      inorder_printer(root->left);
      std::cout<< root->key << " ";
      inorder_printer(root->right);
    }
  }
};
