#ifndef TEST_H
#define TEST_H

#include "../include/board/board.h"
#include "utils.h"
#include <stdio.h>
#define DEBUG 1
#define BIT(n) (1ULL << (n))

void testBoard();
void testAttacks();
void testMoveGeneration();
void testHistory();
void testPieceList();
#endif
