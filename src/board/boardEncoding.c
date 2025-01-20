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
  fillRandomArray(randoms->castlingRandoms, NKEYSFORCASTLING,
                  &ZOBRIST_RANDOM_STATE);
  fillRandomArray(randoms->sidesRandoms, NKEYSFORSIDES, &ZOBRIST_RANDOM_STATE);
  fillRandomArray(randoms->passantRandoms, NKEYSFORPASSANT,
                  &ZOBRIST_RANDOM_STATE);
  for (int i = 0; i < NUMBEROFSQUARES; i++) {
    for (int j = 0; j < NUMBEROFCOLORS; j++) {
      fillRandomArray(randoms->pieceRandoms[i][j], NUMBEROFDIFFERENTPIECES,
                      &ZOBRIST_RANDOM_STATE);
    }
  }
}

uint64_t computeZobristFromState(zobristRandoms *randoms,
                                 bitBoardsList *bitBoardsList, COLOR side,
                                 CASTLING_KEYS castlingCode,
                                 PASSANT_KEYS passantCode) {
  uint64_t key = 0ULL;
  int i, j;
  for (i = 0; i < NUMBEROFCOLORS; i++) {
    for (j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      bitboard bb = bitBoardsList->pieces[i][j];
      while (bb) {
        int k = __builtin_ctzll(bb);
        bb &= bb - 1;
        key ^= randoms->pieceRandoms[k][i][j];
      }
    }
  }
  key ^= randoms->castlingRandoms[castlingCode];
  key ^= randoms->sidesRandoms[side];
  key ^= randoms->passantRandoms[passantCode];
  return key;
}
