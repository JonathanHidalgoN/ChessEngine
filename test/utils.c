#include "utils.h"
#include "test.h"
#include <stdint.h>
#include <stdio.h>

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

BOOL compareBitBoard(bitboard expectedResult, bitboard result, char testNumber,
                     const char *functionName, BOOL expectedToFail) {

  if (result != expectedResult && !expectedToFail) {
    printf(RED "Error in function %s, test case %c \n" RESET, functionName,
           testNumber);
    showDiff(expectedResult, result);
    return FALSE;
  } else if (result == expectedResult && expectedToFail) {
    printf(RED "Error in function %s expected to fail, test case %c \n" RESET,
           functionName, testNumber);
    showDiff(expectedResult, result);
    return FALSE;
  }
  return TRUE;
}

BOOL areBitBoardListEqual(const bitBoardsList *expectedBBL,
                          const bitBoardsList *functionBBL, int *f1, int *f2) {
  for (int i = 0; i < NUMBEROFCOLORS; i++) {
    for (int j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      if (expectedBBL->pieces[i][j] != functionBBL->pieces[i][j]) {
        *f1 = i;
        *f2 = j;
        return FALSE;
      }
    }
  }
  return TRUE;
}

BOOL compareBitBoardLists(const bitBoardsList *bbl1, const bitBoardsList *bbl2,
                          char testNumber, char *functionName,
                          BOOL expectedToFail) {
  int colorWhereFailed = -1;
  int pieceWhereFailed = -1;
  int areEqual =
      areBitBoardListEqual(bbl1, bbl2, &colorWhereFailed, &pieceWhereFailed);
  if (!areEqual && !expectedToFail) {
    printf(RED "Error in %s, color:%d, piece:%d expected equal bitBoardsList "
               "test number %c\n" RESET,
           functionName, colorWhereFailed, pieceWhereFailed, testNumber);
    showDiff(bbl1->pieces[colorWhereFailed][pieceWhereFailed],
             bbl2->pieces[colorWhereFailed][pieceWhereFailed]);
    return FALSE;
  } else if (areEqual && expectedToFail) {
    printf(RED
           "Error in %s, color:%d, piece:%d expected different bitBoardsList "
           "test number %c\n" RESET,
           functionName, colorWhereFailed, pieceWhereFailed, testNumber);
    showDiff(bbl1->pieces[colorWhereFailed][pieceWhereFailed],
             bbl2->pieces[colorWhereFailed][pieceWhereFailed]);
    return FALSE;
  }
  return TRUE;
}

BOOL arePiecesEqual(const piece *expectedResult, const piece *functionResult) {
  return expectedResult->bitIndex == functionResult->bitIndex &&
         expectedResult->side == functionResult->side &&
         expectedResult->type == functionResult->type;
}

void printPieceStruct(const piece *piece) {
  printf("side:%d, type:%d, bitIndex:%d\n", piece->side, piece->type,
         piece->bitIndex);
}

BOOL comparePieces(const piece *expectedPiece, const piece *resultPiece,
                   char testNumber, const char *functionName,
                   BOOL expectedToFail) {
  int areEqual = arePiecesEqual(expectedPiece, resultPiece);
  if (!areEqual && !expectedToFail) {
    printf(RED "Error in %s function case %c\n" RESET, functionName,
           testNumber);
    printf("Expected piece: ");
    printPieceStruct(expectedPiece);
    printf("Actual value: ");
    printPieceStruct(resultPiece);
    return 0;
  } else if (areEqual && expectedToFail) {
    printf(RED "Error in %s, expected to fail function case %c\n" RESET,
           functionName, testNumber);
    printf("Expected piece: ");
    printPieceStruct(expectedPiece);
    printf("Actual value: ");
    printPieceStruct(resultPiece);
    return 0;
  }
  return 1;
}

BOOL compareFenStrings(const fenString *expected, const fenString *result,
                       char testNumber, const char *functionName,
                       BOOL expectedToFail) {
  int areEqual = areFenStringsEqual(expected, result);
  if (!areEqual && !expectedToFail) {
    printf(RED "Error testing FEN string function %s, case: %c\n" RESET,
           functionName, testNumber);
    printf("------------------- Expected result ------------------------\n");
    printFenString(expected);
    printf("------------------- Function result ------------------------\n");
    printFenString(result);
    return FALSE;
  } else if (!areEqual && !expectedToFail) {
    printf(RED "Error testing FEN string, expected inequality, function %s, "
               "case: %c\n" RESET,
           functionName, testNumber);
    printf("------------------- Expected result ------------------------\n");
    printFenString(expected);
    printf("------------------- Function result ------------------------\n");
    printFenString(result);
    return FALSE;
  }
  return TRUE;
}

BOOL compareIntNumbers(int expected, int result, const char *functionName,
                       const char *fieldName, BOOL expectedToFail) {
  if (expected != result && !expectedToFail) {
    printf(
        RED
        "Error in function %s in %s equality, expected %d, result %d\n" RESET,
        functionName, fieldName, expected, result);
    return 0;
  } else if (expected == result && expectedToFail) {
    printf(RED "Error in function %s in %s inequality, expected %d, result "
               "%d\n" RESET,
           functionName, fieldName, expected, result);
    return 0;
  }
  return 1;
}

piece createPiece(int bitIndex, int side, int type) {
  piece result = {side, type, bitIndex};
  return result;
}

BOOL arePieceListEqual(const pieceList *pl1, const pieceList *pl2) {
  for (int i = 0; i < NUMBEROFSQUARES; i++) {
    if (!(pl1->pieces[i] == pl2->pieces[i]))
      return FALSE;
  }
  return TRUE;
}

BOOL areGameStatesEqual(const gameState *expected, const gameState *result) {
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
         "phaseValue: %d\n TODO:ADD PIECE LIST PRINT AND BBL\n",
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

BOOL areIntPairEqual(const intPair *a, const intPair *b) {
  return (a->first == b->first && a->second == b->second);
}

BOOL areFenStringsEqual(const fenString *a, const fenString *b) {
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

  if (!areIntPairEqual(&a->piecesPositions, &b->piecesPositions)) {
    return 0;
  }

  if (a->sideToMove != b->sideToMove) {
    return 0;
  }

  if (!areIntPairEqual(&a->castling, &b->castling)) {
    return 0;
  }

  if (!areIntPairEqual(&a->passant, &b->passant)) {
    return 0;
  }

  if (!areIntPairEqual(&a->halfMove, &b->halfMove)) {
    return 0;
  }

  if (!areIntPairEqual(&a->fullMove, &b->fullMove)) {
    return 0;
  }

  return 1;
}

BOOL comparePieceList(const pieceList *expected, const pieceList *result,
                      char testNumber, const char *functionName,
                      BOOL expectedToFail) {

  BOOL areEqual = arePieceListEqual(expected, result);
  if (!areEqual && !expectedToFail) {
    printf(RED "Error in function %s, expected equality, test case %c. "
               "Expected result:" RESET,
           functionName, testNumber);
    printPieceList(expected);
    printf(RED "-----------------Result----------------------" RESET);
    printPieceList(result);
    return FALSE;
  } else if (areEqual && expectedToFail) {
    printf(RED "Error in function %s, expected inequality, test case %c. "
               "Expected result:" RESET,
           functionName, testNumber);
    printPieceList(expected);
    printf(RED "-----------------Result----------------------" RESET);
    printPieceList(result);
    return FALSE;
  }
  return TRUE;
}

void printPieceList(const pieceList *pieceList) {
  for (int i = NUMBEROFSQUARES - 1; i >= 0; i--) {
    int pieceType = pieceList->pieces[i];
    printf("%d ", pieceType);
  }
  printf("\n");
}

BOOL areHistoryEqual(const history *expected, const history *result, int *idx) {
  // TODO: THIS TEST USES THE ARRAY OF THE HISTORY NO THE POP FUNCTION
  // BECAUSE THE CONST, CHANGE THIS
  if (expected->len != result->len) {
    *idx = -1;
    return FALSE;
  }
  gameState gs1, gs2;
  for (int i = 0; i < expected->len; i++) {
    BOOL areEqual =
        areGameStatesEqual(&expected->states[i], &result->states[i]);
    if (!areEqual)
      *idx = i;
    return FALSE;
  }
  return TRUE;
}

BOOL compareHistory(const history *expected, const history *result,
                    char testNumber, const char *functionName,
                    BOOL expectedToFail) {
  int idx = -2;
  BOOL areEqual = areHistoryEqual(expected, result, &idx);
  if (!areEqual && !expectedToFail) {
    if (idx == -2) {
      printf(RED "Error in function %s, test case %d, expected equal lenghts, "
                 "expected: %d, result: %d\n" RESET,
             functionName, testNumber, result->len, expected->len);
    }
    printf(RED "Error in function %s, test case %d, expected equality, "
               "eexpected: \n" RESET,
           functionName, testNumber);
    printGameState(&expected->states[idx]);
    printf(RED "Result: \n" RESET);
    printGameState(&result->states[idx]);
    return FALSE;
  } else if (!areEqual && !expectedToFail) {
    if (idx == -2) {
      printf(RED
             "Error in function %s, test case %d, expected inequal lenghts, "
             "expected: %d, result: %d\n" RESET,
             functionName, testNumber, result->len, expected->len);
    }
    printf(RED "Error in function %s, test case %d, expected inequality, "
               "eexpected: \n" RESET,
           functionName, testNumber);
    printGameState(&expected->states[idx]);
    printf(RED "Result: \n" RESET);
    printGameState(&result->states[idx]);
    return FALSE;
  }
  return TRUE;
}

BOOL areInt64ListEqual(const uint64_t *l1, const uint64_t *l2, int len,
                       int *idx) {
  for (int i = 0; i < len; i++) {
    if (l1[i] != l2[i]) {
      *idx = i;
      return FALSE;
    }
  }
  return TRUE;
}

BOOL areZobristRandomsEqual(const zobristRandoms *expected,
                            const zobristRandoms *result) {
  return FALSE;
}
