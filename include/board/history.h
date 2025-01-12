#ifndef HISTORY_H
#define HISTORY_H

#include "defs.h"
#include "gameState.h"

// This is like a stack
typedef struct history {
  gameState states[MAXTURNS];
  int len;
} history;

void cleanHistory(history *hist);
void pushIntoHistory(history *history, gameState *gameState);
gameState *popFromHistory(history *history);
int getLenHistory(const history *history);
gameState *getCurrentGameStateFromHistory(history *history);

#endif // !HISTORY_H
