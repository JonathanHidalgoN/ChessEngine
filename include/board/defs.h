// TODO: MOVE DEFS TO UPPER FILE LEVEL
#ifndef CONSTANTS_C
#define CONSTANTS_C

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define COLS 8
#define ROWS 8
#define NUMBEROFCOLORS 2
#define NUMBEROFDIFFERENTPIECES 6
#define NUMBEROFSQUARES (ROWS * COLS)
#define LASTBIT (NUMBEROFSQUARES - 1)
#define MAXTURNS 2048
#define countBits(bitboard) __builtin_popcountll(bitboard)
#define fromBoardCordsToBitIndex(row, col) ((col) + ROWS * (row))
#define getLSBIndex(bitboard) ((bitboard) ? __builtin_ctzll(bitboard) : -1)

typedef enum {
  PIECE_PAWN,
  PIECE_KING,
  PIECE_QUEEN,
  PIECE_BISHOP,
  PIECE_KNIGHT,
  PIECE_ROOK,
  PIECE_EMPTY,
} PIECE;

typedef enum { COLOR_WHITE, COLOR_BLACK } COLOR;

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
