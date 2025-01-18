#ifndef GAME_STATE
#define GAME_STATE

#include "bitBoard.h"
#include "boardEncoding.h"
#include "defs.h"
#include "pieceList.h"

typedef struct gameState {
  COLOR playingSide;
  CASTLING_KEYS castlingCode;
  int halfMoveCounter;
  PASSANT_KEYS enPassantCode;
  int fullMoveCounter;
  uint64_t zobristKey;
  int phaseValue;
} gameState;

#endif // !GAME_STATE
