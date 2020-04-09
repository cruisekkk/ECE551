#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define CLICK_KNOWN_MINE -2
#define CLICK_INVALID -1
#define CLICK_CONTINUE 0
#define CLICK_LOSE 1

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

#define IS_MINE(x) ((x) == HAS_MINE || (x) == KNOWN_MINE)

struct _board_t {
  int ** board;
  int width;
  int height;
  int totalMines;
};

typedef struct _board_t board_t;

void addRandomMine(board_t * b) {
  int x;
  int y;
  //we could have a board too small for the number
  //of mines taht we request. try w*h*10 times before
  //we give up
  int limit = b->width * b->height * 10;
  do {
    x = random() % b->width;
    y = random() % b->height;
    assert(limit > 0);
    limit--;
  } while (b->board[y][x] == HAS_MINE);
  b->board[y][x] = HAS_MINE;
}

board * makeBoard(int w, int h, int numMines){
  board_t * p = malloc(sizeof(*p));
  p -> width = w;
  p -> height = h;
  p -> totalMines = numMines;
  p -> board = malloc(h*sizeof(*board)); 
  for (int j = 0; j < h; j++){
    p -> board[j] = malloc(w*sizeof(**board));
    for (int i = 0; i < w; i++){
      p -> board[j][i] = UNKNOWN;
    }
  }
  for (int m = 0; m < numMines; m++){
    addRandomMine(p);
  }
  
  return p;
}


  
  // *int =  malloc(w*sizeof(int))

int countMines(board_ t * b, int x, int y){
  int count = 0;
  for (int dy = -1; dy <=1 ; dy++) {
    for (int dx = -1; dx <=1 ; dx++) {
      if (dx == 0 && dy == 0){
	continue;
      }
      else {
	int nx = x + dx;
	int ny = y + dy;
	if (nx >= 0 && nx < b->width &&
	    ny >= 0 && ny < b->height) {
	  if (b->board[ny][nx] == KNOWN_MINE || b->board[ny][nx] == HAS_MINE){
	    count++;
	  };
	};
      }
    }
  }
  return count;
}	
	
// dir[8][2] = {{1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1}};      

int checkWin(board_t * b) {
  for (int i = 0; i < b->height; i++){
    for (int j = 0; j < b->weight; j++){
      if (b->board[i][j] == UNKNOWN){
	return 0;
      } 
    }
  }
  return 1;
}

void freeBoard(board_t * b) {
  for (int i = 0; i < b->height; i++){ 
    free(b->board[i]);
  }
  free(b)->board;
}
