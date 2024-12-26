#include "include/attacks.h"
#include "include/board.h"
#include "test/test.h"
#include <stdio.h>

void runTest() {
  testBoard();
  testAttacks();
  testMoveGeneration();
}

int main() {

  if (1) {
    runTest();
    return 0;
  }

  printf("Chess engine programmed by me (: \n");
  chessBoard board;
  initChessBoard(&board);
  printChessBoard(&board);
  return 0;
}
