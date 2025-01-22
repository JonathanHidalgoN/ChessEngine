#include "../../include/moveGeneration/moveGeneration.h"
#define DEBBUG 1

bitboard computePawnForwardMove(int bitIndex, int side) {
  // TODO :  add special pawn moves
  bitboard move = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  // side == 1 means black
  if (side) {
    move |= (mask >> 8);
  } else {
    move |= (mask << 8);
  }
  return move;
}

piece findPieceByBitIndex(int bitIndex, const bitBoardsList *board) {
  // TODO: Union with something to represent not found
  struct piece newPiece;
  int i, j, found;
  found = 0;
  // Find the index of piece to move
  for (i = 0; i < NUMBEROFCOLORS; i++) {
    for (j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      bitboard mask = 1ULL << bitIndex;
      if (board->pieces[i][j] & mask) {
        newPiece.type = j;
        newPiece.side = i;
        newPiece.bitIndex = bitIndex;
        found = 1;
        break;
      }
      if (found)
        break;
    }
  }
  if (!found)
    printf("Piece not found, this will create a bug");
  return newPiece;
}

bitboard computeLegalMoves(int bitIndex, const bitBoardsList *board) {
  piece piece = findPieceByBitIndex(bitIndex, board);
  bitboard legalMoves, alyBitBoard, generalBitBoard;
  // Add castling, mate, passang pawn,
  alyBitBoard = computeSideBitBoard(piece.side, board);
  switch (piece.type) {
  case PIECE_PAWN:
    // Why didn't I add the forward move in the pawn attack function?
    // I am making this chess engine myself but sometimes I get stuck,
    // a tutorial I was following did the attack and move in different
    // functions, and claude says I will help in the future.
    legalMoves = (computePawnForwardMove(piece.bitIndex, piece.side) |
                  computePawnAttack(bitIndex, piece.side)) &
                 ~alyBitBoard;
    break;
  case PIECE_KING:
    legalMoves = computePawnAttack(bitIndex, piece.side) & ~alyBitBoard;
    break;
  case PIECE_KNIGHT:
    legalMoves = computePawnAttack(bitIndex, piece.side) & ~alyBitBoard;
    break;
  case PIECE_ROOK:
    generalBitBoard = computeSideBitBoard(!piece.side, board) | alyBitBoard;
    legalMoves = computeRookAttack(bitIndex, generalBitBoard) & ~alyBitBoard;
    break;
  case PIECE_BISHOP:
    generalBitBoard = computeSideBitBoard(!piece.side, board) | alyBitBoard;
    legalMoves = computeBishopAttack(bitIndex, generalBitBoard) & ~alyBitBoard;
    break;
  }
  return legalMoves;
}
