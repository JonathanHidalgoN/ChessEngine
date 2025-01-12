#ifndef GAME_STATE
#define GAME_STATE

#include "bitBoard.h"
#include "defs.h"
#include "pieceList.h"

typedef struct gameState {
  int playingSide;
  int castlingCode;
  int halfMoveCounter;
  int enPassantCode;
  int fullMoveCounter;
  uint64_t zobristKey;
  int phaseValue;
  bitBoardsList bitBoardsList;
  pieceList pieceList;
} gameState;

#endif // !GAME_STATE
