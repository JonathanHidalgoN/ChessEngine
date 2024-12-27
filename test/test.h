#ifndef TEST_H
#define TEST_H

#include "../include/board.h"
#include "utils.h"
#include <stdio.h>
#define DEBUG 1
#define BIT(n) (1ULL << (n))

void testBoard();
void testAttacks();
void testMoveGeneration();
#endif
