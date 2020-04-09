#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL){
    exit(EXIT_FAILURE);
  };
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while ((len = getline(&line, &sz, f))>=0){
    //printf()
    line[strlen(line)-1] = '\0';
    char * name = lookupValue(kvPairs,line);
    //printf("%s***%s*****%s\n", name,line, kvPairs->p[0].value);
    addCount(c, name);  
  }
  //printf("%ld\n", c->numunk);
  //printf("%ld\n", c->nump);
  free(line);
  fclose(f);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <=2){
    fprintf(stderr,"Usage: inputFileName\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i =2; i < argc; i++){
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    //printf("%ld", c->nump);
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }  
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
