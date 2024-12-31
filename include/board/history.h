#ifndef HISTORY_H
#define HISTORY_H

#include "defs.h"

// This is like a stack
typedef struct history {
  gameState state[MAXTURNS];
  int len;
} history;

void pushIntoHistory(history *history, gameState *gameState);
void popFromHistory(history *history, gameState *gameState);
int getLenHistory(history *history);
gameState *getCurrentGameStateFromHistory(history *history);

#endif // !HISTORY_H
