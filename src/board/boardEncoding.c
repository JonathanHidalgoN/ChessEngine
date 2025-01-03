#include "../../include/board/boardEncoding.h"
#include <stdint.h>

// TODO: MULTI THREADS CAUSE A BUG HERE WITH THE STATIC VARIABLE
static uint64_t ZOBRIST_RANDOM_STATE = 0x123456789ABCDEFULL;

static void fillRandomArray(uint64_t *array, int size, uint64_t *state) {
  for (int i = 0; i < size; i++) {
    array[i] = getRandom64UNumber(state);
  }
}

void fillZobristRandoms(zobristRandoms *randoms) {
  fillRandomArray(randoms->pieceRandoms, NKEYSFORPIECES, &ZOBRIST_RANDOM_STATE);
  fillRandomArray(randoms->castlingRandoms, NKEYSFORCASTLING,
                  &ZOBRIST_RANDOM_STATE);
  fillRandomArray(randoms->sidesRandoms, NKEYSFORSIDES, &ZOBRIST_RANDOM_STATE);
  fillRandomArray(randoms->passantRandoms, NKEYSFORPASSANT,
                  &ZOBRIST_RANDOM_STATE);
}

uint64_t computeZobristFromBoard(zobristRandoms *randoms,
                                 bitBoardsList *bitBoardsList, int side,
                                 int castlingCode, int passantCode) {
  uint64_t key = 0ULL;
  int i, j, k;
  for (i = 0; i < NUMBEROFCOLORS; i++) {
    for (j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      bitboard bb = bitBoardsList->pieces[i][j];
      while (bb) {
        int k = __builtin_ctzll(bb);
        bb &= bb - 1;
        int index = k + NUMBEROFSQUARES * (j + NUMBEROFDIFFERENTPIECES * i);
        key ^= randoms->pieceRandoms[index];
      }
    }
  }
  key ^= randoms->castlingRandoms[castlingCode];
  key ^= randoms->sidesRandoms[side];
  key ^= randoms->passantRandoms[passantCode];
  return key;
}
