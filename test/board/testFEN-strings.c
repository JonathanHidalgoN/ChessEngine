#include "../test.h"

int testInitFenString() {
  int stringLen = 56;
  char *validString =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  fenString fenString;
  initFenString(validString, stringLen, &fenString);
  printFenString(&fenString);
  return 1;
}

void testFenString() {
  int resultTestInitFenString = testInitFenString();
  if (resultTestInitFenString) {
    printf(GREEN "Tested FEN string successfully\n" RESET);
  }
}
