#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...
// des
state_t parseLine(const char * line) {
  // step 1:
  char * sta = malloc(1 + strlen(line) * sizeof(*line));
  strcpy(sta, line);
  sta[strlen(line) * sizeof(*line)] = '\0';
  state_t state;
  char * namet;
  uint64_t popt;
  char * poptc;
  unsigned int elet;
  char * eletc;
  int j = 0;
  for (int i = 0; i < strlen(sta); i++) {
    if (sta[i] == ':') {
      j++;
      if (i == 0 || i == (strlen(sta) - 1)) {
        fprintf(stderr, "error1\n");
        exit(EXIT_FAILURE);
      };
      if (sta[i] == sta[i - 1]) {
        fprintf(stderr, "error2\n");
        exit(EXIT_FAILURE);
      }
    };
  }
  if (j != 2) {
    fprintf(stderr, "error3\n ");
    exit(EXIT_FAILURE);
  };

  // pass the data into struct
  namet = strtok(sta, ":");
  poptc = strtok(NULL, ":");
  eletc = strtok(NULL, ":");

  // check
  for (int i = 0; i < strlen(poptc); i++) {
    if (poptc[i] < '0' || poptc[i] > '9') {
      fprintf(stderr, "error4\n ");
      exit(EXIT_FAILURE);
    };
  }
  for (int i = 0; i < strlen(eletc); i++) {
    if (eletc[i] < '0' || eletc[i] > '9') {
      free(sta);
      fprintf(stderr, "error5\n ");
      exit(EXIT_FAILURE);
    };
  }
  popt = atoi(poptc);
  elet = atoi(eletc);

  strcpy(state.name, namet);

  state.population = popt;
  state.electoralVotes = elet;
  free(sta);
  return state;
}

/*
//
//


 */


unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int count = 0;
  // loop for each state
  for (int i = 0; i < nStates; i++) {
    if (stateData[i].population - voteCounts[i] < voteCounts[i]) {
      count = count + stateData[i].electoralVotes;
    }
  }

  return count;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  //double percentage;
  for (int i = 0; i < nStates; i++) {
    double percentage = voteCounts[i] / (double)stateData[i].population;
    if ((percentage >= 0.495) && (percentage <= 0.505)) {
      //percentage = voteCounts[i] / stateData[i].population;
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             percentage * 100);
    };
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  int j = 0;
  double large = 0;
  for (int i = 0; i < nStates; i++) {
    // calculate percentage
    double percentage = voteCounts[i] / (double)stateData[i].population;
    if (percentage > large) {
      large = percentage;
      j = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[j].name, large * 100);
}
