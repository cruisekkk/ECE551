#include <cassert>
#include <iostream>

#include "bstset.h"

int main() {
  BstSet<int> test1;
  test1.add(60);
  test1.add(19);
  test1.add(93);
  test1.add(4);
  test1.add(25);
  //  assert(test1.contains(60));
  //assert(!test1.contains(2));
  BstSet<int> test2;
  test2 = test1;
  test2.remove(19);
  //  std::cout << test1 << std::endl;
}
