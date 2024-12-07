#include "../include/attacks.h"

// THIS CONST REPRESENT THE BOARD BELOW THEM
const bitboard NOT_COL_0 = 18374403900871474942ULL;
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0

const bitboard NOT_COL_7 = 9187201950435737471ULL;
// 0 1 1 1 1 1 1 1
// 0 1 1 1 1 1 1 1
// 0 1 1 1 1 1 1 1
// 0 1 1 1 1 1 1 1
// 0 1 1 1 1 1 1 1
// 0 1 1 1 1 1 1 1
// 0 1 1 1 1 1 1 1
// 0 1 1 1 1 1 1 1

bitboard computePawnAttack(int row, int col, int side) {
  bitboard pawnAttack = 0;
  uint64_t mask = (uint64_t)1 << (col + ROWS * row);
  // side == 1 means black
  if (side) {
    if (mask & NOT_COL_7)
      pawnAttack |= (mask >> 7);
    if (mask & NOT_COL_0)
      pawnAttack |= (mask >> 9);
  } else {
    if (mask & NOT_COL_0)
      pawnAttack |= (mask << 7);
    if (mask & NOT_COL_7)
      pawnAttack |= (mask << 9);
  }
  printBitboard(pawnAttack | mask);
  return pawnAttack;
}
