#ifndef FEN_STRINGS
#define FEN_STRINGS

#include "defs.h"
#define FEN_STRING_NUMBER_OF_VALID_POSITION_CHARACTERS 22

#define FEN_STRING_CASTLING_WHITE_QUEEN_SIDE 'Q'
#define FEN_STRING_CASTLING_WHITE_KING_SIDE 'K'
#define FEN_STRING_CASTLING_BLACK_QUEEN_SIDE 'q'
#define FEN_STRING_CASTLING_BLACK_KING_SIDE 'k'
#define FEN_STRING_NUMBER_CASTLING_CHARACTERS 4
#define FEN_STRING_LIMIT_EN_PASSANT_INDEX 16
#define FEN_STRING_LIMIT_HALF_MOVE_INDEX 50
#define FEN_STRING_LIMIT_FULL_MOVE_INDEX 800

const char FEN_STRING_VALID_POSITION_CHARACTERS
    [FEN_STRING_NUMBER_OF_VALID_POSITION_CHARACTERS] = {
        'p', 'n', 'b', 'q', 'k', 'r',           // Black pieces
        'P', 'N', 'B', 'Q', 'K', 'R',           // White pieces
        '/',                                    // Rank separator
        '1', '2', '3', '4', '5', '6', '7', '8', // Empty squares
};

const char FEN_STRING_VALID_SIDE_CHARACTERS[NUMBEROFCOLORS] = {'w', 'b'};

const char FEN_STRING_VALID_CASTLING_CHARACTERS
    [FEN_STRING_NUMBER_CASTLING_CHARACTERS] = {
        FEN_STRING_CASTLING_WHITE_QUEEN_SIDE,
        FEN_STRING_CASTLING_WHITE_KING_SIDE,
        FEN_STRING_CASTLING_BLACK_QUEEN_SIDE,
        FEN_STRING_CASTLING_BLACK_KING_SIDE};

/*
 * This struct represent a FEN string where
 * string : is the full string
 * stringLen : len of the string
 * piecesPositions : int pair with the index where piece position starts and
 * ends sideToMove : index where side to is castling : int pair with index where
 * castling starts and ends and so on.
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

#endif // !FEN_STRINGS
