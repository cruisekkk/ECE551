#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream f(fname);

  uint64_t * ans;
  ans = new uint64_t[257]();  
  for (int i = 0; i < 257; i++){
    ans[i] = 0; // 对象是0，内置不一定
  }
  int c = f.get();
  
  while (f.good()){
    ans[c]++;//unsigned
    //(unsigned char)
    //(uint64_t)
    c = f.get();
  }
  if (c == -1){
    ans[256] = 1;
    //std::cout << "haha" << std::endl;
  }
  f.close();
  return ans;
  
  //FILE * f;     //c
  //f = fopen(fname, "r");
}
