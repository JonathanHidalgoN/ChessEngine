#include "../../include/board/boardEncoding.h"

void fillZobristRandoms(zobristRandoms *randoms) {
  int i;
  uint64_t randomNumber;
  for (i = 0; i < NKEYSFORPIECES; i++) {
    randomNumber = getRandom64UNumber();
    randoms->pieceRandoms[i] = randomNumber;
  }
  for (i = 0; i < NKEYSFORCASTLING; i++) {
    randomNumber = getRandom64UNumber();
    randoms->castlingRandoms[i] = randomNumber;
  }
  for (i = 0; i < NKEYSFORSIDES; i++) {
    randomNumber = getRandom64UNumber();
    randoms->sidesRandoms[i] = randomNumber;
  }
  for (i = 0; i < NKEYSFORPASSANT; i++) {
    randomNumber = getRandom64UNumber();
    randoms->passantRandoms[i] = randomNumber;
  }
}
