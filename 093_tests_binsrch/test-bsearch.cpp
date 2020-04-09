#include <stdlib.h>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

extern int binarySearchForZero(Function<int, int> * f, int low, int high);
class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(const char * m) : mesg(m) {}
  virtual int Finvoke(int arg) = 0;
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return Finvoke(arg);
  }
  void check(int low, int high, int expect, int runtime) {
    int ans = 0;
    remaining = runtime;
    ans = binarySearchForZero(this, low, high);
    if (ans != expect) {
      std::cerr << "Search result wrong in " << mesg << ", should be " << expect << "now:"<< ans<< std::endl;
      exit(EXIT_FAILURE);
    }
  }
};

class y_xFunction : public CountedIntFn
{
 public:
  y_xFunction() : CountedIntFn("y = x") {}
  virtual int Finvoke(int arg) { return arg; }
};

class SinFunction : public CountedIntFn
{
 public:
  SinFunction() : CountedIntFn("y = sin(x)") {}
  virtual int Finvoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

int main() {
  SinFunction().check(0, 150000, 52359, 20);
  y_xFunction().check(-1, 10, 0, 4);
  y_xFunction().check(-2, 0, -1, 2);
}
