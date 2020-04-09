#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

// allocate mem for counts_t
// initialize
counts_t * createCounts(void) {
  counts_t * s = malloc(sizeof(*s));
  //s->p = malloc(sizeof(*s->p));
  s->p = NULL;
  s->nump = 0;
  s->numunk = 0;
  return s;
}

// incre count for name
// count for unkown when name = null
void addCount(counts_t * c, const char * name) {
  if (name == NULL){
    c->numunk++;
  }
  else{
    if (c->p == NULL){
      c->p = malloc(sizeof(*c->p));
      c->p[0].name = malloc((strlen(name)+1) * sizeof(*c->p[0].name)); 
      //strcpy(c->p[0].name, (char *)name);
      for (int i = 0; i <= strlen(name); i++){
	c->p[0].name[i] = name[i];
      }
      c->p[0].c = 1;
      c->nump = 1;
    }
    else{
      int cc = 0;
      for (int i = 0; i < c->nump; i++){
	if (strcmp(c->p[i].name,name) == 0){
	  c->p[i].c++;
	  cc++;
	};
      }
      if (cc == 0){
	c->nump++;
	c->p = realloc(c->p,c->nump * sizeof(*c->p));
	c->p[c->nump - 1].name = (char *) name;
	c->p[c->nump - 1].c = 1;
      };
    }
  }
}


// print information to outfile
void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->nump; i++){
    fprintf(outFile, "%s: %d\n", c->p[i].name, c->p[i].c);
  }
  if (c->numunk > 0){
    fprintf(outFile, "<unknown> : %ld\n",c->numunk);
  };
}


void freeCounts(counts_t * c) {
  //for (int i =0; i < c->nump; i++){
  // free(c->p[i].name);
  //}
  free(c->p[0].name);
  free(c->p);
  free(c);
}
