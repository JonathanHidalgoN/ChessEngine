#include "utils.h"
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
                    const char *functionName) {

  if (result != expectedResult) {
    printf(RED "Error in function %s, test case %c \n" RESET, functionName,
           testNumber);
    showDiff(expectedResult, result);
    return 0;
  }
  return 1;
}

int arePiecesEqual(const piece *expectedResult, const piece *functionResult) {
  return expectedResult->bitIndex == functionResult->bitIndex &&
         expectedResult->side == functionResult->side &&
         expectedResult->type == functionResult->type;
}

void printPieceStruct(const piece *piece) {
  printf("side:%d, type:%d, bitIndex:%d\n", piece->side, piece->type,
         piece->bitIndex);
}

int comparePieces(const piece *expectedPiece, const piece *resultPiece,
                  char testNumber) {
  int areEqual = arePiecesEqual(expectedPiece, resultPiece);
  if (!areEqual) {
    printf(RED "Error in findPieceByBitIndex function case %c\n" RESET,
           testNumber);
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

int areGameStatesEqual(const gameState *expected, const gameState *result) {
  return expected->playingSide == result->playingSide &&
         expected->castlingCode == result->castlingCode &&
         expected->halfMoveCounter == result->halfMoveCounter &&
         expected->enPassantCode == result->enPassantCode &&
         expected->fullMoveCounter == result->fullMoveCounter &&
         expected->zobristKey == result->zobristKey &&
         expected->phaseValue == result->phaseValue;
}

void printGameState(const gameState *state) {
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

int arePieceListEqual(const pieceList *pl1, const pieceList *pl2) {
  for (int i = 0; i < NUMBEROFSQUARES; i++) {
    if (!(pl1->pieces[i] == pl2->pieces[i]))
      return 0;
  }
  return 1;
}

void printIntPair(const intPair *pair, const char *name) {
  printf("%s: {first: %d, second: %d}\n", name, pair->first, pair->second);
}

void printFenString(const fenString *fen) {
  printf("fenString {\n");
  printf("  string: \"%s\"\n", fen->string);
  printf("  stringLen: %d\n", fen->stringLen);

  if (fen->piecesPositions.first >= 0 &&
      fen->piecesPositions.second < fen->stringLen) {
    printf("  piecesPositions: {first: %d, end: %d}, string: \"%.*s\"\n",
           fen->piecesPositions.first, fen->piecesPositions.second,
           fen->piecesPositions.second - fen->piecesPositions.first + 1,
           fen->string + fen->piecesPositions.first);
  } else {
    printf("  piecesPositions: {first: %d, end: %d}, string: INVALID RANGE\n",
           fen->piecesPositions.first, fen->piecesPositions.second);
  }

  if (fen->sideToMove >= 0 && fen->sideToMove < fen->stringLen) {
    printf("  sideToMove: %d, string: \"%c\"\n", fen->sideToMove,
           fen->string[fen->sideToMove]);
  } else {
    printf("  sideToMove: %d, string: INVALID INDEX\n", fen->sideToMove);
  }

  if (fen->castling.first >= 0 && fen->castling.second < fen->stringLen) {
    printf("  castling: {first: %d, end: %d}, string: \"%.*s\"\n",
           fen->castling.first, fen->castling.second,
           fen->castling.second - fen->castling.first + 1,
           fen->string + fen->castling.first);
  } else {
    printf("  castling: {first: %d, end: %d}, string: INVALID RANGE\n",
           fen->castling.first, fen->castling.second);
  }

  if (fen->passant.first >= 0 && fen->passant.second < fen->stringLen) {
    printf("  passant: {first: %d, end: %d}, string: \"%.*s\"\n",
           fen->passant.first, fen->passant.second,
           fen->passant.second - fen->passant.first + 1,
           fen->string + fen->passant.first);
  } else {
    printf("  passant: {first: %d, end: %d}, string: INVALID RANGE\n",
           fen->passant.first, fen->passant.second);
  }

  if (fen->halfMove.first >= 0 && fen->halfMove.second < fen->stringLen) {
    printf("  halfMove: {first: %d, end: %d}, string: \"%.*s\"\n",
           fen->halfMove.first, fen->halfMove.second,
           fen->halfMove.second - fen->halfMove.first + 1,
           fen->string + fen->halfMove.first);
  } else {
    printf("  halfMove: {first: %d, end: %d}, string: INVALID RANGE\n",
           fen->halfMove.first, fen->halfMove.second);
  }

  if (fen->fullMove.first >= 0 && fen->fullMove.second < fen->stringLen) {
    printf("  fullMove: {first: %d, end: %d}, string: \"%.*s\"\n",
           fen->fullMove.first, fen->fullMove.second,
           fen->fullMove.second - fen->fullMove.first + 1,
           fen->string + fen->fullMove.first);
  } else {
    printf("  fullMove: {first: %d, end: %d}, string: INVALID RANGE\n",
           fen->fullMove.first, fen->fullMove.second);
  }

  printf("}\n");
}

int compareIntPair(const intPair *a, const intPair *b) {
  return (a->first == b->first && a->second == b->second);
}

int compareFenString(const fenString *a, const fenString *b) {
  if ((a->string == NULL || b->string == NULL)) {
    if (a->string != b->string) {
      return 0;
    }
  } else if (strcmp(a->string, b->string) != 0) {
    return 0;
  }

  if (a->stringLen != b->stringLen) {
    return 0;
  }

  if (!compareIntPair(&a->piecesPositions, &b->piecesPositions)) {
    return 0;
  }

  if (a->sideToMove != b->sideToMove) {
    return 0;
  }

  if (!compareIntPair(&a->castling, &b->castling)) {
    return 0;
  }

  if (!compareIntPair(&a->passant, &b->passant)) {
    return 0;
  }

  if (!compareIntPair(&a->halfMove, &b->halfMove)) {
    return 0;
  }

  if (!compareIntPair(&a->fullMove, &b->fullMove)) {
    return 0;
  }

  return 1;
}
