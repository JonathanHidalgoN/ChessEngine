#include "test.h"
#include <stdio.h>

int testPawnAttack(int bitIndex, int side, bitboard result, char testNumber) {
  bitboard bb = computePawnAttack(bitIndex, side);
  if (bb != result) {
    printf("Error in function compute pawn attack case %c \n", testNumber);
    return 0;
  }
  return 1;
}

int testPawnAttacks() {
  int c0 = testPawnAttack(9, 1, (1ULL << 0) + (1ULL << 2), '0');
  int c1 = testPawnAttack(1, 1, 0, '1');
  int c2 = testPawnAttack(0, 0, (1ULL << 9), '2');
  int c3 = testPawnAttack(7, 0, (1ULL << 14), '3');
  int c4 = testPawnAttack(56, 1, (1ULL << 49), '4');
  int c5 = testPawnAttack(63, 1, (1ULL << 54), '5');
  int c6 = testPawnAttack(54, 0, (1ULL << 63) + (1ULL << 61), '6');
  return c1 & c0 & c3 & c2 & c4 & c5 & c6;
}

void testAttacks() {
  int resultTestPawnAttack = testPawnAttacks();
  if (resultTestPawnAttack) {
    printf("Test attacks successfully \n");
  }
}
