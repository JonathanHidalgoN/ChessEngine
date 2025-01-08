#include "../../include/board/FEN-strings.h"
#include <stdio.h>

void initFenString(char *string, int stringLen, fenString *fenString) {
  fenString->string = string;
  fenString->stringLen = stringLen;
  intPair piecePositionIndex = {-1, -1};
  int sideToMoveIndex = 0;
  intPair castlingIndex = {-1, -1};
  int enPassantIndex = 0;
  intPair halfMoveIndex = {-1, -1};
  intPair fullMoveIndex = {-1, -1};
  int i;
  int spaceNumber = 0;
  for (i = 0; i < stringLen; i++) {
    char currentChar = string[i];
    if (currentChar == ' ' && spaceNumber == 0) {
      piecePositionIndex.first = 0;
      piecePositionIndex.second = i - 1;
    }
    if (currentChar == ' ' && spaceNumber == 1) {
      sideToMoveIndex = i - 1;
    }
    if (currentChar == ' ' && spaceNumber == 2) {
      castlingIndex.first = sideToMoveIndex + 1;
      castlingIndex.second = i - 1;
    }
    if (currentChar == ' ' && spaceNumber == 3) {
      enPassantIndex = i - 1;
    }
    if (currentChar == ' ' && spaceNumber == 4) {
      halfMoveIndex.first = enPassantIndex + 1;
      halfMoveIndex.second = i - 1;
    }
  }
  if (spaceNumber != 4) {
    printf("FEN strings should have at 4 spaces, like : "
           "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\n");
  }
  fullMoveIndex.first = halfMoveIndex.second + 1;
  fullMoveIndex.second = stringLen;
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

int checkValidFenStringPart1(fenString *fenString) {
  for (int i = fenString->piecesPositions.first;
       i < fenString->piecesPositions.second; i++) {
    char val = fenString->string[i];
    int valid = checkCharInList(val, FEN_STRING_VALID_POSITION_CHARACTERS,
                                FEN_STRING_NUMBER_OF_VALID_POSITION_CHARACTERS);
    if (!valid) {
      printf("Error parsing character %c at index %d, valid characters are "
             "[aA-rR] [1-8] or [/]\n",
             val, i);
      return 0;
    }
  }
  return 1;
}

int checkValidFenStringPart2(fenString *fenString) {

  char sideToMoveChar = fenString->string[fenString->sideToMove];
  int valid = checkCharInList(sideToMoveChar, FEN_STRING_VALID_SIDE_CHARACTERS,
                              NUMBEROFCOLORS);
  if (!valid) {
    printf("Character in FEN string: %c at index: %d is not valid, should be "
           "w or b\n ",
           sideToMoveChar, fenString->sideToMove);
    return 0;
  }
  return 1;
}

int checkValidFenString(fenString *fenString) {
  int nullValid, valid1, valid2, valid3, valid4, valid5, valid6 = 1;
  if (fenString == NULL || fenString->string == NULL) {
    nullValid = 0;
    printf("NULL pointer to FEN string\n");
    return nullValid;
  }
  valid1 = checkValidFenStringPart1(fenString);
  valid2 = checkValidFenStringPart2(fenString);
  return nullValid;
}
