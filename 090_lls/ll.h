#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <iostream>
//YOUR CODE GOES HERE
template<typename T>
class LinkedList{
 private:
  class Node{
  public:
    T data;
    Node * next;
    Node * previous;
  Node(const T & item): data(item), next(NULL), previous(NULL){}
  };
  int size;
  Node * head;
  Node * tail;
 public:
  //int size;
  // 1: constructor
 LinkedList(): size(0), head(NULL), tail(NULL){}
  // 2: addFront
  void addFront(const T &item){
    if (head == NULL){ // size = 0
      head = new Node(item);
      tail = head;
      size = 1;
    }
    else{
      head->previous = new Node(item);
      head->previous->next = head; 
      head = head->previous;
      size++;
    }
  }
  // 3: addBack
  void addBack(const T &item){
    if (tail == NULL){ // size = 0
      head = new Node(item);
      tail = head;
      size = 1;
    }
    else{
      tail->next = new Node(item);
      tail->next->previous = tail;
      tail = tail->next;
      size++;
    }
  }
  // 4: remove
  bool remove(const T &item){
    Node * temp = head;
    while (temp!= NULL){
      if (item == temp->data){
	temp->previous->next = temp->next;
	temp->next->previous = temp->previous;
	delete temp;
	size--;
	return true;
      }
      temp = temp->next;
    }
    return false;
  }
  // 5: index
  T& operator[](int index){
    if (index < 0 || index >= size){
      throw std::exception();
    };
    Node * temp = head;
    int i = 0;
    while (i != index){
      i++;
      temp = temp->next;
    }
    return temp->data;
  }
  // 6: const index
  T& operator[](int index) const{
    if (index < 0 || index >= size){
      throw std::exception();
    };
    Node * temp = head;
    int i = 0;
    while (i != index){
      i++;
      temp = temp->next;
    }
    return temp->data;
  }
  //7: find index
  int find(const T &item) const{
    Node * temp = head;
    int i = 0;
    while(temp!= NULL){
      if (temp->data == item){
	return i;
      }
      i++;
      temp = temp->next;
    }
    return -1;
  }
  //8: getsize
  int getSize() const{
    return size;
  }
  
  //9: copy constructor
 LinkedList(const LinkedList& rhs) : size(0), head(NULL), tail(NULL) {
    int s = rhs.getSize();
    for (int i = 0; i < s; i++){
      this->addBack(rhs[i]);
    }
  }
  
  //10: operator=
  LinkedList& operator=(const LinkedList& rhs){
    if (this!=rhs){
      while(head != NULL){
	Node temp = head->next;
	delete head;
	head = temp;
      }
      int s = rhs.getSize();
      for (int i = 0; i < s; i++){
	this->addBack(rhs[i]);
      } 
    }
    return *this;
  }
  
  //11: destructor
  ~LinkedList(){
    while(head!=NULL){
      Node* temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }
};




#endif
