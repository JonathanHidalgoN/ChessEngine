#ifndef BOARD_H
#define BOARD_H
#include "boardEncoding.h"
#include "defs.h"
#include "history.h"
#include "pieceList.h"

typedef struct board {
  bitBoardsList bitBoardsList;
  gameState gameState;
  history history;
  zobristRandoms zobristRandoms;
  pieceList pieceList;
} board;

void removePiece(board *board, int square, int side, int piece);
void putPiece(board *board, int square, int side, int piece);
// NOTE: this do not eat the piece where its going
void movePiece(board *board, int from, int to, int side, int piece);
//-------------------------------------------------------------------------------------------
// NOTE: This functions could be in gameState.h but we need the zoobristRandoms,
// from the board, maybe move those into gameState? I dont like that so thats
// why these functtions are here
void changePassant(board *board, int passantCode);
void changePlayingSide(board *board);
void changeCastling(board *board, int castlingCode);
void cleanGameState(board *board);
//-------------------------------------------------------------------------------------------
// void cleanBoard(board *board);
#endif
