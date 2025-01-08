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
