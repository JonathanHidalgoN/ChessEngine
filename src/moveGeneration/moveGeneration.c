#include "../../include/moveGeneration/moveGeneration.h"
#include <stdbool.h>
#include <stdint.h>
#define DEBBUG 1

bitboard computePawnForwardMove(int bitIndex, COLOR side, bool firstMove) {
  // TODO :  add special pawn moves
  bitboard move = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  // side == 1 means black
  if (firstMove && side) {
    move |= (mask >> 8) + (mask >> 16);
  } else if (firstMove && !side) {
    move |= (mask << 8) + (mask << 16);
  } else if (side) {
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

bool checkIfPawnFirstMove(COLOR side, int bitIndex) {
  // NOTE: if someone wants to play a random chess variant this will create
  // an unexpected behavior because just uses the position of the pawn

  // Cheks if pawn is in the row where it starts
  uint64_t mask = 1ULL;
  uint64_t numberPosition = 1ULL << bitIndex;
  const uint64_t ROW_2_UPPER_INDEX = 1ULL << 8;
  const uint64_t ROW_2_LOWER_INDEX = 1ULL << 15;
  const uint64_t ROW_7_UPPER_INDEX = 1ULL << 55;
  const uint64_t ROW_7_LOWER_INDEX = 1ULL << 48;
  if (side && numberPosition <= ROW_2_UPPER_INDEX &&
      numberPosition >= ROW_2_LOWER_INDEX) {
    return true;
  } else if (!side && numberPosition <= ROW_7_UPPER_INDEX &&
             numberPosition >= ROW_7_LOWER_INDEX) {
    return true;
  }
  return false;
}

bitboard computeLegalMoves(int bitIndex, const bitBoardsList *board) {
  piece piece = findPieceByBitIndex(bitIndex, board);
  bitboard legalMoves, alyBitBoard, generalBitBoard, enemyBitBoard;
  // Add castling, mate, passang pawn,
  alyBitBoard = computeSideBitBoard(piece.side, board);
  enemyBitBoard = computeSideBitBoard(~piece.side, board);
  generalBitBoard = alyBitBoard | enemyBitBoard;
  switch (piece.type) {
  case PIECE_PAWN:
    bool firstMove = false;
    legalMoves =
        (computePawnForwardMove(piece.bitIndex, piece.side, firstMove) |
         (computePawnAttack(bitIndex, piece.side) & enemyBitBoard)) &
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
