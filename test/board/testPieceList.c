#include "../test.h"
#include <stdio.h>

int computeAndCompareUpdatePieceList(pieceList *expectedPieceList,
                                     bitBoardsList *bitBoardsList,
                                     char testNumber, char *functionName) {
  pieceList resultPieceList;
  updatePieceList(&resultPieceList, bitBoardsList);
  int areEqual = arePieceListEqual(expectedPieceList, &resultPieceList);
  if (!areEqual) {
    printf(RED "Error in %s, test number %c\n" RESET, functionName, testNumber);
    return 0;
  }
  return 1;
}

int testUpdatePieceList() {
  char *functionName = "updatePieceList";
  int i;
  bitBoardsList bitBoardsList;
  pieceList expectedPieceList;
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  // All bitboards full of 0's expect piece list full of emptys
  for (i = 0; i < NUMBEROFSQUARES; i++) {
    expectedPieceList.pieces[i] = EMPTY;
  }
  int c0 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '0', functionName);
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  // Put some pieces
  bitBoardsList.pieces[WHITE][PAWN] = BIT(0) + BIT(1);
  expectedPieceList.pieces[0] = PAWN;
  expectedPieceList.pieces[1] = PAWN;
  int c1 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '1', functionName);
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  // Test case 2 : Mix pieces
  bitBoardsList.pieces[WHITE][PAWN] = BIT(0) + BIT(2);
  expectedPieceList.pieces[0] = PAWN;
  expectedPieceList.pieces[2] = PAWN;
  bitBoardsList.pieces[BLACK][PAWN] = BIT(63) + BIT(55);
  expectedPieceList.pieces[63] = PAWN;
  expectedPieceList.pieces[55] = PAWN;
  bitBoardsList.pieces[BLACK][KING] = BIT(6) + BIT(5);
  expectedPieceList.pieces[6] = KING;
  expectedPieceList.pieces[5] = KING;
  int c2 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '2', functionName);
  // Test case 3: Multiple pieces of different types
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  bitBoardsList.pieces[WHITE][PAWN] = BIT(3);
  bitBoardsList.pieces[WHITE][KNIGHT] = BIT(5);
  expectedPieceList.pieces[3] = PAWN;
  expectedPieceList.pieces[5] = KNIGHT;
  int c3 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '3', functionName);

  // Test case 5: All pieces of one type
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  bitBoardsList.pieces[BLACK][ROOK] = BIT(0) + BIT(7) + BIT(56) + BIT(63);
  expectedPieceList.pieces[0] = ROOK;
  expectedPieceList.pieces[7] = ROOK;
  expectedPieceList.pieces[56] = ROOK;
  expectedPieceList.pieces[63] = ROOK;
  int c5 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '5', functionName);

  return c0 && c1 && c3 && c5 && c2;
}

void testPieceList() {
  int testUpdatePieceListResult = testUpdatePieceList();
  if (testUpdatePieceListResult) {
    printf(GREEN "Tested piece list successfully\n" RESET);
  }
}
