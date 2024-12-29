#ifndef CONSTANTS_C
#define CONSTANTS_C

#include <stdint.h>
#define COLS 8
#define NUMBEROFCOLORS 2
#define ROWS 8
#define WHITE 0
#define BLACK 1
#define NUMBEROFDIFFERENTPIECES 6
#define PAWN 0
#define KING 1
#define QUEEN 2
#define BISHOP 3
#define KNIGHT 4
#define ROOK 5
#define NUMBEROFSQUARES (ROWS * COLS)
#define LASTBIT (NUMBEROFSQUARES - 1)

typedef uint64_t bitboard;

typedef struct piece {
  int side;
  int type;
  int bitIndex;
} piece;

// Will be using a bitboard representation
// TODO: change name to piece list or something like that
typedef struct chessBoard {
  bitboard pieces[NUMBEROFCOLORS][NUMBEROFDIFFERENTPIECES];
} chessBoard;
#endif // !CONSTANTS_C
