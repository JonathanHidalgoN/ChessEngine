#ifndef TEST_UTILS_H
#define TEST_UTILS_H
#include "../include/board/FEN-strings.h"
#include "../include/board/board.h"
#include <string.h>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

void showDiff(bitboard expected, bitboard result);
BOOL compareBitBoard(bitboard expectedResult, bitboard result, char testNumber,
                     const char *functionName);
void printPieceStruct(const piece *piece);
BOOL comparePieces(const piece *expectedPiece, const piece *resultPiece,
                   char testNumber);
piece createPiece(int bitIndex, int side, int type);
BOOL areGameStatesEqual(const gameState *expected, const gameState *result);
void printGameState(const gameState *state);
gameState createGameState(int playingSide, int castlingCode,
                          int halfMoveCounter, int enPassantCode,
                          int fullMoveCounter, uint64_t zobristKey,
                          int phaseValue);
BOOL arePieceListEqual(const pieceList *pl1, const pieceList *pl2);
void printIntPair(const intPair *pair, const char *name);
void printFenString(const fenString *fen);
BOOL areIntPairEqual(const intPair *a, const intPair *b);
BOOL areFenStringsEqual(const fenString *a, const fenString *b);
BOOL compareFenStrings(const fenString *functionResult,
                       const fenString *expectedResult, char testNumber);
BOOL compareBitBoardLists(const bitBoardsList *bbl1, const bitBoardsList *bbl2,
                          char testNumber, char *functionName,
                          int expectedToFail);
BOOL compareIntNumbers(int expected, int result, const char *functionName,
                       const char *fieldName, BOOL expectedToFail);
#endif
