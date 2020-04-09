#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "ff_shell.h"

int main() {
  ff_shell shell;
  // directly go into the input processing of my shell
  // .input method is the entrance of my object 'shell'
  shell.input();
  // after processing, return out
  return EXIT_SUCCESS;
}
