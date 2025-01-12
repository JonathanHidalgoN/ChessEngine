// TODO: MOVE DEFS TO UPPER FILE LEVEL
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
#define countBits(bitboard) __builtin_popcountll(bitboard)
#define fromBoardCordsToBitIndex(row, col) ((col) + ROWS * (row))
#define getLSBIndex(bitboard) ((bitboard) ? __builtin_ctzll(bitboard) : -1)

typedef struct piece {
  int side;
  int type;
  int bitIndex;
} piece;

typedef struct intPair {
  int first;
  int second;
} intPair;

#endif // !CONSTANTS_C
