#ifndef ATTACKS_H
#define ATTACKS_H
#include "../include/board.h"
#define BOARD_INDEX(row, col) ((col) + (ROWS * (row)))
bitboard computePawnAttack(int row, int col, int side);
bitboard computeKingAttack(int row, int col);
#endif
