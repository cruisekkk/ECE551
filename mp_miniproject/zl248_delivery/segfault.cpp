#include <cstdio>
#include <iostream>


int main(void){
  int a[3] = {1,2,3};
  std::cout << a[1000000] << std::endl;
  return EXIT_SUCCESS;
}
