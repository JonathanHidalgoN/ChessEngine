#include "include/board.h"

int main() {
  ChessBoard board;
  cleanBoard(&board);
  populateBoard(&board);
  displayBoard(&board);
  return 0;
}
