#include "../include/board.h"
#include <stdint.h>
#include <stdio.h>

void setBitboard0(bitboard *bb) { (*bb) = 0; }
/*
 * This function will print the board
 */
void printBitboard(bitboard bb) {
  int i, j;
  const int LASTBIT = (int)ROWS * COLS - 1;
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      uint64_t mask = (uint64_t)1 << (LASTBIT - (i * ROWS + j));
      char val = (mask & bb) != 0 ? '1' : '0';
      printf("%c ", val);
    }
    printf("\n");
  }
}

/*
 * -1 < col < 8, -1 < row < 8, so at max following col + (8) * row
 *  will be 7 + 56 = 63, and at min will be 0 so we can move the 1
 *  from the 0 to the 63 bit
 */
void placeBitValue(int row, int col, int val, bitboard *bb) {
  // COULD CHECK FOR VALID COORDS IN RANGE HERE
  uint64_t mask = (uint64_t)1 << (col + ROWS * row);
  if (!val) {
    *bb = *bb & ~mask;
  } else {
    *bb = *bb | mask;
  }
}

void cleanChessBoard(chessBoard *chessBoard) {
  int i, j;
  for (i = 0; i < NUMBEROFCOLORS; i++) {
    for (j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      setBitboard0(&chessBoard->pieces[i][j]);
    }
  }
}

void initChessBoard(chessBoard *chessBoard) {
  int i;
  cleanChessBoard(chessBoard);
  bitboard whitePawns = chessBoard->pieces[WHITE][PAWN];
  bitboard whiteKings = chessBoard->pieces[WHITE][KING];
  bitboard whiteQueens = chessBoard->pieces[WHITE][QUEEN];
  bitboard whiteBishops = chessBoard->pieces[WHITE][BISHOP];
  bitboard whiteKnights = chessBoard->pieces[WHITE][KNIGHT];
  bitboard whiteRooks = chessBoard->pieces[WHITE][ROOK];

  bitboard blackPawns = chessBoard->pieces[BLACK][PAWN];
  bitboard blackKings = chessBoard->pieces[BLACK][KING];
  bitboard blackQueens = chessBoard->pieces[BLACK][QUEEN];
  bitboard blackBishops = chessBoard->pieces[BLACK][BISHOP];
  bitboard blackKnights = chessBoard->pieces[BLACK][KNIGHT];
  bitboard blackRooks = chessBoard->pieces[BLACK][ROOK];

  for (i = 0; i < COLS; i++) {
    placeBitValue(1, i, 1, &whitePawns);
    placeBitValue(6, i, 1, &blackPawns);
  }

  placeBitValue(0, 0, 1, &whiteRooks);
  placeBitValue(0, 7, 1, &whiteRooks);
  placeBitValue(7, 0, 1, &blackRooks);
  placeBitValue(7, 7, 1, &blackRooks);

  placeBitValue(0, 1, 1, &whiteKnights);
  placeBitValue(0, 6, 1, &whiteKnights);
  placeBitValue(7, 1, 1, &blackKnights);
  placeBitValue(7, 6, 1, &blackKnights);

  placeBitValue(0, 2, 1, &whiteBishops);
  placeBitValue(0, 5, 1, &whiteBishops);
  placeBitValue(7, 2, 1, &blackBishops);
  placeBitValue(7, 5, 1, &blackBishops);

  placeBitValue(0, 3, 1, &whiteQueens);
  placeBitValue(7, 3, 1, &blackQueens);

  placeBitValue(0, 4, 1, &whiteKings);
  placeBitValue(7, 4, 1, &blackKings);
}
