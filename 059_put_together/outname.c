#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * out = malloc((strlen(inputName)+8) * sizeof(*out));
  for (size_t i = 0; i <= strlen(inputName); i++){
    out[i] = inputName[i];
  }
  memcpy(out + strlen(inputName), ".counts", 8);
  return out;
}
