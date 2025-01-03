#include "../../include/board/boardEncoding.h"
#include <stdint.h>

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

uint64_t computeZobristFromBoard(zobristRandoms *randoms,
                                 bitBoardsList *bitBoardsList, int side,
                                 int castlingCode, int passantCode) {
  uint64_t key = 0ULL;
  int i, j, k;
  for (i = 0; i < NUMBEROFCOLORS; i++) {
    for (j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      for (k = 0; k < NUMBEROFSQUARES; k++) {
        uint64_t mask = 1ULL << k;
        if (mask & bitBoardsList->pieces[i][j]) {
          int index = (int)i * j * k;
          key ^= randoms->pieceRandoms[index];
        }
      }
    }
  }
  key ^= randoms->castlingRandoms[castlingCode];
  key ^= randoms->sidesRandoms[side];
  key ^= randoms->passantRandoms[passantCode];
  return key;
}
