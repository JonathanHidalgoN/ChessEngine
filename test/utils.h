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

/*
 * NOTE: This file has a lot of functions used for testing.
 * COMPARE FUNCTIONS : Given two data types, expected and result
 * this function will check if those are equal, depending of this and other
 * argument called expected to fail the function will return false or true and
 * print an message to output with some information.
 * -
 * ARE EQUAL: Testing requieres a lot of comparison between custom types,
 * this functions are responsible for that, return true when expected and result
 * are equal, some functions also require pointers to int, this is when the type
 * has an array so we can know the index where it failed(it can fail in multiple
 * index but functions return in the first one).
 * -
 * GENERAL FUNCTIONS : Those functions are just to save some time, for example
 * to print custom data types to output or maybe init some structures faster
 */

// GENERAL FUNCTIONS
void printPieceStruct(const piece *piece);
void printGameState(const gameState *state);
void printFenString(const fenString *fen);
void printIntPair(const intPair *pair, const char *name);
void printPieceList(const pieceList *pieceList);
/**
 * This function is used a lot, comparing bitboards is really usefull, when
 * they are not equal, just call this function and will print to output
 * both bitboards with some formatting
 */
void showDiff(bitboard expected, bitboard result);
gameState createGameState(int playingSide, int castlingCode,
                          int halfMoveCounter, int enPassantCode,
                          int fullMoveCounter, uint64_t zobristKey,
                          int phaseValue);
piece createPiece(int bitIndex, int side, int type);
// ARE EQUAL FUNCTIONA
bool areGameStatesEqual(const gameState *expected, const gameState *result);
bool arePieceListEqual(const pieceList *pl1, const pieceList *pl2);
bool areIntPairEqual(const intPair *a, const intPair *b);
bool areFenStringsEqual(const fenString *a, const fenString *b);
bool areHistoryEqual(const history *expected, const history *result, int *idx);
bool areZobristRandomsEqual(const zobristRandoms *expected,
                            const zobristRandoms *result, int *idx);
bool areInt64ListEqual(const uint64_t *l1, const uint64_t *l2, int len,
                       int *idx);
// COMPARE FUNCTIONS
bool compareGameStates(const gameState *expected, const gameState *result,
                       const char *functionName, char testNumber,
                       bool expectedToFail);
bool compareBoards(const board *expected, const board *result,
                   const char *functionName, char testNumber,
                   bool expectedToFail);
bool compareBitBoard(bitboard expectedResult, bitboard result, char testNumber,
                     const char *functionName, bool expectedToFail);
bool comparePieces(const piece *expectedPiece, const piece *resultPiece,
                   char testNumber, const char *functionName,
                   bool expectedToFail);
bool compareFenStrings(const fenString *expected, const fenString *resutl,
                       char testNumber, const char *functionName,
                       bool expectedToFail);
bool compareBitBoardLists(const bitBoardsList *bbl1, const bitBoardsList *bbl2,
                          char testNumber, const char *functionName,
                          bool expectedToFail);
bool compareIntNumbers(int expected, int result, const char *functionName,
                       const char *fieldName, bool expectedToFail);
bool comparePieceList(const pieceList *expected, const pieceList *result,
                      char testNumber, const char *functionName,
                      bool expectedToFail);
bool compareHistory(const history *expected, const history *result,
                    char testNumber, const char *functionName,
                    bool expectedToFail);
bool compareZobristRandoms(const zobristRandoms *expected,
                           const zobristRandoms *result, char testNumber,
                           const char *functionName, bool expectedToFail);
#endif
