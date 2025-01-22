#include "../test.h"
#include <stdio.h>

// TODO : MOVE THIS TO UTILS
static bool computeAndCompareUpdatePieceList(pieceList *expectedPieceList,
                                             bitBoardsList *bitBoardsList,
                                             char testNumber,
                                             char *functionName) {
  pieceList resultPieceList;
  updatePieceList(&resultPieceList, bitBoardsList);
  int areEqual = arePieceListEqual(expectedPieceList, &resultPieceList);
  if (!areEqual) {
    printf(RED "Error in %s, test number %c\n" RESET, functionName, testNumber);
    return 0;
  }
  return 1;
}

static bool testUpdatePieceList() {
  char *functionName = "updatePieceList";
  int i;
  bitBoardsList bitBoardsList;
  pieceList expectedPieceList;
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  // All bitboards full of 0's expect piece list full of emptys
  for (i = 0; i < NUMBEROFSQUARES; i++) {
    expectedPieceList.pieces[i] = PIECE_EMPTY;
  }
  int c0 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '0', functionName);
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  // Put some pieces
  bitBoardsList.pieces[COLOR_WHITE][PIECE_PAWN] = BIT(0) + BIT(1);
  expectedPieceList.pieces[0] = PIECE_PAWN;
  expectedPieceList.pieces[1] = PIECE_PAWN;
  int c1 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '1', functionName);
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  // Test case 2 : Mix pieces
  bitBoardsList.pieces[COLOR_WHITE][PIECE_PAWN] = BIT(0) + BIT(2);
  expectedPieceList.pieces[0] = PIECE_PAWN;
  expectedPieceList.pieces[2] = PIECE_PAWN;
  bitBoardsList.pieces[COLOR_BLACK][PIECE_PAWN] = BIT(63) + BIT(55);
  expectedPieceList.pieces[63] = PIECE_PAWN;
  expectedPieceList.pieces[55] = PIECE_PAWN;
  bitBoardsList.pieces[COLOR_BLACK][PIECE_KING] = BIT(6) + BIT(5);
  expectedPieceList.pieces[6] = PIECE_KING;
  expectedPieceList.pieces[5] = PIECE_KING;
  int c2 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '2', functionName);
  // Test case 3: Multiple pieces of different types
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  bitBoardsList.pieces[COLOR_WHITE][PIECE_PAWN] = BIT(3);
  bitBoardsList.pieces[COLOR_WHITE][PIECE_KNIGHT] = BIT(5);
  expectedPieceList.pieces[3] = PIECE_PAWN;
  expectedPieceList.pieces[5] = PIECE_KNIGHT;
  int c3 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '3', functionName);

  // Test case 5: All pieces of one type
  cleanBitBoardList(&bitBoardsList);
  cleanPieceList(&expectedPieceList);
  bitBoardsList.pieces[COLOR_BLACK][PIECE_ROOK] = BIT(0) + BIT(7) + BIT(56) + BIT(63);
  expectedPieceList.pieces[0] = PIECE_ROOK;
  expectedPieceList.pieces[7] = PIECE_ROOK;
  expectedPieceList.pieces[56] = PIECE_ROOK;
  expectedPieceList.pieces[63] = PIECE_ROOK;
  int c5 = computeAndCompareUpdatePieceList(&expectedPieceList, &bitBoardsList,
                                            '5', functionName);

  return c0 && c1 && c3 && c5 && c2;
}

void testPieceList() {
  bool testUpdatePieceListResult = testUpdatePieceList();
  if (testUpdatePieceListResult) {
    printf(GREEN "Tested piece list successfully\n" RESET);
  }
}
