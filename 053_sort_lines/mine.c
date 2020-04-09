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
  p -> numMines = totalMines;

  //p -> *board = malloc(h *sizeof(*board));
  //p -> **board = malloc(w * sizeof(**board));
  
  for (int j = 0; j < h; j++){
    for (int i = 0; i < w; i++){
      
      p -> board[j][i] = UNKNOWN;
    }
  }
  
  
  // *int =  malloc(w*sizeof(int))


}
