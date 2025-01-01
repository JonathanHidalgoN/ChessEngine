#include "test.h"

void showDiff(bitboard expected, bitboard result) {
  if (DEBUG) {
    printf("------------------------------------------------------");
    printf("\n Expected board \n");
    printBitboard(expected);
    printf("\n\n Result\n");
    printBitboard(result);
    printf("------------------------------------------------------");
    printf("\n");
  }
}

int compareBitBoard(bitboard expectedResult, bitboard result, char testNumber,
                    char *functionName) {

  if (result != expectedResult) {
    printf("Error in function %s, test case %c \n", functionName, testNumber);
    showDiff(expectedResult, result);
    return 0;
  }
  return 1;
}

int arePiecesEqual(piece *expectedResult, piece *functionResult) {
  return expectedResult->bitIndex == functionResult->bitIndex &&
         expectedResult->side == functionResult->side &&
         expectedResult->type == functionResult->type;
}

void printPieceStruct(piece *piece) {
  printf("side:%d, type:%d, bitIndex:%d\n", piece->side, piece->type,
         piece->bitIndex);
}

int comparePieces(piece *expectedPiece, piece *resultPiece, char testNumber) {
  int areEqual = arePiecesEqual(expectedPiece, resultPiece);
  if (!areEqual) {
    printf("Error in findPieceByBitIndex function case %c\n", testNumber);
    printf("Expected piece: ");
    printPieceStruct(expectedPiece);
    printf("Actual value: ");
    printPieceStruct(resultPiece);
    return 0;
  }
  return 1;
}

piece createPiece(int bitIndex, int side, int type) {
  piece result = {side, type, bitIndex};
  return result;
}

int areGameStatesEqual(gameState *expected, gameState *result) {
  return expected->playingSide == result->playingSide &&
         expected->castlingCode == result->castlingCode &&
         expected->halfMoveCounter == result->halfMoveCounter &&
         expected->enPassantCode == result->enPassantCode &&
         expected->fullMoveCounter == result->fullMoveCounter &&
         expected->zobristKey == result->zobristKey &&
         expected->phaseValue == result->phaseValue;
}

void printGameState(gameState *state) {
  printf("playingSide: %d\ncastlingCode: %d\nhalfMoveCounter: %d\n"
         "enPassantCode: %d\nfullMoveCounter: %d\nzobristKey: %lu\n"
         "phaseValue: %d\n",
         state->playingSide, state->castlingCode, state->halfMoveCounter,
         state->enPassantCode, state->fullMoveCounter, state->zobristKey,
         state->phaseValue);
}

gameState createGameState(int playingSide, int castlingCode,
                          int halfMoveCounter, int enPassantCode,
                          int fullMoveCounter, uint64_t zobristKey,
                          int phaseValue) {
  gameState result = {playingSide,   castlingCode,    halfMoveCounter,
                      enPassantCode, fullMoveCounter, zobristKey,
                      phaseValue};
  return result;
}
