/*
 * Bitboard Representation:
 *
 * Board is arranged from least significant bit (LSB) to most significant bit
 * (MSB) 64-bit representation, mapping as follows:
 *
 * Bit 0  (LSB) = a1
 * Bit 1        = b1
 * Bit 2        = c1
 * ...
 * Bit 7        = h1
 * Bit 8        = a2
 * Bit 9        = b2
 * ...
 * Bit 63 (MSB) = h8
 *
 * Indexing follows row-major order:
 * - Lowest 8 bits (0-7)   represent first rank (row 1)
 * - Next 8 bits (8-15)    represent second rank (row 2)
 * - ...
 * - Highest 8 bits (56-63) represent eighth rank (row 8)
 */
#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>

// Some useful constants
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

// Will be using a bitboard representation
typedef uint64_t bitboard;
typedef struct chessBoard {
  bitboard pieces[NUMBEROFCOLORS][NUMBEROFDIFFERENTPIECES];
} chessBoard;
void setBitboard0(bitboard *bb);
void printBitboard(bitboard bb);
void placeBitValue(int col, int row, int val, bitboard *bb);
void initChessBoard(chessBoard *chessBoard);
#endif
