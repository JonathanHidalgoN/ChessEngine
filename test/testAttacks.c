#include "test.h"
#include <stdio.h>
#define DEBUG 1
#define BIT(n) (1ULL << (n))

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

int testBishopAttack(int bitIndex, bitboard board, bitboard result,
                     char testNumber) {
  bitboard bb = computeBishopAttack(bitIndex, board);
  if (bb != result) {
    printf("Error in function compute bishop attacks case %c \n", testNumber);
    showDiff(bb, result);
    return 0;
  }
  return 1;
}

int testBishopAttacks() {
  // empty board
  bitboard bb = 0ULL;
  int c0 = testBishopAttack(0, bb, 9241421688590303744ULL, '0');
  int c1 = testBishopAttack(7, bb, 72624976668147712ULL, '1');
  int c2 = testBishopAttack(56, bb, 567382630219904ULL, '2');
  int c3 = testBishopAttack(63, bb, 18049651735527937ULL, '3');
  // with blockers
  bb = BIT(9);
  int c4 = testBishopAttack(0, bb, BIT(9), '4');
  bb = BIT(14);
  int c5 = testBishopAttack(7, bb, BIT(14), '5');
  bb = BIT(49);
  int c6 = testBishopAttack(56, bb, BIT(49), '6');
  bb = BIT(54);
  int c7 = testBishopAttack(63, bb, BIT(54), '7');
  return c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7;
}

int testRookAttacks() {
  // empty board
  bitboard bb = 0ULL;
  int c0 = testRookAttack(0, bb, 72340172838076926ULL, '0');
  int c1 = testRookAttack(7, bb, 9259542123273814143ULL, '1');
  int c2 = testRookAttack(56, bb, 18302911464433844481ULL, '2');
  int c3 = testRookAttack(63, bb, 9187484529235886208ULL, '3');
  int c4 = testRookAttack(20, bb, 1157442765423841296, '4');
  // With blockers
  bb = BIT(1) + BIT(8);
  int c5 = testRookAttack(0, bb, BIT(1) + BIT(8), '5');
  bb = BIT(6) + BIT(15);
  int c6 = testRookAttack(7, bb, BIT(6) + BIT(15), '6');
  bb = BIT(57) + BIT(48);
  int c7 = testRookAttack(56, bb, BIT(57) + BIT(48), '7');
  bb = BIT(62) + BIT(55);
  int c8 = testRookAttack(63, bb, BIT(62) + BIT(55), '8');
  bb = BIT(19) + BIT(21) + BIT(28) + BIT(12);
  int c9 = testRookAttack(20, bb, BIT(19) + BIT(21) + BIT(28) + BIT(12), '9');
  bb = BIT(31) + BIT(45) + BIT(21);
  int c10 = testRookAttack(29, bb, 35325554458624, 'a');
  return c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8 && c9 && c10;
}

int testPawnAttacks() {
  int c0 = testPawnAttack(9, 1, BIT(0) + BIT(2), '0');
  int c1 = testPawnAttack(1, 1, 0, '1');
  int c2 = testPawnAttack(0, 0, BIT(9), '2');
  int c3 = testPawnAttack(7, 0, BIT(14), '3');
  int c4 = testPawnAttack(56, 1, BIT(49), '4');
  int c5 = testPawnAttack(63, 1, BIT(54), '5');
  int c6 = testPawnAttack(54, 0, BIT(63) + BIT(61), '6');
  return c1 && c0 && c3 && c2 && c4 && c5 && c6;
}

int testKnightAttacks() {
  int c0 = testKnightAttack(0, BIT(17) + BIT(10), '0');
  int c1 = testKnightAttack(7, BIT(22) + BIT(13), '1');
  int c2 = testKnightAttack(56, BIT(50) + BIT(41), '2');
  int c3 = testKnightAttack(63, BIT(46) + BIT(53), '3');
  return c0 && c1 && c2 && c3;
}

int testKingAttacks() {
  int c0 = testKingAttack(0, BIT(1) + BIT(8) + BIT(9), '0');
  int c1 = testKingAttack(7, BIT(6) + BIT(15) + BIT(14), '1');
  int c2 = testKingAttack(56, BIT(57) + BIT(48) + BIT(49), '2');
  int c3 = testKingAttack(63, BIT(62) + BIT(55) + BIT(54), '3');
  return c0 && c1 && c2 && c3;
}
void testAttacks() {
  int resultTestPawnAttack = testPawnAttacks();
  int resultTestKnightAttack = testKnightAttacks();
  int resultTestKingAttack = testKingAttacks();
  int resultTestRookAttack = testRookAttacks();
  int resultTestBishopAttack = testBishopAttacks();
  if (resultTestPawnAttack && resultTestKnightAttack && resultTestKingAttack &&
      resultTestRookAttack && resultTestBishopAttack) {
    printf("Test attacks successfully \n");
  }
}
