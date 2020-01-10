#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

typedef unsigned long UL;

/*
#define SIZE 5

#define PIECES 12

#define WIDTH 10

#define HEIGHT 6
*/

vector<string> sols;
int numPieces = 0;
vector<int> lastPiece;
vector<int> chosen;
int SIZE;
int WIDTH;
int HEIGHT;
int PIECES;
UL *boardPieces = NULL;

#define TO_CELL(x, y) (WIDTH * (y) + (x))
#define TO_BOARD(x, y) ((UL)1 << TO_CELL(x, y))
#define BOARD_MAX ((UL)1 << (WIDTH * HEIGHT))
#define BOARD_FULL (BOARD_MAX - 1)
#define FIND_SET_BIT(b) ((b) & -(b))
#define BOARD_SHIFT_LEFT(board, X) ((board) >> (X))
#define BOARD_SHIFT_RIGHT(board, X) ((board) << (X))
#define BOARD_SHIFT_UP(board, Y) ((board) >> (WIDTH * (Y)))
#define BOARD_SHIFT_DOWN(board, Y) ((board) << (WIDTH * (Y)))
#define BOARD_LEFT					\
  (TO_BOARD(0,0) | TO_BOARD(0,1) | TO_BOARD(0,2) |	\
   TO_BOARD(0,3) | TO_BOARD(0,4) | TO_BOARD(0,5))

#define BOARD_RIGHT BOARD_SHIFT_RIGHT(BOARD_LEFT, WIDTH - 1)
#define BOARD_TOP							\
  (TO_BOARD(0,0)|TO_BOARD(1,0)|TO_BOARD(2,0)|TO_BOARD(3,0)|TO_BOARD(4,0)| \
   TO_BOARD(5,0)|TO_BOARD(6,0)|TO_BOARD(7,0)|TO_BOARD(8,0)|TO_BOARD(9,0))

#define BOARD_BOTTOM BOARD_SHIFT_DOWN(BOARD_TOP, HEIGHT - 1)
#define IS_LEFT(board) ((board) & BOARD_LEFT)
#define IS_RIGHT(board) ((board) & BOARD_RIGHT)
#define IS_BOTTOM(board) ((board) & BOARD_BOTTOM)
#define IS_TOP(board) ((board) & BOARD_TOP)

UL normalize (UL board){
  assert (board);
  while (!IS_LEFT(board)) board = BOARD_SHIFT_LEFT(board, 1);
  while (!IS_TOP(board)) board = BOARD_SHIFT_UP(board, 1);
  return board;
}

UL rotate (UL board) {
  UL rotated = 0;
  for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < SIZE; y++)
      if (board & TO_BOARD(x, y))
	rotated |= TO_BOARD((SIZE - 1) - y, x);
  return normalize (rotated);
}

UL flipX (UL board) {
  UL flipped = 0, mask = BOARD_LEFT;
  for (int x = 0; x < WIDTH; x++, mask = BOARD_SHIFT_RIGHT(mask, 1)) {
    UL col = BOARD_SHIFT_LEFT(board & mask, x);
    flipped |= BOARD_SHIFT_RIGHT(col, (WIDTH - 1) - x);
  }
  return flipped;
}

UL flipY (UL board) {
  UL flipped = 0, mask = BOARD_TOP;
  for (int y = 0; y < HEIGHT; y++, mask = BOARD_SHIFT_DOWN(mask, 1)) {
    UL row = BOARD_SHIFT_UP(board & mask, y);
    flipped |= BOARD_SHIFT_DOWN(row, (HEIGHT - 1) - y);
  }
  return flipped;
}

UL piecetobits (const string piece) {
  UL bits = 0;
  for (int x = 0; x < SIZE; x++)
    for (int y = 0; y < SIZE; y++)
      if (piece[x + SIZE * y] != '-')
	bits |= TO_BOARD(x,y);
  return bits;
}

void printboard() {
  int piece;
  ostringstream os;

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      UL bit = TO_BOARD(x, y);
      char c = '-';
      for (piece = 0; piece < PIECES; piece++) {
        if (boardPieces[chosen[piece]] & bit) {
          c = 'a' + piece;
          break;
        }
      }
      os << c;
    }
  }
  sols.push_back(os.str());
}

static void addtemplate (UL board)
{
  if (!numPieces)
    boardPieces = (UL *) malloc (sizeof (UL));
  else
    boardPieces = (UL *) realloc (boardPieces, (1 + numPieces) * sizeof (UL));
  boardPieces[numPieces++] = board;
}

static int symmetric (int n, UL board)
{
  const UL flippedX = flipX (board), flippedY = flipY (board);
  board = flipY (flippedX);
  for (; n < numPieces; n++)
    if (boardPieces[n] == flippedX ||
	boardPieces[n] == flippedY ||
	boardPieces[n] == board)
      return 1;
  return 0;
}

static void addtoboard (int piece, UL board)
{
  const int n = numPieces;

  for (;; board = BOARD_SHIFT_RIGHT(board, 1)) {
    UL yboard;
    for (yboard = board;; yboard = BOARD_SHIFT_DOWN(yboard, 1)) {
      if (piece > 0 || !symmetric (n, yboard))
	addtemplate (yboard);
      if (IS_BOTTOM(yboard)) break;
    }
    if (IS_RIGHT(board)) break;
  }

  lastPiece[piece] = numPieces;
}

static void piecestobits ()
{
  static const string pieces[PIECES]= {
    "aaaaa--------------------",
    "bbbb-b-------------------",
    "cccc--c------------------",
    "d----ddd--d--------------",
    "-e---eee--e--------------",
    "--f--fff--f--------------",
    "-g---ggg---g-------------",
    "hhh--h-h-----------------",
    "iii--ii------------------",
    "jjj--j----j--------------",
    "kk----kk----k------------",
    "l----ll----l----l--------"
  };

  for (int i = 0; i < PIECES; ++i) {
    int j, k = 0;
    UL rotated[8];
    UL last = piecetobits (pieces[i]);
    rotated[k] = last;
    for (j = 1; j < 4; j++) {
      int l;
      last = rotate (last);
      for (l = 0; l <= k && rotated[l] != last; l++);
      if (l > k) rotated[k = l] = last;
      else break;
    }
    for (j = 0; j <= k; j++) {
      int l;
      last = normalize (flipY (rotated[j]));
      for (l = 0; l <= k && rotated[l] != last; l++);
      if (l > k)
	rotated[k = l] = last;
    }

    for (j = 0; j <= k; j++)
      addtoboard (i, rotated[j]);
  }
}

static int
fill (UL* board, UL dot)
{
  int filled = 0;
  UL queue = 0;

  for (;;) {
    UL mask = *board | (BOARD_LEFT | BOARD_MAX);


    for (;;) {
      UL right = BOARD_SHIFT_RIGHT(dot, 1);
      filled++;
      if (mask & right)
	break;
      dot |= right;
    }
    *board |= dot;
    queue |= BOARD_SHIFT_DOWN(dot & ~BOARD_BOTTOM, 1);
    queue |= BOARD_SHIFT_UP(dot & ~BOARD_TOP, 1);
    if (!(queue &= ~*board)) {
      return filled;
    }

    dot = FIND_SET_BIT(queue);
    mask = BOARD_SHIFT_RIGHT(*board, 1) | BOARD_LEFT;
    while (!(dot & mask))
      dot = BOARD_SHIFT_LEFT(dot, 1);
  }
}

int prune (UL board) {
  do
    if (fill (&board, FIND_SET_BIT(~board)) % SIZE)
      return 1;
  while (board != BOARD_FULL);
  return 0;
}

void dfs (int piece, UL board) {
  if(piece != PIECES){
    int i;
    if (prune (board))
      return;
    for (i = lastPiece[piece - 1]; i < lastPiece[piece]; i++)
      if (!(board & boardPieces[i]))
        dfs (piece + 1, board | (boardPieces[chosen[piece] = i]));
  }
  else{
    printboard ();
  }
}

static void dfs2 (int i) {
  for (chosen[0] = i; chosen[0] < lastPiece[0]; chosen[0]++)
    dfs (1, boardPieces[chosen[0]]);
}

int main() {
  piecestobits ();
  dfs2 (0);
  cout << sols.size() << '\n';
  for(string i : sols) cout << i << '\n';
  return 0;
}
