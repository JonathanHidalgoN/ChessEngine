#include "../../include/board/FEN-strings.h"
#include <stdio.h>
#include <string.h>
// TODO : When testing for invalid fen string the message is print, maybe move
// it because when test are run everything is fine but still print to console
// TODO : CHANGE ALL STRING ITERATION TO USE THE STRING TERMINATION?
// NOTE: I dont like the fact that we are first checking the fen string to see
// it is valid and then we are again checking it to parse it to a game state, I
// wont refactor this for now because it is not performance critial but the work
// could be done just on one cycle
const char FEN_STRING_VALID_POSITION_CHARACTERS
    [FEN_STRING_NUMBER_OF_VALID_POSITION_CHARACTERS] = {
        'p', 'n', 'b', 'q', 'k', 'r', 'P', 'N', 'B', 'Q', 'K',
        'R', '/', '1', '2', '3', '4', '5', '6', '7', '8', '-'};

const char FEN_STRING_VALID_SIDE_CHARACTERS[NUMBEROFCOLORS] = {'w', 'b'};

const char FEN_STRING_VALID_CASTLING_CHARACTERS
    [FEN_STRING_NUMBER_CASTLING_CHARACTERS] = {
        FEN_STRING_NO_VALUE, FEN_STRING_CASTLING_WHITE_QUEEN_SIDE,
        FEN_STRING_CASTLING_WHITE_KING_SIDE,
        FEN_STRING_CASTLING_BLACK_QUEEN_SIDE,
        FEN_STRING_CASTLING_BLACK_KING_SIDE};

void initFenString(char *string, int stringLen, fenString *fenString) {
  const char *EXAMPLE_VALID_STRING =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  if (stringLen < FEN_STRING_MIN_CHARACTERS) {
    printf("Error FEN string min characters are %d, your string has %d, valid "
           "FEN string example: %s\n",
           FEN_STRING_NUMBER_CASTLING_CHARACTERS, stringLen,
           EXAMPLE_VALID_STRING);
    return;
  }
  int i;
  fenString->string = string;
  fenString->stringLen = stringLen;

  intPair piecePositionIndex = {-1, -1};
  int sideToMoveIndex = -1;
  intPair castlingIndex = {-1, -1};
  intPair enPassantIndex = {-1, -1};
  intPair halfMoveIndex = {-1, -1};
  intPair fullMoveIndex = {-1, -1};

  int spaceNumber = 0;

  for (i = 0; i < stringLen; i++) {
    char currentChar = string[i];
    if (currentChar == ' ') {
      switch (spaceNumber) {
      case 0:
        piecePositionIndex.first = 0;
        piecePositionIndex.second = i - 1;
        break;
      case 1:
        sideToMoveIndex = i - 1;
        break;
      case 2:
        castlingIndex.first = sideToMoveIndex + 2;
        castlingIndex.second = i - 1;
        break;
      case 3:
        enPassantIndex.first = castlingIndex.second + 2;
        enPassantIndex.second = i - 1;
        break;
      case 4:
        halfMoveIndex.first = enPassantIndex.second + 2;
        halfMoveIndex.second = i - 1;
        break;
      default:
        break;
      }
      spaceNumber++;
    }
  }

  if (spaceNumber != 5) {
    printf("FEN strings should have at least 5 spaces, like: %s \n",
           EXAMPLE_VALID_STRING);
    return;
  }

  fullMoveIndex.first = halfMoveIndex.second + 2;
  fullMoveIndex.second = stringLen - 1;

  fenString->piecesPositions = piecePositionIndex;
  fenString->sideToMove = sideToMoveIndex;
  fenString->castling = castlingIndex;
  fenString->passant = enPassantIndex;
  fenString->halfMove = halfMoveIndex;
  fenString->fullMove = fullMoveIndex;
}

static int checkCharInList(char val, const char *list, int listLen) {
  int found = 0;
  for (int i = 0; i < listLen; i++) {
    char charInList = list[i];
    if (charInList == val) {
      found = 1;
      break;
    }
  }
  return found;
}

bool checkValidFenStringPart2(const char *string, int start) {

  char sideToMoveChar = string[start];
  int valid = checkCharInList(sideToMoveChar, FEN_STRING_VALID_SIDE_CHARACTERS,
                              NUMBEROFCOLORS);
  if (!valid) {
    printf("Error parsing character: %c at index: %d is not valid, should be "
           "w or b\n ",
           sideToMoveChar, start);
    return false;
  }
  return true;
}

bool checkValidFenStringPart3(const char *string, int start, int end) {
  for (int i = start; i <= end; i++) {
    char val = string[i];
    int valid = checkCharInList(val, FEN_STRING_VALID_CASTLING_CHARACTERS,
                                FEN_STRING_NUMBER_CASTLING_CHARACTERS);
    if (!valid) {
      printf("Error parsing character %c at index %d, valid characters are: ",
             val, i);
      for (int j = 0; j < FEN_STRING_NUMBER_CASTLING_CHARACTERS; j++) {
        printf("%c ", FEN_STRING_VALID_CASTLING_CHARACTERS[j]);
      }
      printf("\n");
      return false;
    }
  }
  return true;
}

// TODO: extract the logic of taking a string a parse number to a util function
bool checkValidFenStringNumberVals(const char *string, int start, int end,
                                   int limit) {
  char numberStr[5];
  int c = 0;
  for (int i = start; i <= end; i++) {
    char val = string[i];
    if (isdigit(val)) {
      numberStr[c] = val;
      c++;
    } else if (val == FEN_STRING_NO_VALUE) {
      return 1;
    } else {
      printf(
          "Error parsing FEN string at index %d, %c should be a number [0-9]\n",
          i, val);
      return false;
    }
  }
  numberStr[c] = '\0';
  int number = atoi(numberStr);
  if (number > limit) {
    printf("Error parsing FEN string limit number is %d, provided "
           "number is %d\n",
           limit, number);
    return false;
  }
  return true;
}

bool checkValidFenStringPart1(const char *string, int start, int end) {
  for (int i = start; i <= end; i++) {
    char val = string[i];
    int valid = checkCharInList(val, FEN_STRING_VALID_POSITION_CHARACTERS,
                                FEN_STRING_NUMBER_OF_VALID_POSITION_CHARACTERS);
    if (!valid) {
      printf("Error parsing character %c at index %d, valid characters are "
             "[aA-rR] [1-8] or [/]\n",
             val, i);
      return false;
    }
  }
  return true;
}

bool checkValidFenString(const fenString *fenString) {
  bool nullValid, valid1, valid2, valid3, valid4, valid5, valid6 = 1;
  if (fenString == NULL || fenString->string == NULL) {
    nullValid = 0;
    printf("NULL pointer to FEN string\n");
    return nullValid;
  }
  valid1 = checkValidFenStringPart1(fenString->string,
                                    fenString->piecesPositions.first,
                                    fenString->piecesPositions.second);
  valid2 = checkValidFenStringPart2(fenString->string, fenString->sideToMove);
  valid3 = checkValidFenStringPart3(
      fenString->string, fenString->castling.first, fenString->castling.second);
  valid4 = checkValidFenStringNumberVals(
      fenString->string, fenString->passant.first, fenString->passant.second,
      FEN_STRING_LIMIT_EN_PASSANT);
  valid5 = checkValidFenStringNumberVals(
      fenString->string, fenString->halfMove.first, fenString->halfMove.second,
      FEN_STRING_LIMIT_HALF_MOVE);
  valid6 = checkValidFenStringNumberVals(
      fenString->string, fenString->fullMove.first, fenString->fullMove.second,
      FEN_STRING_LIMIT_FULL_MOVE);
  return valid1 && valid2 && valid3 && valid4 && valid5 && valid6;
}

static void assingPiece(int *boardSquare, int color, int pieceType,
                        bitBoardsList *bbl) {
  bitboard mask = 1ULL << *boardSquare;
  bbl->pieces[color][pieceType] |= mask;
  (*boardSquare)++;
}

void initBoardWithFenString(board *board, char *string, int stringLen) {
  fenString fenString;
  initFenString(string, stringLen, &fenString);
  bool valid = checkValidFenString(&fenString);
  if (!valid) {
    printf("invalid FEN string \n");
    return;
  }
  // TODO : CHANGE ZOOBRIST KEY
  initBitBoardListWithFenString(&board->bitBoardsList, &fenString);
  board->gameState.playingSide = getSideFromFenString(&fenString);
  board->gameState.castlingCode = getCastlingCodeFromFenString(&fenString);
  board->gameState.halfMoveCounter = getHalfMovesFromFenString(&fenString);
  board->gameState.fullMoveCounter = getFullMovesFromFenString(&fenString);
}

static int parseIntFromString(const char *string, int from, int to) {
  char subString[to - from + 2]; // +1 for null terminator, +1 for length
  for (int i = from, j = 0; i <= to; i++, j++) {
    subString[j] = string[i];
  }
  subString[to - from + 1] = '\0';
  return atoi(subString);
}

PASSANT_KEYS getPassantCodeFromFenString(const fenString *fenString) {
  if (fenString->string[fenString->passant.first] == FEN_STRING_NO_VALUE) {
    return NO_PASSANT;
  }
  // NOTE: Here we use the fact that in the FEN string passant section
  // 1 means that the white pawn at the H column can passant THIS WILL ONLY WORK
  // AS LONG AS THE PASSANT_KEYS ENUM IS IN ORDER!
  return parseIntFromString(fenString->string, fenString->passant.first,
                            fenString->passant.second);
}

int getHalfMovesFromFenString(const fenString *fenString) {
  return parseIntFromString(fenString->string, fenString->halfMove.first,
                            fenString->halfMove.second);
}

int getFullMovesFromFenString(const fenString *fenString) {
  return parseIntFromString(fenString->string, fenString->fullMove.first,
                            fenString->fullMove.second);
}

COLOR getSideFromFenString(fenString *fenString) {
  char side = fenString->string[fenString->sideToMove];
  if (side == 'w') {
    return COLOR_WHITE;
  } else {
    return COLOR_BLACK;
  }
}

CASTLING_KEYS getCastlingCodeFromFenString(const fenString *fenString) {
  bool whiteKingside = false;
  bool whiteQueenside = false;
  bool blackKingside = false;
  bool blackQueenside = false;

  for (int i = fenString->castling.first; i <= fenString->castling.second;
       i++) {
    switch (fenString->string[i]) {
    case 'K':
      whiteKingside = true;
      break;
    case 'Q':
      whiteQueenside = true;
      break;
    case 'k':
      blackKingside = true;
      break;
    case 'q':
      blackQueenside = true;
      break;
    }
  }

  if (whiteKingside && whiteQueenside && blackKingside && blackQueenside) {
    return BOTH_ALL;
  } else if (whiteKingside && whiteQueenside && blackKingside) {
    return WHITE_BOTH_BLACK_KINGSIDE;
  } else if (whiteKingside && whiteQueenside && blackQueenside) {
    return WHITE_BOTH_BLACK_QUEENSIDE;
  } else if (whiteKingside && whiteQueenside && blackKingside &&
             !blackQueenside) {
    return WHITE_BOTH_BLACK_QUEENSIDE;
  } else if (whiteKingside && whiteQueenside) {
    return WHITE_BOTH;
  } else if (blackKingside && blackQueenside) {
    return BLACK_BOTH;
  } else if (whiteKingside && blackKingside) {
    return WHITE_KINGSIDE_BLACK_KINGSIDE;
  } else if (whiteKingside && blackQueenside) {
    return WHITE_KINGSIDE_BLACK_QUEENSIDE;
  } else if (whiteQueenside && blackKingside) {
    return WHITE_QUEENSIDE_BLACK_KINGSIDE;
  } else if (whiteQueenside && blackQueenside) {
    return WHITE_QUEENSIDE_BLACK_QUEENSIDE;
  } else if (whiteKingside) {
    return WHITE_KINGSIDE;
  } else if (whiteQueenside) {
    return WHITE_QUEENSIDE;
  } else if (blackKingside) {
    return BLACK_KINGSIDE;
  } else if (blackQueenside) {
    return BLACK_QUEENSIDE;
  } else {
    return NO_CASTLING;
  }
}

void initBitBoardListWithFenString(bitBoardsList *bbl, fenString *fenString) {
  cleanBitBoardList(bbl);
  int boardSquare = 0;
  for (int i = fenString->piecesPositions.first;
       i <= fenString->piecesPositions.second; i++) {
    switch (fenString->string[i]) {
    case 'p':
      assingPiece(&boardSquare, COLOR_WHITE, PIECE_PAWN, bbl);
      break;
    case 'P':
      assingPiece(&boardSquare, COLOR_BLACK, PIECE_PAWN, bbl);
      break;
    case 'r':
      assingPiece(&boardSquare, COLOR_WHITE, PIECE_ROOK, bbl);
      break;
    case 'R':
      assingPiece(&boardSquare, COLOR_BLACK, PIECE_ROOK, bbl);
      break;
    case 'n':
      assingPiece(&boardSquare, COLOR_WHITE, PIECE_KNIGHT, bbl);
      break;
    case 'N':
      assingPiece(&boardSquare, COLOR_BLACK, PIECE_KNIGHT, bbl);
      break;
    case 'b':
      assingPiece(&boardSquare, COLOR_WHITE, PIECE_BISHOP, bbl);
      break;
    case 'B':
      assingPiece(&boardSquare, COLOR_BLACK, PIECE_BISHOP, bbl);
      break;
    case 'q':
      assingPiece(&boardSquare, COLOR_WHITE, PIECE_QUEEN, bbl);
      break;
    case 'Q':
      assingPiece(&boardSquare, COLOR_BLACK, PIECE_QUEEN, bbl);
      break;
    case 'k':
      assingPiece(&boardSquare, COLOR_WHITE, PIECE_KING, bbl);
      break;
    case 'K':
      assingPiece(&boardSquare, COLOR_BLACK, PIECE_KING, bbl);
      break;
    case '-':
      boardSquare++;
      break;
    case '/':
      // Do nothing
      break;
    default:
      // Quick and dirty number conversion
      boardSquare = boardSquare + (fenString->string[i] - '0');
      break;
    }
  }
}
