#include "../../include/board/pieceList.h"
#include <stdio.h>

void updatePieceList(pieceList *pieceList, bitBoardsList *bitBoardsList) {
  cleanPieceList(pieceList);
  for (int i = 0; i < NUMBEROFCOLORS; i++) {
    for (int j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      bitboard bb = bitBoardsList->pieces[i][j];
      while (bb) {
        int k = __builtin_ctzll(bb);
        bb &= bb - 1;
        pieceList->pieces[k] = j;
      }
    }
  }
}

void cleanPieceList(pieceList *pieceList) {
  for (int i = 0; i < NUMBEROFSQUARES; i++) {
    pieceList->pieces[i] = PIECE_EMPTY;
  }
}
