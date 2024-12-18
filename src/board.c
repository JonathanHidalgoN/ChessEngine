#include "../include/board.h"
#include <stdint.h>
#include <stdio.h>

void printBitboard(bitboard bb) {
  int i, j;
  printf("\n");
  for (i = 0; i < ROWS; i++) {
    printf("%d | ", ROWS - i - 1);
    for (j = 0; j < COLS; j++) {
      uint64_t mask = (uint64_t)1 << (LASTBIT - (i * ROWS + j));
      char val = (mask & bb) != 0 ? '1' : '0';
      printf("%c ", val);
    }
    printf("\n");
  }
  printf("\n");
  printf("    7 6 5 4 3 2 1 0");
  printf("\n");
}

/*
 * -1 < col < 8, -1 < row < 8, so at max following col + (8) * row
 *  will be 7 + 56 = 63, and at min will be 0 so we can move the 1
 *  from the 0 to the 63 bit
 */
void placeBitValue(int bitIndex, int val, bitboard *bb) {
  // uint64_t mask = (uint64_t)1 << (col + ROWS * row);
  uint64_t mask = (uint64_t)1 << bitIndex;
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
      chessBoard->pieces[i][j] = 0ULL;
    }
  }
}

void initChessBoard(chessBoard *chessBoard) {
  int i;
  // TODO : CHANGE COORDS TO USE BIT INDEX AND AVOID THE INIT
  cleanChessBoard(chessBoard);

  for (i = 0; i < COLS; i++) {
    placeBitValue(fromBoardCordsToBitIndex(1, i), 1,
                  &chessBoard->pieces[WHITE][PAWN]); // Modify directly
    placeBitValue(fromBoardCordsToBitIndex(6, i), 1,
                  &chessBoard->pieces[BLACK][PAWN]); // Modify directly
  }

  placeBitValue(fromBoardCordsToBitIndex(0, 0), 1,
                &chessBoard->pieces[WHITE][ROOK]);
  placeBitValue(fromBoardCordsToBitIndex(0, 7), 1,
                &chessBoard->pieces[WHITE][ROOK]);
  placeBitValue(fromBoardCordsToBitIndex(7, 0), 1,
                &chessBoard->pieces[BLACK][ROOK]);
  placeBitValue(fromBoardCordsToBitIndex(7, 7), 1,
                &chessBoard->pieces[BLACK][ROOK]);

  placeBitValue(fromBoardCordsToBitIndex(0, 1), 1,
                &chessBoard->pieces[WHITE][KNIGHT]);
  placeBitValue(fromBoardCordsToBitIndex(0, 6), 1,
                &chessBoard->pieces[WHITE][KNIGHT]);
  placeBitValue(fromBoardCordsToBitIndex(7, 1), 1,
                &chessBoard->pieces[BLACK][KNIGHT]);
  placeBitValue(fromBoardCordsToBitIndex(7, 6), 1,
                &chessBoard->pieces[BLACK][KNIGHT]);

  placeBitValue(fromBoardCordsToBitIndex(0, 2), 1,
                &chessBoard->pieces[WHITE][BISHOP]);
  placeBitValue(fromBoardCordsToBitIndex(0, 5), 1,
                &chessBoard->pieces[WHITE][BISHOP]);
  placeBitValue(fromBoardCordsToBitIndex(7, 2), 1,
                &chessBoard->pieces[BLACK][BISHOP]);
  placeBitValue(fromBoardCordsToBitIndex(7, 5), 1,
                &chessBoard->pieces[BLACK][BISHOP]);

  placeBitValue(fromBoardCordsToBitIndex(0, 3), 1,
                &chessBoard->pieces[WHITE][QUEEN]);
  placeBitValue(fromBoardCordsToBitIndex(7, 3), 1,
                &chessBoard->pieces[BLACK][QUEEN]);

  placeBitValue(fromBoardCordsToBitIndex(0, 4), 1,
                &chessBoard->pieces[WHITE][KING]);
  placeBitValue(fromBoardCordsToBitIndex(7, 4), 1,
                &chessBoard->pieces[BLACK][KING]);
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
