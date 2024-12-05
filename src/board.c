#include "../include/board.h"
#include <stdio.h>

void cleanBitboard(bitboard *bb) { (*bb) = 0; }

/*
 * This function will print the board
 */
void printBitboard(bitboard bb) {
  int i, j;
  const int LASTBIT = 63;
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      uint64_t mask = (uint64_t)1 << (LASTBIT - (i * ROWS + j));
      char val = (mask & bb) != 0 ? '1' : '0';
      printf("%c ", val);
    }
    printf("\n");
  }
}
