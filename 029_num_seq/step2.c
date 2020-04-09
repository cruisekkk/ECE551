# include <stdio.h>
# include <stdlib.h>

int seq2(int x);
int sumSeq2(int low, int high);

int seq2(int x){
  if (x % 4 ==2 || (-x)%4 ==2){
    return 2*x;
  }
  else{
    return x*x + 3*x +1;
  }
}

int sumSeq2(int low, int high){
  int sum = 0;
  if (high <= low){
    return 0;
  }
  for (int i = low; i < high; i++){
    sum += seq2(i);
  }
  return sum;
}


int main(void){
  printf("seq2(%d) = %d\n", 5, seq2(5));
  printf("seq2(%d) = %d\n", 12, seq2(12));
  printf("seq2(%d) = %d\n", 0, seq2(0));
  printf("seq2(%d) = %d\n", -8, seq2(-8));
  printf("seq2(%d) = %d\n", -2, seq2(-2));
  printf("sumSeq2(%d, %d) = %d\n", 0,0, sumSeq2(0,0));
  printf("sumSeq2(%d, %d) = %d\n", 0,1, sumSeq2(0,1));
  printf("sumSeq2(%d, %d) = %d\n", 0,-2, sumSeq2(0,-2));
  printf("sumSeq2(%d, %d) = %d\n", 0,5, sumSeq2(0,5));
  printf("sumSeq2(%d, %d) = %d\n", -4,0, sumSeq2(-4,0));
  printf("sumSeq2(%d, %d) = %d\n", 5,10, sumSeq2(5,10));
  

  return 0;
}



// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
