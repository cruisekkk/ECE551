#include <stdlib.h>
#include <stdio.h>

unsigned power(unsigned x, unsigned y);

unsigned power(unsigned x, unsigned y){
  int n = 1;
  if (y == 0) {
    if (x==0){
      return 1;
    }
    return n;
      }else{
    
    if (y > 0){
      n = x;
      return n*(power(x,y-1));
	}else{
      n = x;
      return n*(power(x,y+1));
    }
  }
}
 
