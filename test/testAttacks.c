#include "test.h"
#include <stdio.h>

int testPawnAttack() {
  bitboard bb = 0;
  bb = computePawnAttack(9, 1);
  if (bb != (1ULL << 0) + (1ULL << 2)) {
    printf("Error in function compute pawn attack case 0 \n");
    return 0;
  }
  return 1;
}

void testAttacks() {
  int resultTestPawnAttack = testPawnAttack();
  if (resultTestPawnAttack) {
    printf("Test attacks successfully \n");
  }
}
