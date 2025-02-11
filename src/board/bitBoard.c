#include "../../include/board/bitBoard.h"

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

void cleanBitBoardList(bitBoardsList *bitBoardsList) {
  int i, j;
  for (i = 0; i < NUMBEROFCOLORS; i++) {
    for (j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      bitBoardsList->pieces[i][j] = 0ULL;
    }
  }
}

void initBitBoardsListStandarChess(bitBoardsList *bitBoardsList) {
  int i;
  // TODO : CHANGE COORDS TO USE BIT INDEX AND AVOID THE INIT
  cleanBitBoardList(bitBoardsList);

  for (i = 0; i < COLS; i++) {
    placeBitValue(fromBoardCordsToBitIndex(1, i), 1,
                  &bitBoardsList->pieces[COLOR_WHITE][PIECE_PAWN]); // Modify directly
    placeBitValue(fromBoardCordsToBitIndex(6, i), 1,
                  &bitBoardsList->pieces[COLOR_BLACK][PIECE_PAWN]); // Modify directly
  }

  placeBitValue(fromBoardCordsToBitIndex(0, 0), 1,
                &bitBoardsList->pieces[COLOR_WHITE][PIECE_ROOK]);
  placeBitValue(fromBoardCordsToBitIndex(0, 7), 1,
                &bitBoardsList->pieces[COLOR_WHITE][PIECE_ROOK]);
  placeBitValue(fromBoardCordsToBitIndex(7, 0), 1,
                &bitBoardsList->pieces[COLOR_BLACK][PIECE_ROOK]);
  placeBitValue(fromBoardCordsToBitIndex(7, 7), 1,
                &bitBoardsList->pieces[COLOR_BLACK][PIECE_ROOK]);

  placeBitValue(fromBoardCordsToBitIndex(0, 1), 1,
                &bitBoardsList->pieces[COLOR_WHITE][PIECE_KNIGHT]);
  placeBitValue(fromBoardCordsToBitIndex(0, 6), 1,
                &bitBoardsList->pieces[COLOR_WHITE][PIECE_KNIGHT]);
  placeBitValue(fromBoardCordsToBitIndex(7, 1), 1,
                &bitBoardsList->pieces[COLOR_BLACK][PIECE_KNIGHT]);
  placeBitValue(fromBoardCordsToBitIndex(7, 6), 1,
                &bitBoardsList->pieces[COLOR_BLACK][PIECE_KNIGHT]);

  placeBitValue(fromBoardCordsToBitIndex(0, 2), 1,
                &bitBoardsList->pieces[COLOR_WHITE][PIECE_BISHOP]);
  placeBitValue(fromBoardCordsToBitIndex(0, 5), 1,
                &bitBoardsList->pieces[COLOR_WHITE][PIECE_BISHOP]);
  placeBitValue(fromBoardCordsToBitIndex(7, 2), 1,
                &bitBoardsList->pieces[COLOR_BLACK][PIECE_BISHOP]);
  placeBitValue(fromBoardCordsToBitIndex(7, 5), 1,
                &bitBoardsList->pieces[COLOR_BLACK][PIECE_BISHOP]);

  placeBitValue(fromBoardCordsToBitIndex(0, 3), 1,
                &bitBoardsList->pieces[COLOR_WHITE][PIECE_QUEEN]);
  placeBitValue(fromBoardCordsToBitIndex(7, 3), 1,
                &bitBoardsList->pieces[COLOR_BLACK][PIECE_QUEEN]);

  placeBitValue(fromBoardCordsToBitIndex(0, 4), 1,
                &bitBoardsList->pieces[COLOR_WHITE][PIECE_KING]);
  placeBitValue(fromBoardCordsToBitIndex(7, 4), 1,
                &bitBoardsList->pieces[COLOR_BLACK][PIECE_KING]);
}

void placePieceRepresentationIntoBoardString(bitboard bb, char *br,
                                             char symbol) {
  int i;
  for (i = 0; i <= LASTBIT; i++) {
    uint64_t mask = (uint64_t)1 << i;
    if ((mask & bb) != 0) {
      br[LASTBIT - i] = symbol;
    }
  }
}

bitboard computeSideBitBoard(int side, const bitBoardsList *board) {
  bitboard result = 0ULL;
  for (int i = 0; i < NUMBEROFDIFFERENTPIECES; i++)
    result |= board->pieces[side][i];
  return result;
}

void printChessBoard(bitBoardsList *bitBoardsList) {
  // HERE I COULD CREATE TWO FUNCS ONE TO MAKE THE BOARD STRING AND OTHER
  // TO PRINT IT THAT WAY I AVOID CREATING THE STRING EACH TIME
  int numberOfCharsInBoard = (int)COLS * ROWS;
  char boardRepresentation[numberOfCharsInBoard];
  int i, j;
  for (i = 0; i < numberOfCharsInBoard; i++) {
    boardRepresentation[i] = '.';
  }
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_WHITE][PIECE_PAWN],
                                          boardRepresentation, 'P');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_WHITE][PIECE_KNIGHT],
                                          boardRepresentation, 'T');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_WHITE][PIECE_QUEEN],
                                          boardRepresentation, 'Q');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_WHITE][PIECE_KING],
                                          boardRepresentation, 'K');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_WHITE][PIECE_ROOK],
                                          boardRepresentation, 'R');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_WHITE][PIECE_BISHOP],
                                          boardRepresentation, 'B');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_BLACK][PIECE_PAWN],
                                          boardRepresentation, 'p');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_BLACK][PIECE_KNIGHT],
                                          boardRepresentation, 't');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_BLACK][PIECE_QUEEN],
                                          boardRepresentation, 'q');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_BLACK][PIECE_KING],
                                          boardRepresentation, 'k');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_BLACK][PIECE_ROOK],
                                          boardRepresentation, 'r');
  placePieceRepresentationIntoBoardString(bitBoardsList->pieces[COLOR_BLACK][PIECE_BISHOP],
                                          boardRepresentation, 'b');
  for (i = 0; i < COLS; i++) {
    printf("%d | ", ROWS - i - 1);
    for (j = 0; j < ROWS; j++) {
      int idx = (int)i * COLS + j;
      printf("%c ", boardRepresentation[idx]);
    }
    printf("\n");
  }
  printf("\n");
  printf("    7 6 5 4 3 2 1 0");
  printf("\n");
}
