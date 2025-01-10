
#ifndef FEN_STRINGS
#define FEN_STRINGS

#include "defs.h"
#include "stdlib.h"
#include <ctype.h>

#define FEN_STRING_NUMBER_OF_VALID_POSITION_CHARACTERS 22
#define FEN_STRING_NO_CASTLING '-'
#define FEN_STRING_CASTLING_WHITE_QUEEN_SIDE 'Q'
#define FEN_STRING_CASTLING_WHITE_KING_SIDE 'K'
#define FEN_STRING_CASTLING_BLACK_QUEEN_SIDE 'q'
#define FEN_STRING_CASTLING_BLACK_KING_SIDE 'k'
#define FEN_STRING_NUMBER_CASTLING_CHARACTERS 5
#define FEN_STRING_LIMIT_EN_PASSANT 16
#define FEN_STRING_LIMIT_HALF_MOVE 50
#define FEN_STRING_LIMIT_FULL_MOVE 800
#define FEN_STRING_MIN_CHARACTERS 28

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

void initFenString(const char *string, int stringLen, fenString *fenString);
int checkValidFenStringPart1(const char *string, int start, int end);
int checkValidFenStringPart2(const char *string, int start);
int checkValidFenStringPart3(const char *string, int start, int end);
int checkValidFenStringNumberVals(const char *string, int lowIndex,
                                  int highIndex, int limit);
int checkValidFenString(const fenString *fenString);

#endif // FEN_STRINGS
