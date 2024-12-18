#include "test.h"
#include <stdio.h>
#define DEBUG 1

void showDiff(bitboard expected, bitboard result) {
  if (DEBUG) {
    printf("------------------------------------------------------");
    printf("\n Expected board \n");
    printBitboard(expected);
    printf("\n\n Result\n");
    printBitboard(result);
    printf("------------------------------------------------------");
    printf("\n");
  }
}

int testPawnAttack(int bitIndex, int side, bitboard result, char testNumber) {
  bitboard bb = computePawnAttack(bitIndex, side);
  if (bb != result) {
    printf("Error in function compute pawn attack case %c \n", testNumber);
    showDiff(bb, result);
    return 0;
  }
  return 1;
}

int testKnightAttack(int bitIndex, bitboard result, char testNumber) {
  bitboard bb = computeKnightAttack(bitIndex);
  if (bb != result) {
    printf("Error in function compute knight attack case %c \n", testNumber);
    showDiff(bb, result);
    return 0;
  }
  return 1;
}

int testKingAttack(int bitIndex, bitboard result, char testNumber) {
  bitboard bb = computeKingAttack(bitIndex);
  if (bb != result) {
    printf("Error in function compute King attack case %c \n", testNumber);
    showDiff(bb, result);
    return 0;
  }
  return 1;
}

int testRookAttack(int bitIndex, bitboard board, bitboard result,
                   char testNumber) {
  bitboard bb = computeRookAttack(bitIndex, board);
  if (bb != result) {
    printf("Error in function compute Rook attacks case %c \n", testNumber);
    showDiff(bb, result);
    return 0;
  }
  return 1;
}

int testRookAttacks() {
  bitboard bb = 0ULL;
  int c0 = testRookAttack(0, bb, 72340172838076926ULL, '0');
  int c1 = testRookAttack(7, bb, 9259542123273814143ULL, '1');
  int c2 = testRookAttack(56, bb, 18302911464433844481ULL, '2');
  int c3 = testRookAttack(63, bb, 9187484529235886208ULL, '3');
  return c0 && c1 && c2 && c3;
}

int testPawnAttacks() {
  int c0 = testPawnAttack(9, 1, (1ULL << 0) + (1ULL << 2), '0');
  int c1 = testPawnAttack(1, 1, 0, '1');
  int c2 = testPawnAttack(0, 0, (1ULL << 9), '2');
  int c3 = testPawnAttack(7, 0, (1ULL << 14), '3');
  int c4 = testPawnAttack(56, 1, (1ULL << 49), '4');
  int c5 = testPawnAttack(63, 1, (1ULL << 54), '5');
  int c6 = testPawnAttack(54, 0, (1ULL << 63) + (1ULL << 61), '6');
  return c1 && c0 && c3 && c2 && c4 && c5 && c6;
}

int testKnightAttacks() {
  int c0 = testKnightAttack(0, (1ULL << 17) + (1ULL << 10), '0');
  int c1 = testKnightAttack(7, (1ULL << 22) + (1ULL << 13), '1');
  int c2 = testKnightAttack(56, (1ULL << 50) + (1ULL << 41), '2');
  int c3 = testKnightAttack(63, (1ULL << 46) + (1ULL << 53), '3');
  return c0 && c1 && c2 && c3;
}

int testKingAttacks() {
  int c0 = testKingAttack(0, (1ULL << 1) + (1ULL << 8) + (1ULL << 9), '0');
  int c1 = testKingAttack(7, (1ULL << 6) + (1ULL << 15) + (1ULL << 14), '1');
  int c2 = testKingAttack(56, (1ULL << 57) + (1ULL << 48) + (1ULL << 49), '2');
  int c3 = testKingAttack(63, (1ULL << 62) + (1ULL << 55) + (1ULL << 54), '3');
  return c0 && c1 && c2 && c3;
}

void testAttacks() {
  int resultTestPawnAttack = testPawnAttacks();
  int resultTestKnightAttack = testKnightAttacks();
  int resultTestKingAttack = testKingAttacks();
  int resultTestRookAttack = testRookAttacks();
  if (resultTestPawnAttack && resultTestKnightAttack && resultTestKingAttack &&
      resultTestRookAttack) {
    printf("Test attacks successfully \n");
  }
}
