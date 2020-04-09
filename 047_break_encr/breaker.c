#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int breaker(FILE * f){
  int c;
  int fre[26] = {0};
  //1. calculate the frequency number
  while ((c = fgetc(f)) != EOF){
    //if ((c >= 'a' && c <= 'z') || (c >= 'A'&& c <= 'Z')){
    // continue;
    //};
    if (isalpha(c)){
      c = tolower(c);
      //      printf("%c", c);
    };    
    for (int i = 0; i <=25; i++){
      if (c == i + 97){
	//	printf("yes");
	fre[i] += 1;
      };
    }
  }
  //2. second for loop,
  int maxfreq = 0;
  int maxi =0;
  for (int i = 0; i <=25; i++){
    if (fre[i] > maxfreq){
      maxfreq = fre[i];
      maxi = i;
    };
    //printf("%d\n",fre[i]);
  }

  //3. get N
  int key = 0;
  char N = 'a' + maxi;
  //  printf("%c", N);
  if (N >= 'e'){
    key = N - 'e';
  }
  else{
    key = N + 26 - 'e';
  }
  return key;
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  };
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  };
  printf("%d\n",breaker(f));
  if (breaker(f) > 26 || breaker(f) < 0){
    return EXIT_FAILURE;
  }; 
  
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
}
