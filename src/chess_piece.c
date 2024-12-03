#include "../include/chess_piece.h"

ChessPiece createPiece(PieceType type, PieceColor color, char file, int rank) {
  ChessPiece piece;
  piece.type = type;
  piece.color = color;
  piece.position.file = file;
  piece.position.rank = rank;
  return piece;
}
