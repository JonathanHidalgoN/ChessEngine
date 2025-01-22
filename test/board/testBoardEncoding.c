#include "../../include/board/boardEncoding.h"
#include "../test.h"
#include <stdint.h>

static BOOL testComputeZobristC1(zobristRandoms *randoms) {
  uint64_t expectedKey, resultKey;
  bitBoardsList bbl;
  cleanBitBoardList(&bbl);
  int side = WHITE;
  int castlingCode = 0;
  int passantCode = 0;
  bbl.pieces[WHITE][PAWN] = BIT(0);
  expectedKey =
      computeZobristFromState(randoms, &bbl, side, castlingCode, passantCode);
  side = BLACK;
  resultKey =
      computeZobristFromState(randoms, &bbl, side, castlingCode, passantCode);
  if (expectedKey == resultKey) {
    printf("Error in computeZobristFromBoard c1");
    return 0;
  }
  return 1;
}

void testZobristGeneration() {
  zobristRandoms randoms;
  fillZobristRandoms(&randoms);
  BOOL resultC1 = testComputeZobristC1(&randoms);
  if (resultC1) {
    printf(GREEN "Tested zobrist keys successfully\n" RESET);
  }
}
