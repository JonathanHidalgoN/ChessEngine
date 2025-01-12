#ifndef PIECE_LIST_H
#define PIECE_LIST_H

#include "bitBoard.h"
#include "defs.h"

typedef struct pieceList {
  int pieces[NUMBEROFSQUARES];
} pieceList;

void updatePieceList(pieceList *pieceList, bitBoardsList *bitBoardsList);
void printPieceList(pieceList *pieceList);
void cleanPieceList(pieceList *pieceList);
#endif // !PIECE_LIST_H
