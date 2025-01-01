#ifndef HISTORY_H
#define HISTORY_H

#include "defs.h"

// This is like a stack
typedef struct history {
  gameState states[MAXTURNS];
  int len;
} history;

void pushIntoHistory(history *history, gameState *gameState);
gameState *popFromHistory(history *history);
int getLenHistory(history *history);
gameState *getCurrentGameStateFromHistory(history *history);

#endif // !HISTORY_H
