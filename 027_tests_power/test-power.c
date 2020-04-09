#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

int main(void){
  if ((power(1,1) == 1) && (power(2,2) == 4) && (power(111111,1) == 111111) && (power(-2,1)== -2)&& (power(321,0)==1)&&( power(1,10) == 1) && (power(2,10)==1024) && (power(-2,0)==1)&&(power(-2,2)== 4)&& (power(-1,10000)== 1) && (power(0,-1)== 0 ) && (power(0,0)==1) ) {
      return EXIT_SUCCESS;
       }else {
    return EXIT_FAILURE;
  }

    
}

