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
#include "defs.h"

// Some useful constants
#define countBits(bitboard) __builtin_popcountll(bitboard)
#define fromBoardCordsToBitIndex(row, col) ((col) + ROWS * (row))
#define getLSBIndex(bitboard) ((bitboard) ? __builtin_ctzll(bitboard) : -1)
/**
 Set all pieces of the board to empty board
*/
void cleanChessBoard(chessBoard *chessBoard);
/**
  print the bitboard
 */
void printBitboard(bitboard bb);
/**
  Place the val in the bitIndex on the Bitboard
 */
void placeBitValue(int bitIndex, int val, bitboard *bb);
/**
  Init the chessBoard with the classic chess config
 */
void initChessBoard(chessBoard *chessBoard);
/**
  Create a string representation of the chessBoard
 */
void placePieceRepresentationIntoBoardString(bitboard bb, char *br,
                                             char symbol);
/**
  Print the chessBoard
 */
void printChessBoard(chessBoard *chessBoard);
#endif
