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

#define NKEYSFORCASTLING 16
#define NKEYSFORSIDES 2
#define NKEYSFORPASSANT 17

typedef enum {
  NO_PASSANT,
  W1,
  W2,
  W3,
  W4,
  W5,
  W6,
  W7,
  W8,
  B1,
  B2,
  B3,
  B4,
  B5,
  B6,
  B7,
  B8
} PASSANT_KEYS;

typedef enum {
  NO_CASTLING,
  WHITE_KINGSIDE,
  WHITE_QUEENSIDE,
  BLACK_KINGSIDE,
  BLACK_QUEENSIDE,
  WHITE_BOTH,
  BLACK_BOTH,
  WHITE_KINGSIDE_BLACK_KINGSIDE,
  WHITE_KINGSIDE_BLACK_QUEENSIDE,
  WHITE_QUEENSIDE_BLACK_KINGSIDE,
  WHITE_QUEENSIDE_BLACK_QUEENSIDE,
  WHITE_BOTH_BLACK_KINGSIDE,
  WHITE_BOTH_BLACK_QUEENSIDE,
  BOTH_ALL
} CASTLING_KEYS;

typedef struct zobristRandoms {
  uint64_t pieceRandoms[NUMBEROFSQUARES][NUMBEROFCOLORS]
                       [NUMBEROFDIFFERENTPIECES];
  uint64_t castlingRandoms[NKEYSFORCASTLING];
  uint64_t sidesRandoms[NKEYSFORSIDES];
  uint64_t passantRandoms[NKEYSFORPASSANT];
} zobristRandoms;

void fillZobristRandoms(zobristRandoms *randoms);
uint64_t computeZobristFromBoard(zobristRandoms *randoms,
                                 bitBoardsList *bitBoardsList, int side,
                                 int castlingCode, int passantCode);

#endif // !BOARD_ENCODING_H
