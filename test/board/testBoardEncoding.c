#include "../../include/board/boardEncoding.h"
#include "../test.h"

int testComputeZobristC1(zobristRandoms *randoms) {
  bitBoardsList bbl;
  cleanBitBoardList(&bbl);
  int side = WHITE;
  int castlingCode = 0;
  int passantCode = 0;
  uint64_t key =
      computeZobristFromBoard(randoms, &bbl, side, castlingCode, passantCode);
  printf("%lu\n", key);
  return 1;
}

void testZobristGeneration() {
  zobristRandoms randoms;
  fillZobristRandoms(&randoms);
  int resultC1 = testComputeZobristC1(&randoms);
  if (resultC1) {
    printf(GREEN "Tested zobrist keys successfully\n" RESET);
  }
}
