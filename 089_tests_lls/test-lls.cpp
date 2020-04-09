#include <assert.h>
#include <cstdlib>
#include "il.h"
using namespace std;

void testList() {
  IntList list2;
  assert(list2.size == 0);
  assert(list2.head == NULL);
  assert(list2.tail == NULL);
  assert(list2.getSize() == 0);
  
  IntList list3 = list2;
  assert(list3.size == 0);
  assert(list3.head == NULL);
  assert(list3.tail == NULL);
  
  IntList list4(list2);
  assert(list4.size == 0);
  assert(list4.head == NULL);
  assert(list4.tail == NULL);
  
  
  for (int i = 0; i < 10; i++) {
    list2.addBack(i);
  }
  for (int i = 0; i < 10; i++) {
    assert(list2[i] == i);
  }
  
  
  list2[1] = 10;
  assert(list2[1] == 10);
  assert(list2.head->next->data == 10);
  list2[1] = 1;
  assert(list2.size == 10);
  assert(list2.getSize() == 10);
  IntList list_test = list2;
  list_test = list_test;
  for (int i = 0; i < 10; i++) {
    if (list_test[i] != i) {
      assert(0);
    }
  }
  
  
  assert(list_test.head != list2.head);
  assert(list_test.head->next != list2.head->next);
  assert(list_test.tail != list2.tail);
  assert(list_test.tail->next == NULL);
  assert(list_test.head->data == 0);
  assert(list_test.tail->data == 9);
  
  
  assert(list_test.size == 10);
  assert(list_test.head->next != list2.head->next);
  assert(list_test.tail->next == NULL);
  assert(list_test.head->prev == NULL);
  assert(list_test.tail->prev != list2.head->prev);
  

  assert(list_test.head->next->data == 1);
  assert(list_test.getSize() == list_test.size);
  assert(list_test.find(5) == 5);
  
  
  IntList list5(list2);
  
  
  assert(list5.head != list2.head);
  assert(list5.head->next != list2.head->next);
  assert(list5.tail != list2.tail);
  assert(list5.tail->next == NULL);
  assert(list5.head->data == 0);
  assert(list5.tail->data == 9);
  
  
  assert(list5.size == 10);
  assert(list5.head->next != list2.head->next);
  assert(list5.tail->next == NULL);
  assert(list5.head->prev == NULL);
  assert(list5.tail->prev != list2.head->prev);
  assert(list5.head->next->data == 1);
  assert(list5.getSize() == list_test.size);
  assert(list5.find(5) == 5);
  //-----------------------------------------------
  IntList list_test0;
  list_test0.addFront(1);
  assert(list_test0.head == list_test0.tail);
  assert(list_test0.head->next == NULL);
  assert(list_test0.tail->prev == NULL);
  
  
  list_test0[0] = 10;
  assert(list_test0[0] == 10);
  assert(list_test0.head->data == 10);
  list2[1] = 1;
	
  
  IntList list_test1(list_test0);
  assert(list_test0.size == list_test1.getSize());
  assert(list_test1.head != list_test0.head);
  assert(list_test1.tail != list_test0.tail);
  assert(list_test1.head == list_test1.tail);
  assert(list_test1.head->next == NULL);
  assert(list_test1.tail->next == NULL);
  assert(list_test1.head->prev == NULL);
  assert(list_test1.tail->prev == NULL);
  
  
  IntList list_test2 = list_test0;
  assert(list_test0.size == list_test2.getSize());
  assert(list_test2.head != list_test0.head);
  assert(list_test2.tail != list_test0.tail);
  assert(list_test2.head == list_test2.tail);
  assert(list_test2.head->next == NULL);
  assert(list_test2.tail->next == NULL);
  assert(list_test2.head->prev == NULL);
  assert(list_test2.tail->prev == NULL);
  
  
  list_test = list_test0;
  
  
  assert(list_test[0] == 10);
  assert(list_test.size == 1);
  assert(list_test.head != list_test0.head);
  assert(list_test.tail != list_test0.tail);
  assert(list_test.head == list_test.tail);
  assert(list_test.head->next == NULL);
  assert(list_test.tail->next == NULL);
  assert(list_test.head->prev == NULL);
  assert(list_test.tail->prev == NULL);
  
  
  //----------------------
  IntList list20;
  list20.addFront(4);
  list20.addFront(3);
  list20.addFront(2);
  list20.addFront(1);
  list20.addFront(0);
  assert(list20.find(3) == 3);
  assert(list20.size == 5);
  assert(list20.head->data == 0);
  assert(list20.tail->data == 4);
  
  
  for (int i = 0; i < 5; i++) {
    if (list20[i] != i)
      assert(0);
  }
  
  
  list20.remove(3);
  assert(list20.size == 4);
  assert(list20.getSize() == 4);
	
  
  //-----------------------
  IntList list30;
  list30.addFront(1);
  list30.addFront(1);
  list30.addFront(1);
  assert(list30.head->next->next == list30.tail);
  assert(list30.find(2) == -1);
  assert(list30.head->data == 1);
  assert(list30.tail->data == 1);
  
  
  for (int i = 0; i < 3; i++) {
    if (list30[i] != 1)
      assert(0);
  }
  
  
  list30.remove(1);
  assert(list30.size == 2);
  assert(list30.getSize() == 2);
	  //----------------------------
  IntList list40;
  list40.addBack(0);
  list40.addBack(1);
  list40.addBack(2);
  
  
  list40.remove(1);
  assert(list40.head->data == 0);
  assert(list40.tail->data == 2);
  assert(list40.getSize() == 2);
  assert(list40.size == 2);
  assert(list40.head->next == list40.tail);
  assert(list40.tail->prev == list40.head);
  
  
  IntList list50;
  list50.addBack(0);
  list50.addBack(1);
  list50.addBack(2);
  
  
  list50.remove(2);
  assert(list50.head->data == 0);
  assert(list50.tail->data == 1);
  assert(list50.getSize() == 2);
  assert(list50.size == 2);
  assert(list50.head->next == list50.tail);
  assert(list50.tail->prev == list50.head);
  assert(list50.head->next->next == NULL);
}


int main(void) {
  testList();
  return EXIT_SUCCESS;
}
