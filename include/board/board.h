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
#include "boardEncoding.h"
#include "defs.h"
#include "history.h"
#include "pieceList.h"

typedef struct board {
  bitBoardsList bitBoardsList;
  gameState gameState;
  history history;
  zobristRandoms zobristRandoms;
  pieceList pieceList;
} board;

void removePiece(board *board, int square, int side, int piece);
void putPiece(board *board, int square, int side, int piece);
// NOTE: this do not eat the piece where its going
void movePiece(board *board, int from, int to, int side, int piece);
void resetEnPassant(board *board);
#endif
