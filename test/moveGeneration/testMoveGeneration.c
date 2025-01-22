#include "../../include/moveGeneration/moveGeneration.h"
#include "../test.h"

static bool testComputeSideBitBoard() {
  int side = COLOR_WHITE;
  bool expectedToFail = false;
  bitboard expectedResult = 0ULL;
  bitBoardsList board;
  char *name = "computeSideBitBoard";
  cleanBitBoardList(&board);

  // Board with no pieces should give 0 for white and black
  bitboard result0 = computeSideBitBoard(side, &board);
  int c0 = compareBitBoard(expectedResult, result0, '0', name, expectedToFail);

  side = COLOR_BLACK;
  bitboard result1 = computeSideBitBoard(side, &board);
  int c1 = compareBitBoard(expectedResult, result1, '1', name, expectedToFail);

  // Test with pieces
  board.pieces[COLOR_BLACK][PIECE_PAWN] = BIT(0);
  board.pieces[COLOR_BLACK][PIECE_KING] = BIT(1);
  board.pieces[COLOR_BLACK][PIECE_ROOK] = BIT(2);
  board.pieces[COLOR_BLACK][PIECE_BISHOP] = BIT(3);

  // White should return 0
  side = COLOR_WHITE;
  bitboard result2 = computeSideBitBoard(side, &board);
  int c2 = compareBitBoard(expectedResult, result2, '2', name, expectedToFail);

  // COLOR_BLACK should not return 0
  side = COLOR_BLACK;
  expectedResult = BIT(0) + BIT(1) + BIT(2) + BIT(3);
  bitboard result3 = computeSideBitBoard(side, &board);
  int c3 = compareBitBoard(expectedResult, result3, '3', name, expectedToFail);

  side = COLOR_WHITE;
  board.pieces[COLOR_WHITE][PIECE_KNIGHT] = BIT(10) + BIT(11);
  board.pieces[COLOR_WHITE][PIECE_KING] = BIT(44);
  expectedResult = BIT(10) + BIT(11) + BIT(44);
  bitboard result4 = computeSideBitBoard(side, &board);
  int c4 = compareBitBoard(expectedResult, result4, '4', name, expectedToFail);

  board.pieces[COLOR_WHITE][PIECE_KNIGHT] = 0ULL;
  expectedResult = BIT(44);
  bitboard result5 = computeSideBitBoard(side, &board);
  int c5 = compareBitBoard(expectedResult, result5, '5', name, expectedToFail);

  return c1 && c0 && c2 && c3 && c4 && c5;
}

static bool testFindPieceByIndex() {
  bitBoardsList board;
  initBitBoardsListStandarChess(&board);
  bool expectedToFail = false;
  const char *functionName = "findPieceByBitIndex";
  piece functionResult, expectedResult;
  // Test for Pawns(8 because we have 8 pawns, 48 is bitIndex where black pawns
  // start)
  expectedResult.type = PIECE_PAWN;
  expectedResult.side = COLOR_WHITE;
  int c0 = 1;
  for (int i = 0, j = 8 + i; i < 8; i++) {
    expectedResult.bitIndex = j;
    functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
    c0 = c0 && comparePieces(&expectedResult, &functionResult, '0',
                             functionName, expectedToFail);
  }
  expectedResult.type = PIECE_PAWN;
  expectedResult.side = COLOR_BLACK;
  int c1 = 1;
  for (int i = 0, j = i + 48; i < 8; i++) {
    expectedResult.bitIndex = j;
    functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
    c1 = c1 && comparePieces(&expectedResult, &functionResult, '1',
                             functionName, expectedToFail);
  }
  // Rooks tests
  expectedResult.type = PIECE_ROOK;
  expectedResult.side = COLOR_WHITE;
  expectedResult.bitIndex = 7;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c2 = comparePieces(&expectedResult, &functionResult, '2', functionName,
                         expectedToFail);
  expectedResult.type = PIECE_ROOK;
  expectedResult.side = COLOR_BLACK;
  expectedResult.bitIndex = 56;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c3 = comparePieces(&expectedResult, &functionResult, '3', functionName,
                         expectedToFail);
  expectedResult.type = PIECE_ROOK;
  expectedResult.side = COLOR_WHITE;
  expectedResult.bitIndex = 0;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c4 = comparePieces(&expectedResult, &functionResult, '4', functionName,
                         expectedToFail);

  expectedResult.type = PIECE_ROOK;
  expectedResult.side = COLOR_BLACK;
  expectedResult.bitIndex = 63;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c5 = comparePieces(&expectedResult, &functionResult, '5', functionName,
                         expectedToFail);

  // Knights tests
  expectedResult.type = PIECE_KNIGHT;
  expectedResult.side = COLOR_WHITE;
  expectedResult.bitIndex = 1;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c6 = comparePieces(&expectedResult, &functionResult, '6', functionName,
                         expectedToFail);

  expectedResult.type = PIECE_KNIGHT;
  expectedResult.side = COLOR_BLACK;
  expectedResult.bitIndex = 62;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c7 = comparePieces(&expectedResult, &functionResult, '7', functionName,
                         expectedToFail);

  // Bishops tests
  expectedResult.type = PIECE_BISHOP;
  expectedResult.side = COLOR_WHITE;
  expectedResult.bitIndex = 2;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c8 = comparePieces(&expectedResult, &functionResult, '8', functionName,
                         expectedToFail);

  expectedResult.type = PIECE_BISHOP;
  expectedResult.side = COLOR_BLACK;
  expectedResult.bitIndex = 61;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c9 = comparePieces(&expectedResult, &functionResult, '9', functionName,
                         expectedToFail);

  // Queens tests
  expectedResult.type = PIECE_QUEEN;
  expectedResult.side = COLOR_WHITE;
  expectedResult.bitIndex = 3;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c10 = comparePieces(&expectedResult, &functionResult, 'a', functionName,
                          expectedToFail);

  expectedResult.type = PIECE_QUEEN;
  expectedResult.side = COLOR_BLACK;
  expectedResult.bitIndex = 59;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c11 = comparePieces(&expectedResult, &functionResult, 'b', functionName,
                          expectedToFail);

  // Kings tests
  expectedResult.type = PIECE_KING;
  expectedResult.side = COLOR_WHITE;
  expectedResult.bitIndex = 4;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c12 = comparePieces(&expectedResult, &functionResult, 'c', functionName,
                          expectedToFail);

  expectedResult.type = PIECE_KING;
  expectedResult.side = COLOR_BLACK;
  expectedResult.bitIndex = 60;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c13 = comparePieces(&expectedResult, &functionResult, 'd', functionName,
                          expectedToFail);
  return c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8 && c9 && c10 &&
         c11 && c12 && c13;
}

static bool testPieceLegalMoves(piece *piece, bitboard expectedResult,
                                bitBoardsList *board, char testNumber) {
  bitboard result;
  char *functionName;
  bool expectedToFail = false;
  result = computeLegalMoves(piece->bitIndex, board);
  switch (piece->type) {
  case PIECE_PAWN:
    functionName = "computeLegalMoves for pawn";
    break;
  case PIECE_KING:
    functionName = "computeLegalMoves for king";
    break;
  case PIECE_KNIGHT:
    functionName = "computeLegalMoves for knight";
    break;
  case PIECE_ROOK:
    functionName = "computeLegalMoves for rook";
    break;
  case PIECE_BISHOP:
    functionName = "computeLegalMoves for bishop";
    break;
  default:
    break;
  }
  return compareBitBoard(expectedResult, result, testNumber, functionName,
                         expectedToFail);
}

static int testPawnLegalMove(piece *testPawn, bitBoardsList *blockers,
                             bitboard expectedResult, char testNumber) {
  //+= to merge the current value if we have the same piece
  blockers->pieces[testPawn->side][testPawn->type] += BIT(testPawn->bitIndex);
  int result =
      testPieceLegalMoves(testPawn, expectedResult, blockers, testNumber);
  return result;
}

static bool testPawnLegalMoves() {
  // TODO : test special pawn moves
  bitboard expectedResult;
  bitBoardsList board;
  cleanBitBoardList(&board);
  // Empty board test
  // white pawn at 0 bitIndex
  piece testPawn = {COLOR_WHITE, PIECE_PAWN, 0};
  expectedResult = BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 8);
  int c0 = testPawnLegalMove(&testPawn, &board, expectedResult, '0');
  cleanBitBoardList(&board);
  // move one square, now have two possible attacks
  testPawn = createPiece(1, COLOR_WHITE, PIECE_PAWN);
  expectedResult = BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 8) +
                   BIT(testPawn.bitIndex + 7);
  int c1 = testPawnLegalMove(&testPawn, &board, expectedResult, '1');
  cleanBitBoardList(&board);
  // Place two black pawns at possible attack indices, should  be able to attack
  testPawn = createPiece(1, COLOR_WHITE, PIECE_PAWN);
  board.pieces[COLOR_BLACK][PIECE_PAWN] =
      BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 7);
  expectedResult = BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 8) +
                   BIT(testPawn.bitIndex + 7);
  int c2 = testPawnLegalMove(&testPawn, &board, expectedResult, '2');
  cleanBitBoardList(&board);
  // Change for white pawns, just one forward move
  testPawn = createPiece(1, COLOR_WHITE, PIECE_PAWN);
  board.pieces[COLOR_WHITE][PIECE_PAWN] =
      BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 7);
  expectedResult = BIT(testPawn.bitIndex + 8);
  int c3 = testPawnLegalMove(&testPawn, &board, expectedResult, '3');
  cleanBitBoardList(&board);
  // Black pawn test, empty board corner
  testPawn = createPiece(63, COLOR_BLACK, PIECE_PAWN);
  expectedResult = BIT(testPawn.bitIndex - 8) + BIT(testPawn.bitIndex - 9);
  int c4 = testPawnLegalMove(&testPawn, &board, expectedResult, '4');
  cleanBitBoardList(&board);
  // Black pawn at 19 with 3 black pieces, haven no possible attacks
  testPawn = createPiece(19, COLOR_BLACK, PIECE_PAWN);
  board.pieces[COLOR_BLACK][PIECE_BISHOP] = BIT(testPawn.bitIndex - 8) +
                                BIT(testPawn.bitIndex - 9) +
                                BIT(testPawn.bitIndex - 7);
  expectedResult = 0ULL;
  int c5 = testPawnLegalMove(&testPawn, &board, expectedResult, '5');
  cleanBitBoardList(&board);
  // Black pawn with two blockers and one possible attack
  testPawn = createPiece(19, COLOR_BLACK, PIECE_PAWN);
  board.pieces[COLOR_BLACK][PIECE_BISHOP] =
      BIT(testPawn.bitIndex - 8) + BIT(testPawn.bitIndex - 7);
  board.pieces[COLOR_WHITE][PIECE_QUEEN] = BIT(testPawn.bitIndex - 9);
  expectedResult = BIT(testPawn.bitIndex - 9);
  int c6 = testPawnLegalMove(&testPawn, &board, expectedResult, '6');
  cleanBitBoardList(&board);
  // White pawn at last row, can't move more
  testPawn = createPiece(62, COLOR_WHITE, PIECE_PAWN);
  expectedResult = 0ULL;
  int c7 = testPawnLegalMove(&testPawn, &board, expectedResult, '7');
  cleanBitBoardList(&board);
  // Black pawn at first row can't move
  testPawn = createPiece(3, COLOR_BLACK, PIECE_PAWN);
  expectedResult = 0ULL;
  int c8 = testPawnLegalMove(&testPawn, &board, expectedResult, '8');
  cleanBitBoardList(&board);
  return c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8;
}

void testMoveGeneration() {
  bool resultTestComputeSideBitBoard = testComputeSideBitBoard();
  bool resultTestFindPieceByIndex = testFindPieceByIndex();
  bool resultTestPawnLegalMoves = testPawnLegalMoves();
  if (resultTestComputeSideBitBoard && resultTestFindPieceByIndex &&
      resultTestPawnLegalMoves) {
    printf(GREEN "Tested move generation successfully\n" RESET);
  }
}
