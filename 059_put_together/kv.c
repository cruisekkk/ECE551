#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


// openfile, split into key-value pairs, closefile, return an array {kvarray}
// need realloc 
kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  
  kvarray_t * lines = malloc(sizeof(*lines));
  lines->p = malloc(sizeof(*lines->p));
  char *curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    //lines-> p[0].value = "a";
    lines->p = realloc(lines->p,(i + 1) * sizeof(*lines->p));
    //printf("***\n%s\n***",curr);
    //printf("%s", kvline(curr).value);
    lines->p[i].key = strtok(curr, "=");
    lines->p[i].value = strtok(NULL, "\n");
    //printf("aaa %s", lines->p[i].value);
    curr = NULL;
    i++;
  }
  lines->length = i;
  free(curr);
  fclose(f);
  return lines;
}


// free every element and whole array
void freeKVs(kvarray_t * pairs) {
  //for (size_t j =0; j < pairs->length; j++){
  //  free(pairs->p[j]);
  // }
  //free(pairs);
  for (size_t i = 0; i < pairs->length; i++){
    free((char *)pairs->p[i].key);
    // key - value same place
  }
  free(pairs->p);
  free(pairs);
}


void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++){
    printf("key = '%s' value = '%s'\n", pairs->p[i].key, pairs->p[i].value);
  }
}


char * lookupValue(kvarray_t * pairs, const char * key) {
  char * y;
  for (size_t i = 0; i < pairs->length; i++){
    if (strcmp(pairs->p[i].key, key) == 0){
      y =(char *) pairs->p[i].value;
      return y;
    };
  }
  return NULL;
}
