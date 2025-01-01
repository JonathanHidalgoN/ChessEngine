#include "../../include/board/history.h"

history *getCleanHistory(history *history) {
  for (int i = 0; i < MAXTURNS; i++) {
    gameState dummyGameState = {0, 0, 0, 0, 0, 0ULL, 0};
    history->states[i] = dummyGameState;
  }
  history->len = 0;
  return history;
}
void pushIntoHistory(history *history, gameState *gameState) {
  history->states[history->len] = *gameState;
  history->len += 1;
}

gameState *popFromHistory(history *history) {
  history->len -= 1;
  return &history->states[history->len];
}

int getLenHistory(history *history) { return history->len; }

gameState *getCurrentGameStateFromHistory(history *history) {
  return &history->states[history->len - 1];
}
