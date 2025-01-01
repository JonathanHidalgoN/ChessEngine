#include "../../include/board/history.h"
#include "../test.h"
#include <stdio.h>

int testPushIntoHistory() {
  history history;
  cleanHistory(&history);
  // Test case 2: Pushing a state for WHITE
  gameState testGameState = {WHITE, 1, 2, 3, 4, 1ULL, 5};
  int expectedIndex = 0;
  pushIntoHistory(&history, &testGameState);
  if (!areGameStatesEqual(&testGameState, &history.states[expectedIndex])) {
    printf("Error in pushIntoHistory function case 1\n");
    return 0;
  } // Test case 2: Pushing a state for BLACK
  gameState testGameState2 = {BLACK, 2, 1, 0, 2, 12345ULL, 3};
  int expectedIndex2 = 1;
  pushIntoHistory(&history, &testGameState2);
  if (!areGameStatesEqual(&testGameState2, &history.states[expectedIndex2])) {
    printf("Error in pushIntoHistory function case 2\n");
    return 0;
  }

  // Test case 3: Handling an empty state (default initialization)
  gameState testGameState3 = {0, 0, 0, 0, 0, 0ULL, 0};
  int expectedIndex3 = 2;
  pushIntoHistory(&history, &testGameState3);
  if (!areGameStatesEqual(&testGameState3, &history.states[expectedIndex3])) {
    printf("Error in pushIntoHistory function case 3\n");
    return 0;
  }

  // Test case 4: Large Zobrist Key
  gameState testGameState4 = {WHITE, 10, 20, 5, 3, 0xFFFFFFFFFFFFFFFFULL, 7};
  int expectedIndex4 = 3;
  pushIntoHistory(&history, &testGameState4);
  if (!areGameStatesEqual(&testGameState4, &history.states[expectedIndex4])) {
    printf("Error in pushIntoHistory function case 4\n");
    return 0;
  }

  // Test case 5: Handling repeated pushes of the same state
  gameState testGameState5 = {WHITE, 1, 1, 1, 1, 67890ULL, 4};
  int expectedIndex5 = 4;
  pushIntoHistory(&history, &testGameState5);
  if (!areGameStatesEqual(&testGameState5, &history.states[expectedIndex5])) {
    printf("Error in pushIntoHistory function case 5\n");
    return 0;
  }

  // Test case 6: Edge case - Castling flags set to an extreme value
  gameState testGameState6 = {BLACK, 0, 0, 0, 0xF, 99999ULL, 0};
  int expectedIndex6 = 5;
  pushIntoHistory(&history, &testGameState6);
  if (!areGameStatesEqual(&testGameState6, &history.states[expectedIndex6])) {
    printf("Error in pushIntoHistory function case 6\n");
    return 0;
  }

  // Test case 7: Zobrist Key collision scenario (same key, different states)
  gameState testGameState7 = {WHITE, 3, 4, 5, 6, 12345ULL, 9};
  int expectedIndex7 = 6;
  pushIntoHistory(&history, &testGameState7);
  if (!areGameStatesEqual(&testGameState7, &history.states[expectedIndex7])) {
    printf("Error in pushIntoHistory function case 7\n");
    return 0;
  }

  // Test case 8: Push state after a large number of moves
  gameState testGameState8 = {BLACK, 100, 50, 25, 1, 54321ULL, 8};
  int expectedIndex8 = 7;
  pushIntoHistory(&history, &testGameState8);
  if (!areGameStatesEqual(&testGameState8, &history.states[expectedIndex8])) {
    printf("Error in pushIntoHistory function case 8\n");
    return 0;
  }
  return 1;
}

int testPopFromHistory() { return 1; }

int testGetLenHistory() { return 1; }

int testGetCurrentGameStateFromHistory() { return 1; }

void testHistory() {
  int testPushIntoHistoryResult = testPushIntoHistory();
  int testPopFromHistoryResult = testPopFromHistory();
  int testGetLenHistoryResult = testGetLenHistory();
  int testGetCurrentGameStateFromHistoryResult =
      testGetCurrentGameStateFromHistory();
  if (testPopFromHistoryResult && testPushIntoHistoryResult &&
      testGetCurrentGameStateFromHistoryResult && testGetLenHistoryResult) {
    printf("History tested successfully \n");
  }
}
