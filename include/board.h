#ifndef BOARD_H
#define BOARD_H

#include "chess_piece.h"

#define BOARDHEIGHT 8
#define BOARDWIDTH 8

typedef struct {
  ChessPiece piece;
  int hasPiece;
} BoardSquare;

typedef struct {
  BoardSquare squares[BOARDWIDTH][BOARDWIDTH];
} ChessBoard;

void cleanBoard(ChessBoard *board);
void populateBoard(ChessBoard *board);
void displayBoard(ChessBoard *board);
#endif
