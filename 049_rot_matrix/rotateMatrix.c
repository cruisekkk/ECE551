# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
void funcmatrix (FILE * f){
  char matrix[10][10];
  char line[12];
  int j = 0;  
  while (fgets(line,12,f) != NULL){  
    if (strlen(line) !=11){
      fprintf(stderr,"Line is too short or long !\n");
      exit(EXIT_FAILURE);
    };
    
    if ((line[10]!= '\n') || (line[11]!= '\0')){
      fprintf(stderr,"cannot find \\n \\0"); 
      exit(EXIT_FAILURE);
    };
 
    for (int i =0; i <=9; i++){
      matrix[j][i] = line[i];
      if  ((line[i] == '\n') || (line[i] == '\0')){
	//  if (line[i] == ' '){
  	fprintf(stderr,"null\n");
	exit(EXIT_FAILURE);
      }
    }
    j += 1;
  }
  
  if (j > 10 || j < 10){
    fprintf(stderr,"unmatched lines \n");
    exit(EXIT_FAILURE);
  };

  char new_matrix[10][10];
  for (int q = 0; q<=9;q++){
    for (int p = 0; p <= 9; p++){
      new_matrix[q][p] = matrix[9-p][q];
    }
  }

  for (int q = 0; q<=9;q++){
    for (int p = 0; p <= 9; p++){
      fprintf(stdout, "%c",new_matrix[q][p]);
    }
    fprintf(stdout,"\n");
  }
}


int main (int argc, char ** argv){
  if (argc != 2) {
    fprintf(stderr,"Usage: matrix inputFileName\n");
    return EXIT_FAILURE;
  };
  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  };
  // if (fgets(line,12,f) == NULL){
    // printf("null file\n");
    //  exit(EXIT_FAILURE);
    // }
  // fclose(f);

  funcmatrix(f);
  
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
}
