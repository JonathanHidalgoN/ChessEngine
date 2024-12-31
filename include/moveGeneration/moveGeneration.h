#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H
#include "../board/board.h"
#include "attacks.h"
#include <stdio.h>
piece findPieceByBitIndex(int bitIndex, bitBoardsList *board);
bitboard computeLegalMoves(int bitIndex, bitBoardsList *board);
bitboard computeSideBitBoard(int side, bitBoardsList *board);
/**
 * Computes the pawn forward move
 */
bitboard computePawnForwardMove(int bitIndex, int side);
#endif
