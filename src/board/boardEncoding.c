#include "../../include/board/boardEncoding.h"

void fillZobristRandoms(zobristRandoms *randoms) {
  int i;
  uint64_t randomNumber;
  for (i = 0; i < keysForPieces; i++) {
    randomNumber = getRandom64UNumber();
    randoms->pieceRandoms[i] = randomNumber;
  }
  for (i = 0; i < keysForCastling; i++) {
    randomNumber = getRandom64UNumber();
    randoms->castlingRandoms[i] = randomNumber;
  }
  for (i = 0; i < keysForSides; i++) {
    randomNumber = getRandom64UNumber();
    randoms->sidesRandoms[i] = randomNumber;
  }
  for (i = 0; i < keysForPassant; i++) {
    randomNumber = getRandom64UNumber();
    randoms->passantRandoms[i] = randomNumber;
  }
}
