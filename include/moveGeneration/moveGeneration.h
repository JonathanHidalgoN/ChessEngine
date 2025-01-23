#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H
#include "../board/board.h"
#include "attacks.h"
#include <stdio.h>
piece findPieceByBitIndex(int bitIndex, const bitBoardsList *board);
bitboard computeLegalMoves(int bitIndex, const bitBoardsList *board);
bitboard computeSideBitBoard(int side, const bitBoardsList *board);
/**
 * Computes the pawn forward move
 */
bitboard computePawnForwardMove(int bitIndex, COLOR side, bool firstMove);
#endif
