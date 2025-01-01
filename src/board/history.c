#include "../../include/board/history.h"

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
