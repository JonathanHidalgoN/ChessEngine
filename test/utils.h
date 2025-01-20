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
                     const char *functionName, BOOL expectedToFail);
void printPieceStruct(const piece *piece);
BOOL comparePieces(const piece *expectedPiece, const piece *resultPiece,
                   char testNumber, const char *functionName,
                   BOOL expectedToFail);
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
BOOL compareFenStrings(const fenString *expected, const fenString *resutl,
                       char testNumber, const char *functionName,
                       BOOL expectedToFail);
BOOL compareBitBoardLists(const bitBoardsList *bbl1, const bitBoardsList *bbl2,
                          char testNumber, char *functionName,
                          BOOL expectedToFail);
BOOL compareIntNumbers(int expected, int result, const char *functionName,
                       const char *fieldName, BOOL expectedToFail);
BOOL areBoardsEqual(const board *expected, const board *result);
BOOL comparePieceList(const pieceList *expected, const pieceList *result,
                      char testNumber, const char *functionName,
                      BOOL expectedToFail);
BOOL areHistoryEqual(const history *expected, const history *result, int *idx);
BOOL compareHistory(const history *expected, const history *result,
                    char testNumber, const char *functionName,
                    BOOL expectedToFail);
BOOL areZobristRandomsEqual(const zobristRandoms *expected,
                            const zobristRandoms *result);
BOOL compareZobristRandoms(const zobristRandoms *expected,
                           const zobristRandoms *result, char testNumber,
                           const char *functionName, BOOL expectedToFail);
void printPieceList(const pieceList *pieceList);
#endif
