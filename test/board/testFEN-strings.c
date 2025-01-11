#include "../test.h"
#include <stdio.h>

int areFenStringEqual(const fenString *functionResult,
                      const fenString *expectedResult, char testNumber) {
  int areEqual = compareFenString(functionResult, expectedResult);
  if (!areEqual) {
    printf(RED "Error testing FEN string case: %c\n" RESET, testNumber);
    printf("------------------- Expected result ------------------------\n");
    printFenString(expectedResult);
    printf("------------------- Function result ------------------------\n");
    printFenString(functionResult);
    return 0;
  }
  return 1;
}

int testInitFenString() {
  int stringLen = 56;
  char *validString =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  fenString functionResult;
  fenString expectedResult = {validString, stringLen, {0, 42},  44,
                              {46, 49},    {51, 51},  {53, 53}, {55, 55}};
  initFenString(validString, stringLen, &functionResult);
  int c1 = areFenStringEqual(&functionResult, &expectedResult, '1');

  stringLen = 57;
  validString = "rnbqkrrr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq 1 5 10";
  fenString expectedResult2 = {validString, stringLen, {0, 42},  44,
                               {46, 49},    {51, 51},  {53, 53}, {55, 56}};
  initFenString(validString, stringLen, &functionResult);
  int c2 = areFenStringEqual(&functionResult, &expectedResult2, '2');

  stringLen = 28;
  validString = "8/8/8/8/8/8/8/8 w ---q - 5 1";
  fenString expectedResult3 = {validString, stringLen, {0, 14},  16,
                               {18, 21},    {23, 23},  {25, 25}, {27, 27}};
  initFenString(validString, stringLen, &functionResult);
  int c3 = areFenStringEqual(&functionResult, &expectedResult3, '3');

  stringLen = 45;
  validString = "pppp-ppp/8/8/8/8/8/8/ppppppp- w K--q 14 12 12";
  fenString expectedResult4 = {validString, stringLen, {0, 28},  30,
                               {32, 35},    {37, 38},  {40, 41}, {43, 44}};
  initFenString(validString, stringLen, &functionResult);
  int c4 = areFenStringEqual(&functionResult, &expectedResult4, '4');

  return c1 && c2 && c3 && c4;
}

int testCaseCheckValidFenString(fenString *fenString, int expectingValid,
                                char testNumber) {
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

int testCheckValidFenString() {
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
  int c1 = testCaseCheckValidFenString(&result, expectingValid, '0');

  expectingValid = 1;
  stringLen = 28;
  validString = "8/8/8/8/8/8/8/8 w KQkq - 0 1";
  initFenString(validString, stringLen, &result);
  int c2 = testCaseCheckValidFenString(&result, expectingValid, '0');

  expectingValid = 1;
  stringLen = 87;
  validString = "rnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 10 10 11";
  initFenString(validString, stringLen, &result);
  int c3 = testCaseCheckValidFenString(&result, expectingValid, '0');

  // Add invalid char "z" to get invalid FEN string
  expectingValid = 0;
  stringLen = 87;
  validString = "znbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 10 10 11";
  initFenString(validString, stringLen, &result);
  int c4 = testCaseCheckValidFenString(&result, expectingValid, '0');
  // Add invalid char "z" to get invalid FEN string at the end
  expectingValid = 0;
  stringLen = 87;
  validString = "pnbqkbnr/pppppppp/pppppppp/pppppppp/pppppppp/pppppppp/"
                "PPPPPPPP/RNBQKBNR w KQkq 10 10 1z";
  initFenString(validString, stringLen, &result);
  int c5 = testCaseCheckValidFenString(&result, expectingValid, '0');

  return c0 && c1 && c2 && c3 && c4 && c5;
}

void testFenString() {
  int resultTestInitFenString = testInitFenString();
  int resultCheckValidFenString = testCheckValidFenString();
  if (resultTestInitFenString && resultCheckValidFenString) {
    printf(GREEN "Tested FEN string successfully\n" RESET);
  }
}
