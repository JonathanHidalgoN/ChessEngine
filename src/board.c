#include "../include/board.h"
#include <stdint.h>
#include <stdio.h>

void setBitboard0(bitboard *bb) { (*bb) = 0; }
void printBitboard(bitboard bb) {
  int i, j;
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

  for (i = 0; i < COLS; i++) {
    placeBitValue(1, i, 1, &chessBoard->pieces[WHITE][PAWN]); // Modify directly
    placeBitValue(6, i, 1, &chessBoard->pieces[BLACK][PAWN]); // Modify directly
  }

  placeBitValue(0, 0, 1, &chessBoard->pieces[WHITE][ROOK]);
  placeBitValue(0, 7, 1, &chessBoard->pieces[WHITE][ROOK]);
  placeBitValue(7, 0, 1, &chessBoard->pieces[BLACK][ROOK]);
  placeBitValue(7, 7, 1, &chessBoard->pieces[BLACK][ROOK]);

  placeBitValue(0, 1, 1, &chessBoard->pieces[WHITE][KNIGHT]);
  placeBitValue(0, 6, 1, &chessBoard->pieces[WHITE][KNIGHT]);
  placeBitValue(7, 1, 1, &chessBoard->pieces[BLACK][KNIGHT]);
  placeBitValue(7, 6, 1, &chessBoard->pieces[BLACK][KNIGHT]);

  placeBitValue(0, 2, 1, &chessBoard->pieces[WHITE][BISHOP]);
  placeBitValue(0, 5, 1, &chessBoard->pieces[WHITE][BISHOP]);
  placeBitValue(7, 2, 1, &chessBoard->pieces[BLACK][BISHOP]);
  placeBitValue(7, 5, 1, &chessBoard->pieces[BLACK][BISHOP]);

  placeBitValue(0, 3, 1, &chessBoard->pieces[WHITE][QUEEN]);
  placeBitValue(7, 3, 1, &chessBoard->pieces[BLACK][QUEEN]);

  placeBitValue(0, 4, 1, &chessBoard->pieces[WHITE][KING]);
  placeBitValue(7, 4, 1, &chessBoard->pieces[BLACK][KING]);
}

void placePieceRepresentationIntoBoardString(bitboard bb, char *br,
                                             char symbol) {
  int i;
  for (i = 0; i < LASTBIT; i++) {
    uint64_t mask = (uint64_t)1 << i;
    if ((mask & bb) != 0) {
      br[LASTBIT - i] = symbol;
    }
  }
}

void printChessBoard(chessBoard *chessBoard) {
  // HERE I COULD CREATE TWO FUNCS ONE TO MAKE THE BOARD STRING AND OTHER
  // TO PRINT IT THAT WAY I AVOID CREATING THE STRING EACH TIME
  int numberOfCharsInBoard = (int)COLS * ROWS;
  char boardRepresentation[numberOfCharsInBoard];
  int i, j;
  for (i = 0; i < numberOfCharsInBoard; i++) {
    boardRepresentation[i] = '.';
  }
  placePieceRepresentationIntoBoardString(chessBoard->pieces[WHITE][PAWN],
                                          boardRepresentation, 'P');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[WHITE][KNIGHT],
                                          boardRepresentation, 'T');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[WHITE][QUEEN],
                                          boardRepresentation, 'Q');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[WHITE][KING],
                                          boardRepresentation, 'K');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[WHITE][ROOK],
                                          boardRepresentation, 'R');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[WHITE][BISHOP],
                                          boardRepresentation, 'B');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[BLACK][PAWN],
                                          boardRepresentation, 'p');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[BLACK][KNIGHT],
                                          boardRepresentation, 't');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[BLACK][QUEEN],
                                          boardRepresentation, 'q');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[BLACK][KING],
                                          boardRepresentation, 'k');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[BLACK][ROOK],
                                          boardRepresentation, 'r');
  placePieceRepresentationIntoBoardString(chessBoard->pieces[BLACK][BISHOP],
                                          boardRepresentation, 'b');
  for (i = 0; i < COLS; i++) {
    for (j = 0; j < ROWS; j++) {
      int idx = (int)i * COLS + j;
      printf("%c ", boardRepresentation[idx]);
    }
    printf("\n");
  }
}
