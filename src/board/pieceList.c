#include "../../include/board/pieceList.h"

void updatePieceList(pieceList *pieceList, bitBoardsList *bitBoardsList) {
  for (int i = 0; i < NUMBEROFCOLORS; i++) {
    for (int j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      bitboard bb = bitBoardsList->pieces[i][j];
      for (int k = 0; k < NUMBEROFSQUARES; k++) {
        bitboard mask = 1ULL << k;
        if (mask & bb) {
          pieceList->pieces[k] = j;
        } else {
          pieceList->pieces[k] = EMPTY;
        }
      }
    }
  }
}
