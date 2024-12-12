#include "test.h"
#include <stdio.h>

int testSetBitboard0() {
  bitboard bb = 1234;
  setBitboard0(&bb);
  if (bb) {
    printf("Error in function setBitboard0 \n");
    return 0;
  }
  bb = 0;
  setBitboard0(&bb);
  if (bb) {
    printf("Error in function setBitboard0 \n");
    return 0;
  }
  return 1;
}

int testPlaceBitValue() {
  bitboard bb = 0;
  placeBitValue(0, 0, &bb);
  if (bb) {
    printf("Error in function setbitvalue \n");
    return 0;
  }
  bb = 0;
  placeBitValue(0, 1, &bb);
  if (bb != 1ULL) {
    printf("Error in function setbitvalue \n");
    return 0;
  }
  bb = 1;
  placeBitValue(0, 0, &bb);
  if (bb) {
    printf("Error in function setbitvalue \n");
    return 0;
  }
  bb = 0;
  placeBitValue(3, 1, &bb);
  if (bb != 8) {
    printf("Error in function setbitvalue \n");
    return 0;
  }
  return 1;
}

int testBoard() {
  int resultTestSetBitboard0 = testSetBitboard0();
  int resultTestPlaceBitValue = testPlaceBitValue();
  if (resultTestSetBitboard0 && resultTestPlaceBitValue) {
    printf("Test board sucessfully \n");
    return 1;
  }
  return 0;
}
