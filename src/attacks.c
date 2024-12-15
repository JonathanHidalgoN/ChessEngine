#include "../include/attacks.h"
#define DEBBUG 0

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

// Max number of possible attacks per square for example a rook in h1 can attack
// up to 12 squares
const int occupancyRookMap[NUMBEROFSQUARES] = {
    12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 11, 11, 11, 11, 11, 12,
    10, 9,  10, 11, 11, 11, 11, 12, 9,  8,  9,  10, 11, 11, 11, 12,
    8,  7,  8,  9,  10, 11, 11, 12, 7,  6,  7,  8,  9,  10, 11, 12,
    6,  5,  6,  7,  8,  9,  10, 12, 6,  5,  6,  7,  8,  9,  10, 12};
const int occupancyBishopMap[NUMBEROFSQUARES] = {
    6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7,
    5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7,
    7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};

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

bitboard computeBishopAttack(int bitIndex, bitboard blockers) {
  bitboard attacks = 0;
  int col = bitIndex % COLS;
  int row = bitIndex / ROWS;
  int i, j;
  for (i = col + 1, j = row + 1; i <= 7 && j <= 7; i++, j++) {
    attacks |= (1ULL << (j * ROWS + i));
    if ((1ULL << (j * ROWS + i)) & blockers)
      break;
  }
  for (i = col - 1, j = row + 1; i >= 0 && j <= 7; i--, j++) {
    attacks |= (1ULL << (j * ROWS + i));
    if ((1ULL << (j * ROWS + i)) & blockers)
      break;
  }
  for (i = col + 1, j = row - 1; i <= 7 && j >= 0; i++, j--) {
    attacks |= (1ULL << (j * ROWS + i));
    if ((1ULL << (j * ROWS + i)) & blockers)
      break;
  }
  for (i = col - 1, j = row - 1; i >= 0 && j >= 0; i--, j--) {
    attacks |= (1ULL << (j * ROWS + i));
    if ((1ULL << (j * ROWS + i)) & blockers)
      break;
  }
  if (DEBBUG) {
    uint64_t mask = (uint64_t)1 << bitIndex;
    printBitboard(attacks | mask);
  }
  return attacks;
}

bitboard computeRookAttack(int bitIndex, int blockers) {
  bitboard attacks = 0;
  int col = bitIndex % COLS;
  int row = bitIndex / ROWS;
  int i, j;
  // Same as bishop, will be used in magic bitboard implementation
  for (i = col + 1; i <= 7; i++) {
    attacks |= (1ULL << (row * ROWS + i));
    if ((1ULL << (row * ROWS + i)) & blockers)
      break;
  }
  for (i = col - 1; i >= 0; i--) {
    attacks |= (1ULL << (row * ROWS + i));
    if ((1ULL << (row * ROWS + i)) & blockers)
      break;
  }
  for (j = row + 1; j <= 7; j++) {
    attacks |= (1ULL << (j * ROWS + col));
    if ((1ULL << (j * ROWS + col)) & blockers)
      break;
  }
  for (j = col - 1; j >= 0; j--) {
    attacks |= (1ULL << (j * ROWS + col));
    if ((1ULL << (j * ROWS + col)) & blockers)
      break;
  }
  if (DEBBUG) {
    uint64_t mask = (uint64_t)1 << bitIndex;
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
  // Same as bishop, will be used in magic bitboard implementation
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

/* Given an attack mask this computes all the possible permutations(turn or or
off a bit on attack mask) up to an index for example if we have this attack mask
for a rook on a1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0
x 1 1 1 1 1 1 0
We have 12 bits in the mask with n bits we can represent from 0 to 2**n - 1
thats why you will see 2**n -1 in the index
This function will compute the index permutations of the board show above
source :
https://www.youtube.com/watch?v=gaXLyW-yMvg&list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs&index=13
*/
bitboard setOccupancy(int index, int bitsInMask, bitboard attackMask) {
  // TODO : Here is some wasted computation benchmark maybe is worth to optimize
  bitboard occupancy = 0;
  for (int i = 0; i < bitsInMask; i++) {
    int bitIndex = getLSBIndex(attackMask);
    placeBitValue(bitIndex, 0, &attackMask);
    if (index & (1 << i))
      occupancy |= (1ULL << bitIndex);
  }
  return occupancy;
}
