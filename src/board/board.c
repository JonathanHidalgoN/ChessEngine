#include "../../include/board/board.h"

void removePiece(board *board, int square, int side, int piece) {
  bitboard mask = ~(1ULL << square);
  board->bitBoardsList.pieces[side][piece] &= mask;
  board->pieceList.pieces[square] = EMPTY;
}
