#include "../../include/board/board.h"

void removePiece(board *board, int square, int side, int piece) {
  bitboard mask = ~(1ULL << square);
  board->bitBoardsList.pieces[side][piece] &= mask;
  board->pieceList.pieces[square] = EMPTY;
  board->gameState.zobristKey ^=
      board->zobristRandoms.pieceRandoms[square][side][piece];
}

void putPiece(board *board, int square, int side, int piece) {
  bitboard mask = 1ULL << square;
  board->bitBoardsList.pieces[side][piece] |= mask;
  board->pieceList.pieces[square] = piece;
  board->gameState.zobristKey ^=
      board->zobristRandoms.pieceRandoms[square][side][piece];
}

void movePiece(board *board, int from, int to, int side, int piece) {
  removePiece(board, from, side, piece);
  putPiece(board, to, side, piece);
}
