#ifndef ATTACKS_H
#define ATTACKS_H
#include "../include/board.h"
#define BOARD_INDEX(row, col) ((col) + (ROWS * (row)))
bitboard computePawnAttack(int bitIndex, int side);
bitboard computeKnightAttack(int bitIndex);
bitboard computeKingAttack(int bitIndex);
void fillPawnAttackTable(
    bitboard pawnAttackTable[NUMBEROFCOLORS][NUMBEROFSQUARES]);
void fillKnightAttackTable(bitboard knightAttackTable[NUMBEROFSQUARES]);
void fillKingAttackTable(bitboard kingAttackTable[NUMBEROFSQUARES]);
#endif
