#include <stdlib.h>
#include <stdio.h>

size_t  maxSeq(int * array, size_t n);

int main(void){
  int a[] = {};
  int b[] = {1,1,1,1,1,1,1};
  int c[] = {1,0,-1,0,1,0};
  int d[] = {300,1000,0,10,50000,1000000};
  int e[] = {1,100000,100001,-10000001,0,30};
  int f[] = {1};
  int g[] = {1,2,2,3,3,-1};
  int h[] = {2,2,2,3,3};
  int i[] = {1,2,3,4,5,6,7,-8,9};
  int j[] = {2,5,5,7,7,10,-10,3};
  int k[] = {1,-1,-3,498,5,6,-1,9};
  int aa[] = {1,2,2,4,4,6,-1,9};
  int bb[] = {1,2,2,4,4,6,-1,9};
  if (maxSeq(a, 0)==0 && maxSeq(b, 7)==1 && maxSeq(c,6)==3 && maxSeq(d,6)==4 && maxSeq(e,6)==3 && maxSeq(f,1)==1 && maxSeq(g,6)==2 && maxSeq(h,5)==2 && maxSeq(i,9)==7 && maxSeq(j,8)==2 && maxSeq(k,7)==2 && maxSeq(aa,8)==2&& maxSeq(bb,8)==2) {
    return EXIT_SUCCESS;
  }else{
    return EXIT_FAILURE;
  }

}
