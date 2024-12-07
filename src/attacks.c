#include "../include/attacks.h"

bitboard computePawnAttack(int row, int col, int side) {
  bitboard pawnAttack = 0;
  uint64_t mask = (uint64_t)1 << (col + ROWS * row);
  // side == 1 means black
  if (side) {

  } else {
    if (mask << 7)
      pawnAttack |= (mask << 7);
    if (mask << 9)
      pawnAttack |= (mask << 9);
  }
  return pawnAttack;
}
