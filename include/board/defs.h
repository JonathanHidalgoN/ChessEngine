#ifndef CONSTANTS_C
#define CONSTANTS_C

#include <stdint.h>
#include <stdio.h>

#define COLS 8
#define ROWS 8
#define NUMBEROFCOLORS 2
#define WHITE 0
#define BLACK 1
#define NUMBEROFDIFFERENTPIECES 6
#define PAWN 0
#define KING 1
#define QUEEN 2
#define BISHOP 3
#define KNIGHT 4
#define ROOK 5
#define EMPTY 6
#define NUMBEROFSQUARES (ROWS * COLS)
#define LASTBIT (NUMBEROFSQUARES - 1)
#define MAXTURNS 2048

typedef uint64_t bitboard;

typedef struct piece {
  int side;
  int type;
  int bitIndex;
} piece;

typedef struct gameState {
  int playingSide;
  int castlingCode;
  int halfMoveCounter;
  int enPassantCode;
  int fullMoveCounter;
  uint64_t zobristKey;
  int phaseValue;
} gameState;

typedef struct bitBoardsList {
  bitboard pieces[NUMBEROFCOLORS][NUMBEROFDIFFERENTPIECES];
} bitBoardsList;

#endif // !CONSTANTS_C
