#include "../test.h"
#include <stdio.h>

int computeAndCompareUpdatePieceList(pieceList *expectedPieceList,
                                     bitBoardsList *bitBoardsList,
                                     char testNumber, char *functionName) {
  pieceList resultPieceList;
  updatePieceList(&resultPieceList, bitBoardsList);
  int areEqual = arePieceListEqual(expectedPieceList, &resultPieceList);
  if (!areEqual) {
    printf("Error in %s, test number %c\n", functionName, testNumber);
    return 0;
  }
  return 1;
}

int testUpdatePieceList() {
  char *functionName = "updatePieceList";
  bitBoardsList bitBoardsList;
  cleanBitBoardList(&bitBoardsList);
  // All bitboards full of 0's expect piece list full of emptys
  pieceList expectedPieceList;
  for (int i = 0; i < NUMBEROFSQUARES; i++) {
    expectedPieceList.pieces[i] = EMPTY;
  }
  int c0 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '0', functionName);
  return c0;
}

void testPieceList() {
  int testUpdatePieceListResult = testUpdatePieceList();
  if (testUpdatePieceListResult) {
    printf("Tested piece list successfully\n");
  }
}
