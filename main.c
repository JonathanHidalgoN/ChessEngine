#include "include/board/defs.h"
#include "test/test.h"
#include <stdio.h>

// Color codes
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

void runTest() {
  printf(GREEN "Running test suit\n" RESET);
  testBoard();
  testAttacks();
  testMoveGeneration();
  testHistory();
  testPieceList();
  testZobristGeneration();
  testFenString();
}

int main() {

  if (1) {
    runTest();
    return 0;
  }
  // printf("Chess engine programmed by me (: \n");
  // bitBoardsList board;
  // initBitBoardsListStandarChess(&board);
  // printChessBoard(&board);
  // return 0;
}
