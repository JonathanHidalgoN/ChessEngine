#include "../include/board.h"
#include <stdint.h>
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

/*
 * -1 < col < 8, -1 < row < 8, so at max following col + (8) * row
 *  will be 7 + 56 = 63, and at min will be 0 so we can move the 1
 *  from the 0 to the 63 bit
 */
void placeBitValue(int col, int row, int val, bitboard *bb) {
  // COULD CHECK FOR VALID COORDS IN RANGE HERE
  uint64_t mask = (uint64_t)1 << (col + ROWS * row);
  if (!val) {
    *bb = *bb & ~mask;
  } else {
    *bb = *bb | mask;
  }
}
