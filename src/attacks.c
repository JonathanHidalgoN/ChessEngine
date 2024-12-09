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

const bitboard NOT_COL_01 = 18229723555195321596ULL;
const bitboard NOT_COL_67 = 4557430888798830399ULL;
// This follows the logic above but with rows
const bitboard NOT_ROW_0 = 18446744073709551360ULL;
const bitboard NOT_ROW_7 = 72057594037927935ULL;
const bitboard NOT_ROW_67 = 281474976710655ULL;
const bitboard NOT_ROW_01 = 18446744073709486080ULL;

bitboard computePawnAttack(int bitIndex, int side) {
  bitboard attacks = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  // side == 1 means black
  if (side) {
    attacks |= ((mask >> 7) & NOT_COL_7);
    attacks |= ((mask >> 9) & NOT_COL_0);
  } else {
    attacks |= (mask << 7) & NOT_COL_7;
    attacks |= (mask << 9) & NOT_COL_0;
  }
  if (DEBBUG) {
    printBitboard(attacks | mask);
  }
  return attacks;
}
bitboard computeKnightAttack(int bitIndex) {
  bitboard attacks = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  // attacks |= (bitboard <<7) & notAFile;
  attacks |= (mask >> 17) & NOT_COL_0;
  // attacks |= (mask ) &;
  // attacks |= (mask) &;
  // attacks |= (mask) &;
  // attacks |= (mask) &;
  // attacks |= (mask) &;
  // attacks |= (mask) &;
  // attacks |= (mask) &;
  if (DEBBUG) {
    printBitboard(attacks | mask);
  }
  return attacks;
}

void fillPawnAttackTable(
    bitboard pawnAttackTable[NUMBEROFCOLORS][NUMBEROFSQUARES]) {
  for (int i = 0; i < NUMBEROFCOLORS; i++) {
    for (int j = 0; j < NUMBEROFSQUARES; j++) {
      pawnAttackTable[i][j] = computePawnAttack(j, i);
    }
  }
}
