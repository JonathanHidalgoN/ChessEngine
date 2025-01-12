#include "../../include/board/history.h"

void cleanHistory(history *hist) {
  bitBoardsList bbl;
  pieceList pieceList;
  cleanBitBoardList(&bbl);
  cleanPieceList(&pieceList);
  for (int i = 0; i < MAXTURNS; i++) {
    gameState dummyGameState = {0, 0, 0, 0, 0, 0ULL, 0};
    hist->states[i] = dummyGameState;
  }
  hist->len = 0;
}

void pushIntoHistory(history *history, gameState *gameState) {
  history->states[history->len] = *gameState;
  history->len += 1;
}

gameState *popFromHistory(history *history) {
  if (history->len == 0) {
    printf("History will return null, error will occur\n");
    return NULL;
  }
  history->len -= 1;
  return &history->states[history->len];
}

int getLenHistory(const history *history) { return history->len; }

gameState *getCurrentGameStateFromHistory(history *history) {
  return &history->states[history->len - 1];
}
