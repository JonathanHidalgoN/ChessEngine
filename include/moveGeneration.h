#ifndef MOVE_GENERATION_H
#define MOVE_GENERATION_H
#include "../include/attacks.h"
#include "../include/board.h"
#include <stdio.h>
piece findPieceByBitIndex(int bitIndex, chessBoard *board);
bitboard computeLegalMoves(int bitIndex, chessBoard *board);
bitboard computeSideBitBoard(int side, chessBoard *board);
/**
 * Computes the pawn forward move
 */
bitboard computePawnForwardMove(int bitIndex, int side);
#endif
