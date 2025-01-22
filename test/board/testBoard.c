#include "../test.h"
#include <stdbool.h>
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
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 1, COLOR_WHITE, PIECE_PAWN);
  removePiece(&result, 1, COLOR_WHITE, PIECE_PAWN);
  bool c0 =
      compareBoards(&expected, &result, FUNCTION_NAME, '0', expectedToFail);
  // Clean boards, put different pieces
  matchBoardsToTest(&result, &expected);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 1, COLOR_BLACK, PIECE_PAWN);
  putPiece(&result, 3, COLOR_WHITE, PIECE_ROOK);
  putPiece(&result, 4, COLOR_BLACK, PIECE_ROOK);
  removePiece(&result, 1, COLOR_BLACK, PIECE_PAWN);
  removePiece(&result, 3, COLOR_WHITE, PIECE_ROOK);
  removePiece(&result, 4, COLOR_BLACK, PIECE_ROOK);
  bool c1 =
      compareBoards(&expected, &result, FUNCTION_NAME, '1', expectedToFail);
  // Clean boards, put different pieces multiple comparison
  matchBoardsToTest(&result, &expected);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&expected, 1, COLOR_BLACK, PIECE_PAWN);
  putPiece(&result, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 1, COLOR_BLACK, PIECE_PAWN);
  putPiece(&result, 3, COLOR_WHITE, PIECE_ROOK);
  putPiece(&result, 4, COLOR_BLACK, PIECE_ROOK);
  removePiece(&result, 3, COLOR_WHITE, PIECE_ROOK);
  removePiece(&result, 4, COLOR_BLACK, PIECE_ROOK);
  bool c2 =
      compareBoards(&expected, &result, FUNCTION_NAME, '2', expectedToFail);
  // Clean boards, expected to fail
  expectedToFail = true;
  matchBoardsToTest(&result, &expected);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&expected, 1, COLOR_BLACK, PIECE_PAWN);
  putPiece(&result, 1, COLOR_BLACK, PIECE_PAWN);
  putPiece(&result, 3, COLOR_WHITE, PIECE_ROOK);
  putPiece(&result, 4, COLOR_BLACK, PIECE_ROOK);
  removePiece(&result, 3, COLOR_WHITE, PIECE_ROOK);
  removePiece(&result, 4, COLOR_BLACK, PIECE_ROOK);
  bool c3 =
      compareBoards(&expected, &result, FUNCTION_NAME, '2', expectedToFail);
  return c0 && c1 && c2 && c3;
}

static bool testPutPiece() {
  const char *FUNCTION_NAME = "putPiece";
  bool expectedToFail = false;
  board result, expected;
  matchBoardsToTest(&result, &expected);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 0, COLOR_WHITE, PIECE_PAWN);
  bool c0 =
      compareBoards(&expected, &result, FUNCTION_NAME, '0', expectedToFail);

  matchBoardsToTest(&result, &expected);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&expected, 1, COLOR_BLACK, PIECE_ROOK);
  putPiece(&result, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 1, COLOR_BLACK, PIECE_ROOK);
  bool c1 =
      compareBoards(&expected, &result, FUNCTION_NAME, '1', expectedToFail);

  matchBoardsToTest(&result, &expected);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_ROOK);
  putPiece(&result, 0, COLOR_WHITE, PIECE_ROOK);
  bool c2 =
      compareBoards(&expected, &result, FUNCTION_NAME, '2', expectedToFail);

  expectedToFail = true;
  matchBoardsToTest(&result, &expected);
  putPiece(&expected, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 0, COLOR_WHITE, PIECE_PAWN);
  putPiece(&result, 1, COLOR_BLACK, PIECE_ROOK);
  bool c3 =
      compareBoards(&expected, &result, FUNCTION_NAME, '3', expectedToFail);

  return c0 && c1 && c2 && c3;
}

static bool testChangePassant() {
  const char *FUNCTION_NAME = "changePassant";
  bool expectedToFail = false;
  board result, expected;
  matchBoardsToTest(&result, &expected);
  changePassant(&result, W1);
  changePassant(&result, B8);
  changePassant(&result, NO_PASSANT);
  changePassant(&expected, NO_PASSANT);
  bool c0 =
      compareBoards(&expected, &result, FUNCTION_NAME, '0', expectedToFail);
  matchBoardsToTest(&result, &expected);
  changePassant(&result, B7);
  changePassant(&result, B1);
  changePassant(&expected, B1);
  bool c1 =
      compareBoards(&expected, &result, FUNCTION_NAME, '2', expectedToFail);
  matchBoardsToTest(&result, &expected);
  changePassant(&result, B1);
  changePassant(&result, W1);
  changePassant(&result, B2);
  changePassant(&result, B6);
  changePassant(&expected, B6);
  bool c2 =
      compareBoards(&expected, &result, FUNCTION_NAME, '2', expectedToFail);
  expectedToFail = true;
  matchBoardsToTest(&result, &expected);
  changePassant(&result, B1);
  changePassant(&result, B2);
  changePassant(&result, B3);
  changePassant(&expected, B4);
  bool c3 =
      compareBoards(&expected, &result, FUNCTION_NAME, '3', expectedToFail);
  return c0 && c1 && c2 && c3;
}

static bool testChangePlayingSide() {
  const char *FUNCTION_NAME = "changePlayingSide";
  bool expectedToFail = false;
  board result, expected;
  // Expected playing side is white
  matchBoardsToTest(&result, &expected);
  changePlayingSide(&result);
  changePlayingSide(&result);
  bool c0 =
      compareBoards(&expected, &result, FUNCTION_NAME, '0', expectedToFail);
  expectedToFail = true;
  matchBoardsToTest(&result, &expected);
  changePlayingSide(&result);
  changePlayingSide(&result);
  changePlayingSide(&result);
  bool c1 =
      compareBoards(&expected, &result, FUNCTION_NAME, '0', expectedToFail);
  return c0 && c1;
}

static bool testChangeCastling() {
  const char *FUNCTION_NAME = "changeCastling";
  bool expectedToFail = false;
  board result, expected;
  matchBoardsToTest(&result, &expected);
  changeCastling(&result, BLACK_KINGSIDE);
  changeCastling(&result, BLACK_BOTH);
  changeCastling(&result, NO_PASSANT);
  changeCastling(&expected, NO_PASSANT);
  bool c0 =
      compareBoards(&expected, &result, FUNCTION_NAME, '0', expectedToFail);
  matchBoardsToTest(&result, &expected);
  changeCastling(&result, BLACK_KINGSIDE);
  changeCastling(&result, BLACK_BOTH);
  changeCastling(&expected, BLACK_BOTH);
  bool c1 =
      compareBoards(&expected, &result, FUNCTION_NAME, '2', expectedToFail);
  matchBoardsToTest(&result, &expected);
  changeCastling(&result, BLACK_KINGSIDE);
  changeCastling(&result, BLACK_BOTH);
  changeCastling(&result, WHITE_BOTH_BLACK_KINGSIDE);
  changeCastling(&result, BLACK_BOTH);
  changeCastling(&expected, BLACK_BOTH);
  bool c2 =
      compareBoards(&expected, &result, FUNCTION_NAME, '2', expectedToFail);
  expectedToFail = true;
  matchBoardsToTest(&result, &expected);
  changeCastling(&result, BLACK_KINGSIDE);
  changeCastling(&result, BLACK_BOTH);
  changeCastling(&result, WHITE_BOTH_BLACK_KINGSIDE);
  changeCastling(&expected, BLACK_BOTH);
  bool c3 =
      compareBoards(&expected, &result, FUNCTION_NAME, '3', expectedToFail);
  return c0 && c1 && c2 && c3;
}

void testBoard() {
  bool resultTestPlaceBitValue = testPlaceBitValue();
  bool resultTestCleanGameState = testCleanGameState();
  bool resultTestInitBoard = testInitBoard();
  bool resultTestRemovePiece = testRemovePiece();
  bool resultTestPutPiece = testPutPiece();
  bool resultTestChangePlayingSide = testChangePlayingSide();
  bool resultTestChangePassant = testChangePassant();
  bool resultTestChangeCastling = testChangeCastling();
  if (resultTestPlaceBitValue && resultTestCleanGameState &&
      resultTestInitBoard && resultTestRemovePiece && resultTestPutPiece &&
      resultTestChangePassant && resultTestChangePlayingSide &&
      resultTestChangeCastling) {
    printf(GREEN "Tested board sucessfully \n" RESET);
  }
}
