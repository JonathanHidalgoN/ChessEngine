#include "../test.h"
#include <stdio.h>

int areFenStringEqual(const fenString *functionResult,
                      const fenString *expectedResult, char testNumber) {
  int areEqual = compareFenString(functionResult, expectedResult);
  if (!areEqual) {
    printf("Error testing FEN string case: %c\n", testNumber);
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
  int c1 = areFenStringEqual(&functionResult, &expectedResult, '0');
  return c1;
}

void testFenString() {
  int resultTestInitFenString = testInitFenString();
  if (resultTestInitFenString) {
    printf(GREEN "Tested FEN string successfully\n" RESET);
  }
}
