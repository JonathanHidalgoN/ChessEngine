#include "../../include/board/history.h"
#include "../test.h"
#include <stdio.h>

// TODO: : I dont like this test because we know that its not a stack but an
// array inside, maybe integration test would be better for this

int testPushIntoHistory() {
  bitBoardsList bbl;
  cleanBitBoardList(&bbl);
  pieceList pieceList;
  cleanPieceList(&pieceList);

  history history;
  cleanHistory(&history);
  // Test case 1: Pushing a state for WHITE
  gameState testGameState = {WHITE, 1, 2, 3, 4, 1ULL, 5, bbl, pieceList};
  int expectedIndex = 0;
  pushIntoHistory(&history, &testGameState);
  if (!areGameStatesEqual(&testGameState, &history.states[expectedIndex])) {
    printf(RED "Error in pushIntoHistory function case 1\n" RESET);
    return 0;
  } // Test case 2: Pushing a state for BLACK
  gameState testGameState2 = {BLACK, 2, 1, 0, 2, 12345ULL, 3, bbl, pieceList};
  int expectedIndex2 = 1;
  pushIntoHistory(&history, &testGameState2);
  if (!areGameStatesEqual(&testGameState2, &history.states[expectedIndex2])) {
    printf(RED "Error in pushIntoHistory function case 2\n" RESET);
    return 0;
  }

  // Test case 3: Handling an empty state (default initialization)
  gameState testGameState3 = {0, 0, 0, 0, 0, 0ULL, 0, bbl, pieceList};
  int expectedIndex3 = 2;
  pushIntoHistory(&history, &testGameState3);
  if (!areGameStatesEqual(&testGameState3, &history.states[expectedIndex3])) {
    printf(RED "Error in pushIntoHistory function case 3\n" RESET);
    return 0;
  }

  // Test case 4: Large Zobrist Key
  gameState testGameState4 = {WHITE, 10,  20,       5, 3, 0xFFFFFFFFFFFFFFFFULL,
                              7,     bbl, pieceList};
  int expectedIndex4 = 3;
  pushIntoHistory(&history, &testGameState4);
  if (!areGameStatesEqual(&testGameState4, &history.states[expectedIndex4])) {
    printf(RED "Error in pushIntoHistory function case 4\n" RESET);
    return 0;
  }

  // Test case 5: Handling repeated pushes of the same state
  gameState testGameState5 = {WHITE, 1, 1, 1, 1, 67890ULL, 4, bbl, pieceList};
  int expectedIndex5 = 4;
  pushIntoHistory(&history, &testGameState5);
  if (!areGameStatesEqual(&testGameState5, &history.states[expectedIndex5])) {
    printf(RED "Error in pushIntoHistory function case 5\n" RESET);
    return 0;
  }

  // Test case 6: Edge case - Castling flags set to an extreme value
  gameState testGameState6 = {BLACK, 0, 0, 0, 0xF, 99999ULL, 0, bbl, pieceList};
  int expectedIndex6 = 5;
  pushIntoHistory(&history, &testGameState6);
  if (!areGameStatesEqual(&testGameState6, &history.states[expectedIndex6])) {
    printf(RED "Error in pushIntoHistory function case 6\n" RESET);
    return 0;
  }

  // Test case 7: Zobrist Key collision scenario (same key, different states)
  gameState testGameState7 = {WHITE, 3, 4, 5, 6, 12345ULL, 9, bbl, pieceList};
  int expectedIndex7 = 6;
  pushIntoHistory(&history, &testGameState7);
  if (!areGameStatesEqual(&testGameState7, &history.states[expectedIndex7])) {
    printf(RED "Error in pushIntoHistory function case 7\n" RESET);
    return 0;
  }

  // Test case 8: Push state after a large number of moves
  gameState testGameState8 = {BLACK,    100, 50,  25,       1,
                              54321ULL, 8,   bbl, pieceList};
  int expectedIndex8 = 7;
  pushIntoHistory(&history, &testGameState8);
  if (!areGameStatesEqual(&testGameState8, &history.states[expectedIndex8])) {
    printf(RED "Error in pushIntoHistory function case 8\n" RESET);
    return 0;
  }
  return 1;
}

int testPopFromHistory() {
  history history;
  bitBoardsList bbl;
  cleanBitBoardList(&bbl);
  pieceList pieceList;
  cleanPieceList(&pieceList);
  cleanHistory(&history);

  // Test case 1: Normal case
  gameState expectedGameState = {WHITE, 1, 2, 3, 4, 1ULL, 5, bbl, pieceList};
  int len = 10;
  history.len = len;
  int expectedLen = len - 1;
  gameState *resultGameState = popFromHistory(&history);
  history.states[expectedLen] = expectedGameState;
  if (!areGameStatesEqual(&expectedGameState, resultGameState) ||
      history.len != expectedLen) {
    printf(RED "Error in pop from hisotry function case 0\n" RESET);
    return 0;
  }
  // Test case 2: Edge case - Pop from a single-element history
  cleanHistory(&history);
  history.len = 1;
  gameState expectedGameState2 = {WHITE, 1, 0, 0, 0, 1ULL, 0, bbl, pieceList};
  history.states[0] = expectedGameState2; // Single element
  int expectedLen2 = 0;
  gameState *resultGameState2 = popFromHistory(&history);
  if (!areGameStatesEqual(&expectedGameState2, resultGameState2) ||
      history.len != expectedLen2) {
    printf(RED "Error in popFromHistory function case 1\n" RESET);
    return 0;
  }
  // Test case 4: Multiple pops in sequence
  cleanHistory(&history);
  history.len = 3;
  gameState expectedGameState4a = {WHITE, 1, 1, 1, 1, 1ULL, 1, bbl, pieceList};
  gameState expectedGameState4b = {BLACK, 2, 2, 2, 2, 2ULL, 2, bbl, pieceList};
  gameState expectedGameState4c = {WHITE, 3, 3, 3, 3, 3ULL, 3, bbl, pieceList};
  history.states[0] = expectedGameState4a;
  history.states[1] = expectedGameState4b;
  history.states[2] = expectedGameState4c;

  // First pop
  gameState *resultGameState4a = popFromHistory(&history);
  if (!areGameStatesEqual(&expectedGameState4c, resultGameState4a) ||
      history.len != 2) {
    printf(RED "Error in popFromHistory function case 3a\n" RESET);
    return 0;
  }

  // Second pop
  gameState *resultGameState4b = popFromHistory(&history);
  if (!areGameStatesEqual(&expectedGameState4b, resultGameState4b) ||
      history.len != 1) {
    printf(RED "Error in popFromHistory function case 3b\n" RESET);
    return 0;
  }

  // Third pop
  gameState *resultGameState4c = popFromHistory(&history);
  if (!areGameStatesEqual(&expectedGameState4a, resultGameState4c) ||
      history.len != 0) {
    printf(RED "Error in popFromHistory function case 3c\n" RESET);
    return 0;
  }
  return 1;
}

void testHistory() {
  int testPushIntoHistoryResult = testPushIntoHistory();
  int testPopFromHistoryResult = testPopFromHistory();
  if (testPopFromHistoryResult && testPushIntoHistoryResult) {
    printf(GREEN "Tested history successfully \n" RESET);
  }
}
