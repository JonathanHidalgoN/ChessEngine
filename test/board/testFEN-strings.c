#include "../test.h"
#include <stdio.h>

static BOOL testInitFenString() {
  int stringLen = 56;
  const char *FUNCTION_NAME = "initFenString";
  BOOL expectedToFail = FALSE;
  char *validString =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  fenString functionResult;
  fenString expectedResult = {validString, stringLen, {0, 42},  44,
                              {46, 49},    {51, 51},  {53, 53}, {55, 55}};
  initFenString(validString, stringLen, &functionResult);
  int c1 = compareFenStrings(&expectedResult, &functionResult, '1',
                             FUNCTION_NAME, expectedToFail);
  stringLen = 57;
  validString = "rnbqkrrr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq 1 5 10";
  fenString expectedResult2 = {validString, stringLen, {0, 42},  44,
                               {46, 49},    {51, 51},  {53, 53}, {55, 56}};
  initFenString(validString, stringLen, &functionResult);
  int c2 = compareFenStrings(&expectedResult2, &functionResult, '2',
                             FUNCTION_NAME, expectedToFail);

  stringLen = 28;
  validString = "8/8/8/8/8/8/8/8 w ---q - 5 1";
  fenString expectedResult3 = {validString, stringLen, {0, 14},  16,
                               {18, 21},    {23, 23},  {25, 25}, {27, 27}};
  initFenString(validString, stringLen, &functionResult);
  int c3 = compareFenStrings(&expectedResult3, &functionResult, '3',
                             FUNCTION_NAME, expectedToFail);

  stringLen = 45;
  validString = "pppp-ppp/8/8/8/8/8/8/ppppppp- w K--q 14 12 12";
  fenString expectedResult4 = {validString, stringLen, {0, 28},  30,
                               {32, 35},    {37, 38},  {40, 41}, {43, 44}};
  initFenString(validString, stringLen, &functionResult);
  int c4 = compareFenStrings(&expectedResult4, &functionResult, '4',
                             FUNCTION_NAME, expectedToFail);

  return c1 && c2 && c3 && c4;
}

static BOOL testCaseCheckValidFenString(fenString *fenString,
                                        int expectingValid, char testNumber) {
  int valid = checkValidFenString(fenString);
  if (expectingValid && !valid) {
    printf(RED "Error, expecting valid FEN string but got invalid %c\n" RESET,
           testNumber);
    printFenString(fenString);
    return 0;
  } else if (!expectingValid && valid) {
    printf(RED "Error, expecting invalid FEN string but got valid %c\n" RESET,
           testNumber);
    printFenString(fenString);
    return 0;
  }
  return 1;
}

static BOOL testCheckValidFenString() {
  int expectingValid = 1;
  int stringLen = 56;
  char *validString =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  fenString result;
  initFenString(validString, stringLen, &result);
  int c0 = testCaseCheckValidFenString(&result, expectingValid, '0');

  expectingValid = 1;
  stringLen = 56;
  validString = "--------/--------/8/8/8/8/--------/-------- w ---- - 0 0";
  initFenString(validString, stringLen, &result);
  int c1 = testCaseCheckValidFenString(&result, expectingValid, '1');

  expectingValid = 1;
  stringLen = 28;
  validString = "8/8/8/8/8/8/8/8 w KQkq - 0 1";
  initFenString(validString, stringLen, &result);
  int c2 = testCaseCheckValidFenString(&result, expectingValid, '2');

  expectingValid = 1;
  stringLen = 87;
  validString = "rnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 10 10 11";
  initFenString(validString, stringLen, &result);
  int c3 = testCaseCheckValidFenString(&result, expectingValid, '3');

  printf(YELLOW "--------Error messages from now until limit are "
                "expected--------\n" RESET);
  // Add invalid char "z" to get invalid FEN string
  expectingValid = 0;
  stringLen = 87;
  validString = "znbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 10 10 11";
  initFenString(validString, stringLen, &result);
  int c4 = testCaseCheckValidFenString(&result, expectingValid, '4');
  // Add invalid char "z" to get invalid FEN string at the end
  expectingValid = 0;
  stringLen = 87;
  validString = "pnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 10 10 1z";
  initFenString(validString, stringLen, &result);
  int c5 = testCaseCheckValidFenString(&result, expectingValid, '5');

  // Test numeric limits
  expectingValid = 0;
  stringLen = 88;
  validString = "pnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 10 10 900";
  initFenString(validString, stringLen, &result);
  int c6 = testCaseCheckValidFenString(&result, expectingValid, '6');

  // Test numeric limits
  expectingValid = 0;
  stringLen = 88;
  validString = "pnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 10 53 800";
  initFenString(validString, stringLen, &result);
  int c7 = testCaseCheckValidFenString(&result, expectingValid, '7');

  // Test numeric limits
  expectingValid = 0;
  stringLen = 88;
  validString = "pnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 17 50 800";
  initFenString(validString, stringLen, &result);
  int c8 = testCaseCheckValidFenString(&result, expectingValid, '8');

  // Add invalid side "s"
  expectingValid = 0;
  stringLen = 88;
  validString = "pnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR s KQkq 14 50 800";
  initFenString(validString, stringLen, &result);
  int c9 = testCaseCheckValidFenString(&result, expectingValid, '9');
  printf(YELLOW "---------------------LIMIT------------------------------------"
                "---\n" RESET);
  return c8 && c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c9;
}

static BOOL testInitBitBoardWithFenStringC0() {
  int i;
  int expectedToFail = 0;
  char *functionName = "initBitBoardListWithFenString";
  int stringLen = 88;
  char *string = "pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                 "pppppppp/pppppppp w KQkq 14 50 800";
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  bitBoardsList result, expected;
  cleanBitBoardList(&expected);
  initBitBoardListWithFenString(&result, &fenString);
  for (i = 0; i < NUMBEROFSQUARES; i++) {
    expected.pieces[WHITE][PAWN] |= BIT(i);
  }
  int valid = compareBitBoardLists(&expected, &result, '0', functionName,
                                   expectedToFail);
  return valid;
}

static BOOL testInitBitBoardWithFenStringC1() {
  char *functionName = "initBitBoardListWithFenString";
  int expectedToFail = 0;
  int stringLen = 28;
  char *string = "8/8/8/8/8/8/"
                 "8/8 w KQkq 1 5 8";
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  bitBoardsList result, expected;
  cleanBitBoardList(&expected);
  initBitBoardListWithFenString(&result, &fenString);
  int valid = compareBitBoardLists(&expected, &result, '1', functionName,
                                   expectedToFail);
  return valid;
}

static BOOL testInitBitBoardWithFenStringC2() {
  char *functionName = "initBitBoardListWithFenString";
  int expectedToFail = 0;
  int stringLen = 32;
  char *string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 5 8";
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  bitBoardsList result, expected;
  cleanBitBoardList(&expected);
  initBitBoardListWithFenString(&result, &fenString);
  expected.pieces[WHITE][PAWN] |= BIT(0);
  expected.pieces[BLACK][PAWN] |= BIT(7);
  expected.pieces[BLACK][ROOK] |= BIT(56);
  expected.pieces[WHITE][ROOK] |= BIT(63);
  int valid = compareBitBoardLists(&expected, &result, '2', functionName,
                                   expectedToFail);
  return valid;
}

static BOOL testInitBitBoardWithFenStringC3() {
  char *functionName = "initBitBoardListWithFenString";
  int expectedToFail = 1;
  int stringLen = 32;
  char *string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 5 8";
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  bitBoardsList result, expected;
  cleanBitBoardList(&expected);
  initBitBoardListWithFenString(&result, &fenString);
  int valid = compareBitBoardLists(&expected, &result, '2', functionName,
                                   expectedToFail);
  return valid;
}

static BOOL testGetSideFromFenString() {
  const char *FIELD_NAME = "SIDE";
  const char *FUNCTION_NAME = "getSideFromFenString";
  COLOR expectedSide = WHITE;
  BOOL expectedToFail = FALSE;
  int stringLen = 32;
  char *string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 5 8";
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  COLOR result = getSideFromFenString(&fenString);
  BOOL c0 = compareIntNumbers(expectedSide, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expectedSide = WHITE;
  expectedToFail = FALSE;
  stringLen = 35;
  string = "p6P/p7/8/8/8/8/8/R6r w KQkq 1 10 10";
  initFenString(string, stringLen, &fenString);
  result = getSideFromFenString(&fenString);
  BOOL c1 = compareIntNumbers(expectedSide, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expectedSide = BLACK;
  expectedToFail = FALSE;
  stringLen = 35;
  string = "p6P/p7/8/8/8/8/8/R6r b KQkq 1 10 10";
  initFenString(string, stringLen, &fenString);
  result = getSideFromFenString(&fenString);
  BOOL c2 = compareIntNumbers(expectedSide, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expectedSide = BLACK;
  expectedToFail = FALSE;
  stringLen = 38;
  string = "pppp3P/p7/8/8/8/8/8/R6r b KQkq 1 10 10";
  initFenString(string, stringLen, &fenString);
  result = getSideFromFenString(&fenString);
  BOOL c3 = compareIntNumbers(expectedSide, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expectedSide = BLACK;
  expectedToFail = TRUE;
  stringLen = 38;
  string = "pppp3P/p7/8/8/8/8/8/R6r w KQkq 1 10 10";
  initFenString(string, stringLen, &fenString);
  result = getSideFromFenString(&fenString);
  BOOL c4 = compareIntNumbers(expectedSide, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expectedSide = WHITE;
  expectedToFail = TRUE;
  stringLen = 35;
  string = "p6P/p7/8/8/8/8/8/R6r b KQkq 1 10 10";
  initFenString(string, stringLen, &fenString);
  result = getSideFromFenString(&fenString);
  BOOL c5 = compareIntNumbers(expectedSide, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);

  return c0 && c1 && c2 && c3 && c4 && c5;
}

static BOOL testGetCastlingCodeFromFenString() {
  const char *FIELD_NAME = "castling code";
  const char *FUNCTION_NAME = "getCastlingCodeFromFenString";
  CASTLING_KEYS expectedCastlingKey = BOTH_ALL;
  BOOL expectedToFail = FALSE;
  int stringLen = 32;
  char *string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 5 8";
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  CASTLING_KEYS result = getCastlingCodeFromFenString(&fenString);
  BOOL c0 = compareIntNumbers(expectedCastlingKey, result, FUNCTION_NAME,
                              FIELD_NAME, expectedToFail);
  expectedCastlingKey = BOTH_ALL;
  expectedToFail = FALSE;
  stringLen = 35;
  string = "p6P/p7/p7/p8/8/8/8/R6r w KQkq 1 5 8";
  initFenString(string, stringLen, &fenString);
  result = getCastlingCodeFromFenString(&fenString);
  BOOL c1 = compareIntNumbers(expectedCastlingKey, result, FUNCTION_NAME,
                              FIELD_NAME, expectedToFail);
  expectedCastlingKey = NO_CASTLING;
  expectedToFail = FALSE;
  stringLen = 35;
  string = "p6P/p7/p7/p8/8/8/8/R6r w ---- 1 5 8";
  initFenString(string, stringLen, &fenString);
  result = getCastlingCodeFromFenString(&fenString);
  BOOL c2 = compareIntNumbers(expectedCastlingKey, result, FUNCTION_NAME,
                              FIELD_NAME, expectedToFail);
  expectedCastlingKey = WHITE_KINGSIDE;
  expectedToFail = FALSE;
  stringLen = 35;
  string = "p6P/p7/p7/p8/8/8/8/R6r w K--- 1 5 8";
  initFenString(string, stringLen, &fenString);
  result = getCastlingCodeFromFenString(&fenString);
  BOOL c3 = compareIntNumbers(expectedCastlingKey, result, FUNCTION_NAME,
                              FIELD_NAME, expectedToFail);
  expectedCastlingKey = WHITE_BOTH_BLACK_QUEENSIDE;
  expectedToFail = FALSE;
  stringLen = 35;
  string = "p6P/p7/p7/p8/8/8/8/R6r w KQ-q 1 5 8";
  initFenString(string, stringLen, &fenString);
  result = getCastlingCodeFromFenString(&fenString);
  BOOL c4 = compareIntNumbers(expectedCastlingKey, result, FUNCTION_NAME,
                              FIELD_NAME, expectedToFail);
  expectedCastlingKey = BLACK_BOTH;
  expectedToFail = FALSE;
  stringLen = 35;
  string = "p6P/p7/p7/p8/8/8/8/R6r w --kq 1 5 8";
  initFenString(string, stringLen, &fenString);
  result = getCastlingCodeFromFenString(&fenString);
  BOOL c5 = compareIntNumbers(expectedCastlingKey, result, FUNCTION_NAME,
                              FIELD_NAME, expectedToFail);
  expectedCastlingKey = BLACK_BOTH;
  expectedToFail = TRUE;
  stringLen = 35;
  string = "p6P/p7/p7/p8/8/8/8/R6r w KQ-- 1 5 8";
  initFenString(string, stringLen, &fenString);
  result = getCastlingCodeFromFenString(&fenString);
  BOOL c6 = compareIntNumbers(expectedCastlingKey, result, FUNCTION_NAME,
                              FIELD_NAME, expectedToFail);
  expectedCastlingKey = BLACK_BOTH;
  expectedToFail = TRUE;
  stringLen = 35;
  string = "p6P/p7/p7/p8/8/8/8/R6r b KQkq 1 5 8";
  initFenString(string, stringLen, &fenString);
  result = getCastlingCodeFromFenString(&fenString);
  BOOL c7 = compareIntNumbers(expectedCastlingKey, result, FUNCTION_NAME,
                              FIELD_NAME, expectedToFail);
  return c0 && c1 && c2 && c4 && c3 && c5 && c6 && c7;
}

static BOOL testGetHalfMovesFromFenString() {
  const char *FIELD_NAME = "half moves";
  const char *FUNCTION_NAME = "getHalfMovesFromFenString";
  int expected = 5;
  BOOL expectedToFail = FALSE;
  int stringLen = 32;
  char *string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 5 8";
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  int result = getHalfMovesFromFenString(&fenString);
  BOOL c0 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 5;
  expectedToFail = FALSE;
  stringLen = 33;
  string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 5 10";
  initFenString(string, stringLen, &fenString);
  result = getHalfMovesFromFenString(&fenString);
  BOOL c1 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 8;
  expectedToFail = FALSE;
  stringLen = 35;
  string = "ppp6P/8/8/8/8/8/8/R6r w --kq 1 8 10";
  initFenString(string, stringLen, &fenString);
  result = getHalfMovesFromFenString(&fenString);
  BOOL c2 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 12;
  expectedToFail = FALSE;
  stringLen = 33;
  string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 12 8";
  initFenString(string, stringLen, &fenString);
  result = getHalfMovesFromFenString(&fenString);
  BOOL c3 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 44;
  expectedToFail = FALSE;
  stringLen = 32;
  string = "p7/8/8/8/8/8/8/R6r w KQkq 1 44 8";
  initFenString(string, stringLen, &fenString);
  result = getHalfMovesFromFenString(&fenString);
  BOOL c4 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 5;
  expectedToFail = TRUE;
  stringLen = 32;
  string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 6 8";
  initFenString(string, stringLen, &fenString);
  result = getHalfMovesFromFenString(&fenString);
  BOOL c5 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 5;
  expectedToFail = TRUE;
  stringLen = 33;
  string = "p6P/8/8/8/8/8/8/R6r b KQkq 1 10 8";
  initFenString(string, stringLen, &fenString);
  result = getHalfMovesFromFenString(&fenString);
  BOOL c6 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  return c0 && c1 && c2 && c3 && c4 && c5 && c6;
}

static BOOL testGetFullMovesFromFenString() {
  const char *FIELD_NAME = "full moves";
  const char *FUNCTION_NAME = "getFullMovesFromFenString";
  int expected = 8;
  BOOL expectedToFail = FALSE;
  int stringLen = 32;
  char *string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 5 8";
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  int result = getFullMovesFromFenString(&fenString);
  BOOL c0 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 10;
  expectedToFail = FALSE;
  stringLen = 33;
  string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 5 10";
  initFenString(string, stringLen, &fenString);
  result = getFullMovesFromFenString(&fenString);
  BOOL c1 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 12;
  expectedToFail = FALSE;
  stringLen = 36;
  string = "pppp5P/8/8/8/8/8/8/R6r w --kq 1 8 12";
  initFenString(string, stringLen, &fenString);
  result = getFullMovesFromFenString(&fenString);
  BOOL c2 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 1;
  expectedToFail = FALSE;
  stringLen = 33;
  string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 12 1";
  initFenString(string, stringLen, &fenString);
  result = getFullMovesFromFenString(&fenString);
  BOOL c3 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 44;
  expectedToFail = FALSE;
  stringLen = 32;
  string = "p7/8/8/8/8/8/8/R6r w KQkq 1 4 44";
  initFenString(string, stringLen, &fenString);
  result = getFullMovesFromFenString(&fenString);
  BOOL c4 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 5;
  expectedToFail = TRUE;
  stringLen = 32;
  string = "p6P/8/8/8/8/8/8/R6r w KQkq 1 6 8";
  initFenString(string, stringLen, &fenString);
  result = getFullMovesFromFenString(&fenString);
  BOOL c5 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  expected = 5;
  expectedToFail = TRUE;
  stringLen = 33;
  string = "p6P/8/8/8/8/8/8/R6r b KQkq 1 10 1";
  initFenString(string, stringLen, &fenString);
  result = getFullMovesFromFenString(&fenString);
  BOOL c6 = compareIntNumbers(expected, result, FUNCTION_NAME, FIELD_NAME,
                              expectedToFail);
  return c0 && c1 && c2 && c3 && c4 && c5 && c6;
}

static BOOL testInitBitBoardWithFenString() {
  int c0 = testInitBitBoardWithFenStringC0();
  int c1 = testInitBitBoardWithFenStringC1();
  int c2 = testInitBitBoardWithFenStringC2();
  int c3 = testInitBitBoardWithFenStringC3();
  return c0 && c1 && c2 && c3;
}

void testFenString() {
  BOOL resultTestInitFenString = testInitFenString();
  BOOL resultCheckValidFenString = testCheckValidFenString();
  BOOL resultTestIniBitBoardWithFenString = testInitBitBoardWithFenString();
  BOOL resultTestGetSideFromFenString = testGetSideFromFenString();
  BOOL resultTestGetCastlingCode = testGetCastlingCodeFromFenString();
  BOOL resultTestHalfMovesFenString = testGetHalfMovesFromFenString();
  BOOL resultTestGetFullMovesFromFenString = testGetFullMovesFromFenString();
  if (resultTestInitFenString && resultCheckValidFenString &&
      resultTestIniBitBoardWithFenString && resultTestGetSideFromFenString &&
      resultTestGetCastlingCode && resultTestHalfMovesFenString &&
      resultTestGetFullMovesFromFenString) {
    printf(GREEN "Tested FEN string successfully\n" RESET);
  }
}
