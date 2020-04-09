# include <stdlib.h>
# include <stdio.h>

int seq1(int x);
void printSeq1Range(int low, int high);

int seq1(int x){
  int y = x * 4 -3;
  return y;
}

void printSeq1Range(int low, int high){
  if (high <= low){
    printf("\n");
  }
  else{
    for (int i = low; i < high - 1 ; i++){
      printf("%d, ", seq1(i));
    }
    printf("%d\n", seq1(high-1));
  }
}



int main(void){
  int y1 = seq1(3);
  int y2 = seq1(5);
  printf("seq1(%d) = %d\n",3,y1);
  printf("seq1(%d) = %d\n",5,y2);
  int low1 = -2;
  int high1 = 6;
  int low2 = 0;
  int high2 = 0;
  int low3 = 3;
  int high3 = 4;
  printf("printSeq1Range(%d, %d)\n", low1,high1);
  printSeq1Range(low1,high1);
  printf("printSeq1Range(%d, %d)\n", low2,high2);
  printSeq1Range(low2,high2);
  printf("printSeq1Range(%d, %d)\n", low3,high3);
  printSeq1Range(low3,high3);

  return 0;
}

// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
