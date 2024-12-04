#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

typedef enum { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING } PieceType;
typedef enum { WHITE, BLACK } PieceColor;

typedef struct {
  PieceType type;
  PieceColor color;
  int hasMoved;
} ChessPiece;

ChessPiece createPiece(PieceType type, PieceColor color);
#endif // !CHESS_PIECE_H
