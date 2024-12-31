#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H
#include "../board/board.h"
#include "attacks.h"
#include <stdio.h>
piece findPieceByBitIndex(int bitIndex, pieceList *board);
bitboard computeLegalMoves(int bitIndex, pieceList *board);
bitboard computeSideBitBoard(int side, pieceList *board);
/**
 * Computes the pawn forward move
 */
bitboard computePawnForwardMove(int bitIndex, int side);
#endif
