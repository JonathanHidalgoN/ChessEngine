#ifndef BITBOARD
#define BITBOARD

#include "defs.h"
typedef uint64_t bitboard;
typedef struct bitBoardsList {
  bitboard pieces[NUMBEROFCOLORS][NUMBEROFDIFFERENTPIECES];
} bitBoardsList;

/**
 Set all pieces of the board to empty board
*/
void cleanBitBoardList(bitBoardsList *bitBoardsList);
/**
  print the bitboard
 */
void printBitboard(bitboard bb);
/**
  Place the val in the bitIndex on the Bitboard
 */
void placeBitValue(int bitIndex, int val, bitboard *bb);
/**
  Init the bitBoardsList with the classic chess config
 */
void initBitBoardsListStandarChess(bitBoardsList *bitBoardsList);
/**
  Create a string representation of the bitBoardsList
 */
void placePieceRepresentationIntoBoardString(bitboard bb, char *br,
                                             char symbol);
/**
  Print the bitBoardsList
 */
void printChessBoard(bitBoardsList *bitBoardsList);
#endif // !BITBOARD
