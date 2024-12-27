#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include "../include/board.h"
void showDiff(bitboard expected, bitboard result);
int compareBitBoard(bitboard expectedResult, bitboard result, char testNumber,
                    char *functionName);
void printPieceStruct(piece *piece);
int comparePieces(piece *expectedPiece, piece *resultPiece, char testNumber);
#endif
