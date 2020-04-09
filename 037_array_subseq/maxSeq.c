#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int * array, size_t n);

size_t maxSeq(int * array, size_t n){
  int length = 1;
  int current_large =1;
  if (n ==0){
    length = 0;
    return length;
  }
  if (n ==1){
    return length;
  }
  else{
    for (int i = 0; i < n-1; i++){
      if (array[i] < array[i+1]){
	length++;
	if (length > current_large){
	  current_large = length;}
      }
      else{
	length=1;
      }
    }
  }
  return current_large;
}
