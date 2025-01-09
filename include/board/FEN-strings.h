
#ifndef FEN_STRINGS
#define FEN_STRINGS

#include "defs.h"
#include "stdlib.h"
#include <ctype.h>

#define FEN_STRING_NUMBER_OF_VALID_POSITION_CHARACTERS 21
#define FEN_STRING_CASTLING_WHITE_QUEEN_SIDE 'Q'
#define FEN_STRING_CASTLING_WHITE_KING_SIDE 'K'
#define FEN_STRING_CASTLING_BLACK_QUEEN_SIDE 'q'
#define FEN_STRING_CASTLING_BLACK_KING_SIDE 'k'
#define FEN_STRING_NUMBER_CASTLING_CHARACTERS 4
#define FEN_STRING_LIMIT_EN_PASSANT 16
#define FEN_STRING_LIMIT_HALF_MOVE 50
#define FEN_STRING_LIMIT_FULL_MOVE 800

extern const char FEN_STRING_VALID_POSITION_CHARACTERS
    [FEN_STRING_NUMBER_OF_VALID_POSITION_CHARACTERS];
extern const char FEN_STRING_VALID_SIDE_CHARACTERS[NUMBEROFCOLORS];
extern const char
    FEN_STRING_VALID_CASTLING_CHARACTERS[FEN_STRING_NUMBER_CASTLING_CHARACTERS];

/*
 * This struct represents a FEN string.
 */
typedef struct fenString {
  char *string;
  int stringLen;
  intPair piecesPositions;
  int sideToMove;
  intPair castling;
  intPair passant;
  intPair halfMove;
  intPair fullMove;
} fenString;

void initFenString(char *string, int stringLen, fenString *fenString);
int checkValidFenStringPart1(char *string, int start, int end);
int checkValidFenStringPart2(char *string, int start);
int checkValidFenStringPart3(char *string, int start, int end);
int checkValidFenStringNumberVals(char *string, int lowIndex, int highIndex,
                                  int limit);
int checkValidFenString(fenString *fenString);

#endif // FEN_STRINGS
