#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
  for (int i = 0; i < count; i++){
    printf("%s", data[i]);
  }
}


int main(int argc, char ** argv) {
  size_t sz = 0;
  //ssize decide -1;
  size_t count = 0;
  size_t j = 0;
  char **line = NULL;
  char *curr = NULL;
  if (argc == 1){
    while (getline(&curr, &sz, stdin) >= 0){
      line = realloc(line, (j + 1) *sizeof(*line));
      line[j] = curr;
      curr = NULL;
      j++;
      count++;
    }
    free(curr);
    sortData(line, count);
    for (int i = 0; i < count; i++) { 
      free(line[i]);
    }
    free(line);
    return EXIT_SUCCESS;
  }
  else {
    for (int q = 1; q < argc; q++){
      FILE * f = fopen(argv[q], "r");
      //      printf("%d\n",argc);
      // printf("one f\n");
      if (f == NULL) {
	perror("Could not open file");
	return EXIT_FAILURE;
      }
        
      while (getline(&curr, &sz, f) >= 0){
	line = realloc(line, (j + 1) *sizeof(*line));
	line[j] = curr;
	curr = NULL;
	j++;
	count++;
      }
      free(curr);
      sortData(line, count);
      for (int i = 0; i < count; i++) { 
	free(line[i]);
      }
      free(line);
      line = NULL;
      sz = 0;
      curr = NULL;
      j = 0;
      count = 0;
      if (fclose(f) != 0) {
       	return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}


