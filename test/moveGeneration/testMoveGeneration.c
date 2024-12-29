#include "../../include/moveGeneration/moveGeneration.h"
#include "../test.h"

int testComputeSideBitBoard() {
  int side = WHITE;
  bitboard expectedResult = 0ULL;
  chessBoard board;
  char *name = "computeSideBitBoard";
  cleanChessBoard(&board);

  // Board with no pieces should give 0 for white and black
  bitboard result0 = computeSideBitBoard(side, &board);
  int c0 = compareBitBoard(expectedResult, result0, '0', name);

  side = BLACK;
  bitboard result1 = computeSideBitBoard(side, &board);
  int c1 = compareBitBoard(expectedResult, result1, '1', name);

  // Test with pieces
  board.pieces[BLACK][PAWN] = BIT(0);
  board.pieces[BLACK][KING] = BIT(1);
  board.pieces[BLACK][ROOK] = BIT(2);
  board.pieces[BLACK][BISHOP] = BIT(3);

  // White should return 0
  side = WHITE;
  bitboard result2 = computeSideBitBoard(side, &board);
  int c2 = compareBitBoard(expectedResult, result2, '2', name);

  // BLACK should not return 0
  side = BLACK;
  expectedResult = BIT(0) + BIT(1) + BIT(2) + BIT(3);
  bitboard result3 = computeSideBitBoard(side, &board);
  int c3 = compareBitBoard(expectedResult, result3, '3', name);

  side = WHITE;
  board.pieces[WHITE][KNIGHT] = BIT(10) + BIT(11);
  board.pieces[WHITE][KING] = BIT(44);
  expectedResult = BIT(10) + BIT(11) + BIT(44);
  bitboard result4 = computeSideBitBoard(side, &board);
  int c4 = compareBitBoard(expectedResult, result4, '4', name);

  board.pieces[WHITE][KNIGHT] = 0ULL;
  expectedResult = BIT(44);
  bitboard result5 = computeSideBitBoard(side, &board);
  int c5 = compareBitBoard(expectedResult, result5, '5', name);

  return c1 && c0 && c2 && c3 && c4 && c5;
}

int testFindPieceByIndex() {
  chessBoard board;
  initChessBoard(&board);
  piece functionResult, expectedResult;
  // Test for Pawns(8 because we have 8 pawns, 48 is bitIndex where black pawns
  // start)
  expectedResult.type = PAWN;
  expectedResult.side = WHITE;
  int c0 = 1;
  for (int i = 0, j = 8 + i; i < 8; i++) {
    expectedResult.bitIndex = j;
    functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
    c0 = c0 && comparePieces(&expectedResult, &functionResult, '0');
  }
  expectedResult.type = PAWN;
  expectedResult.side = BLACK;
  int c1 = 1;
  for (int i = 0, j = i + 48; i < 8; i++) {
    expectedResult.bitIndex = j;
    functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
    c1 = c1 && comparePieces(&expectedResult, &functionResult, '1');
  }
  // Rooks tests
  expectedResult.type = ROOK;
  expectedResult.side = WHITE;
  expectedResult.bitIndex = 7;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c2 = comparePieces(&expectedResult, &functionResult, '2');
  expectedResult.type = ROOK;
  expectedResult.side = BLACK;
  expectedResult.bitIndex = 56;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c3 = comparePieces(&expectedResult, &functionResult, '3');
  expectedResult.type = ROOK;
  expectedResult.side = WHITE;
  expectedResult.bitIndex = 0;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c4 = comparePieces(&expectedResult, &functionResult, '4');

  expectedResult.type = ROOK;
  expectedResult.side = BLACK;
  expectedResult.bitIndex = 63;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c5 = comparePieces(&expectedResult, &functionResult, '5');

  // Knights tests
  expectedResult.type = KNIGHT;
  expectedResult.side = WHITE;
  expectedResult.bitIndex = 1;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c6 = comparePieces(&expectedResult, &functionResult, '6');

  expectedResult.type = KNIGHT;
  expectedResult.side = BLACK;
  expectedResult.bitIndex = 62;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c7 = comparePieces(&expectedResult, &functionResult, '7');

  // Bishops tests
  expectedResult.type = BISHOP;
  expectedResult.side = WHITE;
  expectedResult.bitIndex = 2;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c8 = comparePieces(&expectedResult, &functionResult, '8');

  expectedResult.type = BISHOP;
  expectedResult.side = BLACK;
  expectedResult.bitIndex = 61;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c9 = comparePieces(&expectedResult, &functionResult, '9');

  // Queens tests
  expectedResult.type = QUEEN;
  expectedResult.side = WHITE;
  expectedResult.bitIndex = 3;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c10 = comparePieces(&expectedResult, &functionResult, 'a');

  expectedResult.type = QUEEN;
  expectedResult.side = BLACK;
  expectedResult.bitIndex = 59;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c11 = comparePieces(&expectedResult, &functionResult, 'b');

  // Kings tests
  expectedResult.type = KING;
  expectedResult.side = WHITE;
  expectedResult.bitIndex = 4;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c12 = comparePieces(&expectedResult, &functionResult, 'c');

  expectedResult.type = KING;
  expectedResult.side = BLACK;
  expectedResult.bitIndex = 60;
  functionResult = findPieceByBitIndex(expectedResult.bitIndex, &board);
  int c13 = comparePieces(&expectedResult, &functionResult, 'd');
  return c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8 && c9 && c10 &&
         c11 && c12 && c13;
}

int testPieceLegalMoves(piece *piece, bitboard expectedResult,
                        chessBoard *board, char testNumber) {
  bitboard result;
  char *functionName;
  result = computeLegalMoves(piece->bitIndex, board);
  switch (piece->type) {
  case PAWN:
    functionName = "computeLegalMoves for pawn";
    break;
  case KING:
    functionName = "computeLegalMoves for king";
    break;
  case KNIGHT:
    functionName = "computeLegalMoves for knight";
    break;
  case ROOK:
    functionName = "computeLegalMoves for rook";
    break;
  case BISHOP:
    functionName = "computeLegalMoves for bishop";
    break;
  default:
    break;
  }
  return compareBitBoard(expectedResult, result, testNumber, functionName);
}

static int testPawnLegalMove(piece *testPawn, chessBoard *blockers,
                             bitboard expectedResult, char testNumber) {
  //+= to merge the current value if we have the same piece
  blockers->pieces[testPawn->side][testPawn->type] += BIT(testPawn->bitIndex);
  int result =
      testPieceLegalMoves(testPawn, expectedResult, blockers, testNumber);
  return result;
}

int testPawnLegalMoves() {
  // TODO : test special pawn moves
  bitboard expectedResult;
  chessBoard board;
  cleanChessBoard(&board);
  // Empty board test
  // white pawn at 0 bitIndex
  piece testPawn = {WHITE, PAWN, 0};
  expectedResult = BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 8);
  int c0 = testPawnLegalMove(&testPawn, &board, expectedResult, '0');
  cleanChessBoard(&board);
  // move one square, now have two possible attacks
  testPawn = createPiece(1, WHITE, PAWN);
  expectedResult = BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 8) +
                   BIT(testPawn.bitIndex + 7);
  int c1 = testPawnLegalMove(&testPawn, &board, expectedResult, '1');
  cleanChessBoard(&board);
  // Place two black pawns at possible attack indices, should  be able to attack
  testPawn = createPiece(1, WHITE, PAWN);
  board.pieces[BLACK][PAWN] =
      BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 7);
  expectedResult = BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 8) +
                   BIT(testPawn.bitIndex + 7);
  int c2 = testPawnLegalMove(&testPawn, &board, expectedResult, '2');
  cleanChessBoard(&board);
  // Change for white pawns, just one forward move
  testPawn = createPiece(1, WHITE, PAWN);
  board.pieces[WHITE][PAWN] =
      BIT(testPawn.bitIndex + 9) + BIT(testPawn.bitIndex + 7);
  expectedResult = BIT(testPawn.bitIndex + 8);
  int c3 = testPawnLegalMove(&testPawn, &board, expectedResult, '3');
  cleanChessBoard(&board);
  // Black pawn test, empty board corner
  testPawn = createPiece(63, BLACK, PAWN);
  expectedResult = BIT(testPawn.bitIndex - 8) + BIT(testPawn.bitIndex - 9);
  int c4 = testPawnLegalMove(&testPawn, &board, expectedResult, '4');
  cleanChessBoard(&board);
  // Black pawn at 19 with 3 black pieces, haven no possible attacks
  testPawn = createPiece(19, BLACK, PAWN);
  board.pieces[BLACK][BISHOP] = BIT(testPawn.bitIndex - 8) +
                                BIT(testPawn.bitIndex - 9) +
                                BIT(testPawn.bitIndex - 7);
  expectedResult = 0ULL;
  int c5 = testPawnLegalMove(&testPawn, &board, expectedResult, '5');
  cleanChessBoard(&board);
  // Black pawn with two blockers and one possible attack
  testPawn = createPiece(19, BLACK, PAWN);
  board.pieces[BLACK][BISHOP] =
      BIT(testPawn.bitIndex - 8) + BIT(testPawn.bitIndex - 7);
  board.pieces[WHITE][QUEEN] = BIT(testPawn.bitIndex - 9);
  expectedResult = BIT(testPawn.bitIndex - 9);
  int c6 = testPawnLegalMove(&testPawn, &board, expectedResult, '6');
  cleanChessBoard(&board);
  // White pawn at last row, can't move more
  testPawn = createPiece(62, WHITE, PAWN);
  expectedResult = 0ULL;
  int c7 = testPawnLegalMove(&testPawn, &board, expectedResult, '7');
  cleanChessBoard(&board);
  // Black pawn at first row can't move
  testPawn = createPiece(3, BLACK, PAWN);
  expectedResult = 0ULL;
  int c8 = testPawnLegalMove(&testPawn, &board, expectedResult, '8');
  cleanChessBoard(&board);
  return c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8;
}

void testMoveGeneration() {
  int resultTestComputeSideBitBoard = testComputeSideBitBoard();
  int resultTestFindPieceByIndex = testFindPieceByIndex();
  int resultTestPawnLegalMoves = testPawnLegalMoves();
  if (resultTestComputeSideBitBoard && resultTestFindPieceByIndex &&
      resultTestPawnLegalMoves) {
    printf("Tested move generation successfully\n");
  }
}
