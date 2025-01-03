#include "../test.h"
#include <stdio.h>

int testPlaceBitValue() {
  bitboard bb = 0;
  placeBitValue(0, 0, &bb);
  if (bb) {
    printf(RED "Error in function setbitvalue case 0 \n" RESET);
    return 0;
  }
  bb = 0;
  placeBitValue(0, 1, &bb);
  if (bb != 1ULL) {
    printf(RED "Error in function setbitvalue case 1 \n" RESET);
    return 0;
  }
  bb = 1;
  placeBitValue(0, 0, &bb);
  if (bb) {
    printf(RED "Error in function setbitvalue case 2\n" RESET);
    return 0;
  }
  bb = 0;
  placeBitValue(3, 1, &bb);
  if (bb != 8) {
    printf(RED "Error in function setbitvalue case 3\n" RESET);
    return 0;
  }
  return 1;
}

void testBoard() {
  int resultTestPlaceBitValue = testPlaceBitValue();
  if (resultTestPlaceBitValue) {
    printf(GREEN "Tested board sucessfully \n" RESET);
  }
}
