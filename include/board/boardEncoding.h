/*
 * This section is to encode the board positions into
 * something that is faster to process and store, we will use
 * zobrist hashing
 *https://www.chessprogramming.org/index.php?title=Zobrist_Hashing&mobileaction=toggle_view_desktop
 * A lot of the code here is inspired by :
 *https://rustic-chess.org/board_representation/zobrist_hashing.html
 */
#ifndef BOARD_ENCODING_H
#define BOARD_ENCODING_H
#include "../random.h"
#include "boardConstants.h"
#include <stdint.h>

const int keysForPieces =
    (int)NUMBEROFSQUARES * NUMBEROFDIFFERENTPIECES * PLAYERS;
const int keysForCastling = 16;
const int keysForSides = 2;
const int keysForPassant = 17;

typedef struct zobristRandoms {
  uint64_t pieceRandoms[keysForPieces];
  uint64_t castlingRandoms[keysForCastling];
  uint64_t sidesRandoms[keysForSides];
  uint64_t passantRandoms[keysForPassant];
} zobristRandoms;

void fillZobristRandoms(zobristRandoms *randoms);

#endif // !BOARD_ENCODING_H
