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
#include "bitBoard.h"
#include "defs.h"
#include <stdint.h>

#define NKEYSFORPIECES                                                         \
  (NUMBEROFSQUARES * NUMBEROFDIFFERENTPIECES * NUMBEROFCOLORS)
#define NKEYSFORCASTLING 16
#define NKEYSFORSIDES 2
#define NKEYSFORPASSANT 17

typedef struct zobristRandoms {
  uint64_t pieceRandoms[NKEYSFORPIECES];
  uint64_t castlingRandoms[NKEYSFORCASTLING];
  uint64_t sidesRandoms[NKEYSFORSIDES];
  uint64_t passantRandoms[NKEYSFORPASSANT];
} zobristRandoms;

void fillZobristRandoms(zobristRandoms *randoms);
uint64_t computeZobristFromBoard(zobristRandoms *randoms,
                                 bitBoardsList *bitBoardsList, int side,
                                 int castlingCode, int passantCode);

#endif // !BOARD_ENCODING_H
