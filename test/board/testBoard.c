#include "../test.h"
#include <stdio.h>

static BOOL testPlaceBitValue() {
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

static BOOL testCleanGameState() {
  const char *FUNCTION_NAME = "cleanGameState";
  // Zobrist keys will be tested alone
  const uint64_t ZOBRIST_KEY = 0ULL;
  BOOL expectedToFail = FALSE;
  board result;
  gameState expectGS = {WHITE, NO_CASTLING, 0, NO_PASSANT, 0, ZOBRIST_KEY, 0};
  cleanGameState(&result);
  result.gameState.zobristKey = ZOBRIST_KEY;
  BOOL c0 = compareGameStates(&expectGS, &result.gameState, FUNCTION_NAME, '0',
                              expectedToFail);
  return c0;
}

static BOOL testInitBoard() {
  const char *FUNCTION_NAME = "initBoard";
  BOOL expectedToFail = FALSE;
  board result, expected;
  initBoard(&result);
  // Have to use this or reset state used to compute random zobrist
  // can't use matchBoardsToTest because call to initBoard function
  expected.zobristRandoms = result.zobristRandoms;
  cleanBitBoardList(&expected.bitBoardsList);
  cleanPieceList(&expected.pieceList);
  cleanHistory(&expected.history);
  cleanGameState(&expected);
  expected.gameState.zobristKey = computeZobristFromState(
      &expected.zobristRandoms, &expected.bitBoardsList,
      expected.gameState.playingSide, expected.gameState.castlingCode,
      expected.gameState.enPassantCode);
  BOOL c0 =
      compareBoards(&expected, &result, FUNCTION_NAME, '0', expectedToFail);
  return c0;
}

static void matchBoardsToTest(board *board1, board *board2) {
  zobristRandoms zobrist;
  fillZobristRandoms(&zobrist);
  initBoard(board1);
  initBoard(board2);
  board1->zobristRandoms = zobrist;
  board2->zobristRandoms = zobrist;
}

// static BOOL testRemovePiece() {
//   const char *FUNCTION_NAME = "removePiece";
//   BOOL expectedToFail = FALSE;
//   board result, expected;
//   matchBoardsToTest(&result, &expected);
//   return FALSE;
// }

void testBoard() {
  BOOL resultTestPlaceBitValue = testPlaceBitValue();
  BOOL resultTestCleanGameState = testCleanGameState();
  BOOL resultTestInitBoard = testInitBoard();
  if (resultTestPlaceBitValue && resultTestCleanGameState &&
      resultTestInitBoard) {
    printf(GREEN "Tested board sucessfully \n" RESET);
  }
}
