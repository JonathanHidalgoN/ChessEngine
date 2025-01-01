#ifndef PIECE_LIST_H
#define PIECE_LIST_H

#include "defs.h"

typedef struct pieceList {
  int pieces[NUMBEROFSQUARES];
} pieceList;

void updatePieceList(pieceList *pieceList, bitBoardsList *bitBoardsList);

#endif // !PIECE_LIST_H
