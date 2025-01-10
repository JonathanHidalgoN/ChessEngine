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

int testCaseCheckValidFenString(fenString *fenString, int expetingValid,
                                char testNumber) {
  int valid = checkValidFenString(fenString);
  if (expetingValid && !valid) {
    printf(RED "Error, expecting valid FEN string but got invalid %c\n" RESET,
           testNumber);
    printFenString(fenString);
    return 0;
  } else if (!expetingValid && valid) {
    printf(RED "Error, expecting invalid FEN string but got valid %c\n" RESET,
           testNumber);
    printFenString(fenString);
    return 0;
  }
  return 1;
}

void testFenString() {
  int resultTestInitFenString = testInitFenString();
  if (resultTestInitFenString) {
    printf(GREEN "Tested FEN string successfully\n" RESET);
  }
}
