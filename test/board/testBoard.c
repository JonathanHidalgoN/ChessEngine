#include "../test.h"
#include <stdio.h>

static bool testPlaceBitValue() {
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

static bool testCleanGameState() {
  const char *FUNCTION_NAME = "cleanGameState";
  // Zobrist keys will be tested alone
  const uint64_t ZOBRIST_KEY = 0ULL;
  bool expectedToFail = false;
  board result;
  gameState expectGS = {COLOR_WHITE, NO_CASTLING, 0, NO_PASSANT,
                        0,           ZOBRIST_KEY, 0};
  cleanGameState(&result);
  result.gameState.zobristKey = ZOBRIST_KEY;
  bool c0 = compareGameStates(&expectGS, &result.gameState, FUNCTION_NAME, '0',
                              expectedToFail);
  return c0;
}

static bool testInitBoard() {
  const char *FUNCTION_NAME = "initBoard";
  bool expectedToFail = false;
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
  bool c0 =
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
  board1->gameState.zobristKey = computeZobristFromState(
      &zobrist, &board1->bitBoardsList, board1->gameState.playingSide,
      board1->gameState.castlingCode, board1->gameState.enPassantCode);
  board2->gameState.zobristKey = computeZobristFromState(
      &zobrist, &board2->bitBoardsList, board2->gameState.playingSide,
      board2->gameState.castlingCode, board2->gameState.enPassantCode);
}

static bool testRemovePiece() {
  const char *FUNCTION_NAME = "removePiece";
  bool expectedToFail = false;
  board result, expected;
  matchBoardsToTest(&result, &expected);
  // Add a two pawns to remove one
  putPiece(&result, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 1, COLOR_WHITE, PIECE_PAWN);
  removePiece(&result, 1, COLOR_WHITE, PIECE_PAWN);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  bool c0 =
      compareBoards(&expected, &result, FUNCTION_NAME, '0', expectedToFail);
  return c0;
}

void testBoard() {
  bool resultTestPlaceBitValue = testPlaceBitValue();
  bool resultTestCleanGameState = testCleanGameState();
  bool resultTestInitBoard = testInitBoard();
  bool resultTestRemovePiece = testRemovePiece();
  if (resultTestPlaceBitValue && resultTestCleanGameState &&
      resultTestInitBoard && resultTestRemovePiece) {
    printf(GREEN "Tested board sucessfully \n" RESET);
  }
}
