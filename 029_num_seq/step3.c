# include <stdio.h>
# include <stdlib.h>

int seq3(int x, int y);
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi);

int seq3(int x, int y){
  return x*y + 2*y -3*x;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi){
  int sum = 0;
  if (xLow >= xHi || yLow >= yHi){
    return sum;
  }
  else{
    for (int i = xLow; i < xHi; i++){
      for (int j = yLow; j < yHi; j++){
	if (seq3(i,j)%2 == 0){
	  sum += 1;
	}
      }
    }
  }
  return sum;
}


int main(void){
  printf("seq3(%d, %d) = %d\n", 2,3, seq3(2,3));
  printf("seq3(%d, %d) = %d\n", 5,-3, seq3(5,-3));
  printf("seq3(%d, %d) = %d\n", 1,6, seq3(1,6));
  printf("seq3(%d, %d) = %d\n", 2,3, seq3(2,3));
  printf("seq3(%d, %d) = %d\n", -2,4, seq3(-2,4));
  printf("seq3(%d, %d) = %d\n", 0,0, seq3(0,0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0,2,0,3, countEvenInSeq3Range(0,2,0,3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0,3,0,0, countEvenInSeq3Range(0,3,0,0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0,3,0,1, countEvenInSeq3Range(0,3,0,1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 5,2,0,3, countEvenInSeq3Range(5,2,0,3));
  return 0;
}



// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
