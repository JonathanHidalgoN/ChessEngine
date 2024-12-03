#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

typedef enum { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING } PieceType;
typedef enum { WHITE, BLACK } PieceColor;

typedef struct {
  char file;
  int rank;
} Position;

typedef struct {
  PieceType type;
  PieceColor color;
  Position position;
  int hasMoved;
} ChessPiece;

ChessPiece createPiece(PieceType type, PieceColor color, char file, int rank);
#endif // !CHESS_PIECE_H
