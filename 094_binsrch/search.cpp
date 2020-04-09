#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high) {
    std::cerr << "lower boundry is greater than upper boundry" << std::endl;
    exit(EXIT_FAILURE);
  }
  int mid = low;
  while (low < high - 1) {
    mid = (low + high)/2;
    int value = f->invoke(mid);
    if (value==0){
      return mid;
    }
    else if (value > 0){
      high = mid;
    }
    else{
      low = mid;
    }
  }
  return low;
}
