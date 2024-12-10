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

// Same logic wont put all the boards
const bitboard NOT_COL_7 = 9187201950435737471ULL;
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
    attacks |= (mask >> 7) & NOT_COL_0;
    attacks |= (mask >> 9) & NOT_COL_7;
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
  attacks |= (mask << 17) & NOT_COL_0;
  attacks |= (mask << 10) & NOT_COL_01;
  attacks |= (mask << 15) & NOT_COL_7;
  attacks |= (mask << 6) & NOT_COL_67;
  attacks |= (mask >> 17) & NOT_COL_7;
  attacks |= (mask >> 10) & NOT_COL_67;
  attacks |= (mask >> 15) & NOT_COL_0;
  attacks |= (mask >> 6) & NOT_COL_01;
  if (DEBBUG) {
    printBitboard(attacks | mask);
  }
  return attacks;
}

bitboard computeKingAttack(int bitIndex) {
  bitboard attacks = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  attacks |= computePawnAttack(bitIndex, 0);
  attacks |= computePawnAttack(bitIndex, 1);
  attacks |= (mask << 1) & NOT_COL_0;
  attacks |= (mask >> 1) & NOT_COL_7;
  attacks |= (mask << 8) & NOT_ROW_0;
  attacks |= (mask >> 8) & NOT_ROW_7;
  if (DEBBUG) {
    printBitboard(attacks | mask);
  }
  return attacks;
}

bitboard maskBishopAttack(int bitIndex) {
  bitboard attacks = 0;
  int col = bitIndex % COLS;
  int row = bitIndex / ROWS;
  int i, j;
  // This is short by 1 square but this bitboard will be use in magic
  // bitboard right now I dont fully undertand how it works for now I will
  // implement by myself as much as I can and copy the rest
  for (i = col + 1, j = row + 1; i <= 6 && j <= 6; i++, j++) {
    attacks |= (1ULL << (j * ROWS + i));
  }
  for (i = col - 1, j = row + 1; i >= 1 && j <= 6; i--, j++) {
    attacks |= (1ULL << (j * ROWS + i));
  }
  for (i = col + 1, j = row - 1; i <= 6 && j >= 1; i++, j--) {
    attacks |= (1ULL << (j * ROWS + i));
  }
  for (i = col - 1, j = row - 1; i >= 1 && j >= 1; i--, j--) {
    attacks |= (1ULL << (j * ROWS + i));
  }
  if (DEBBUG) {
    uint64_t mask = (uint64_t)1 << bitIndex;
    printBitboard(attacks | mask);
  }
  return attacks;
}

bitboard maskRookAttack(int bitIndex) {
  bitboard attacks = 0;
  int col = bitIndex % COLS;
  int row = bitIndex / ROWS;
  int i, j;
  // Same as bishop, will be used in magic printBitboard
  for (i = col + 1; i <= 6; i++) {
    attacks |= (1ULL << (row * ROWS + i));
  }
  for (i = col - 1; i >= 1; i--) {
    attacks |= (1ULL << (row * ROWS + i));
  }
  for (j = row + 1; j <= 6; j++) {
    attacks |= (1ULL << (j * ROWS + col));
  }
  for (j = col - 1; j >= 1; j--) {
    attacks |= (1ULL << (j * ROWS + col));
  }
  if (DEBBUG) {
    uint64_t mask = (uint64_t)1 << bitIndex;
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

void fillKnightAttackTable(bitboard knightAttackTable[NUMBEROFSQUARES]) {
  for (int j = 0; j < NUMBEROFSQUARES; j++) {
    knightAttackTable[j] = computeKnightAttack(j);
  }
}

void fillKingAttackTable(bitboard kingAttackTable[NUMBEROFSQUARES]) {
  for (int j = 0; j < NUMBEROFSQUARES; j++) {
    kingAttackTable[j] = computeKingAttack(j);
  }
}
