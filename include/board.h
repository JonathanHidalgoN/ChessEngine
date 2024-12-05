#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>

// Some useful constants
#define COLS 8
#define ROWS 8
#define NUMBEROFDIFFERENTPIECES 12
#define WHITEKING 1
#define WHITEPAWN 0
#define WHITEQUEEN 2
#define WHITEBISHOP 3
#define WHITEKNIGHT 4
#define WHITEROOK 5
#define BLACKPAWN 6
#define BLACKKING 7
#define BLACKQUEEN 8
#define BLACKBISHOP 9
#define BLACKKNIGHT 10
#define BLACKROOk 11

// Will be using a bitboard representation
typedef uint64_t bitboard;
void cleanBitboard(bitboard *bb);
void printBitboard(bitboard bb);
void placeBitValue(int col, int row, int val, bitboard *bb);
#endif
