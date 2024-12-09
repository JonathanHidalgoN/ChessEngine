#include "../include/attacks.h"
#define DEBBUG 1

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

// This follows the logic above but with rows
const bitboard NOT_ROW_0 = 18446744073709551360ULL;
const bitboard NOT_ROW_7 = 72057594037927935ULL;

bitboard computePawnAttack(int row, int col, int side) {
  bitboard attack = 0;
  uint64_t mask = (uint64_t)1 << BOARD_INDEX(row, col);
  // side == 1 means black
  if (side) {
    if (mask & NOT_COL_7)
      attack |= (mask >> 7);
    if (mask & NOT_COL_0)
      attack |= (mask >> 9);
  } else {
    if (mask & NOT_COL_0)
      attack |= (mask << 7);
    if (mask & NOT_COL_7)
      attack |= (mask << 9);
  }
  if (DEBBUG) {
    printBitboard(attack | mask);
  }
  return attack;
}

bitboard computeKingAttack(int row, int col) {
  bitboard attack = 0;
  uint64_t mask = (uint64_t)1 << BOARD_INDEX(row, col);

  if (DEBBUG) {
    printBitboard(attack | mask);
  }
  return attack;
}
