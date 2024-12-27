#ifndef ATTACKS_H
#define ATTACKS_H
#include "../include/board.h"
#include "../include/random.h"
#define BOARD_INDEX(row, col) ((col) + (ROWS * (row)))
/**
 Given a bitIndex and the side(0 white 1 black) returns a bitboard
 with 1's where the pawn can attack
 */
bitboard computePawnAttack(int bitIndex, int side);
/**
 Given the bitIndex returns a bitboard with 1's where the piece can
 attack
 */
bitboard computeKnightAttack(int bitIndex);
/**
 Given the bitIndex returns a bitboard with 1's where the piece can
 attack
 */
bitboard computeKingAttack(int bitIndex);
/**
 Given the bitIndex and a bitboard with the pieces
 on the board returns a bitboard with 1's where the piece can
 attack
 */
bitboard computeBishopAttack(int bitIndex, bitboard blockers);
/**
 Given the bitIndex and a bitboard with the pieces
 on the board returns a bitboard with 1's where the piece can
 attack
 */
bitboard computeRookAttack(int bitIndex, bitboard blockers);
/**
 Given a bitIndex return the bitboard with 1's whose occupancy
 can affect the piece attacks
 */
bitboard maskBishopAttack(int bitIndex);
/**
 Given a bitIndex return the bitboard with 1's whose occupancy
 can affect the piece attacks
 */
bitboard maskRookAttack(int bitIndex);
/**
Populate the pieceAttack table
 */
void fillPawnAttackTable(
    bitboard pawnAttackTable[NUMBEROFCOLORS][NUMBEROFSQUARES]);
/**
Populate the pieceAttack table
 */
void fillKnightAttackTable(bitboard knightAttackTable[NUMBEROFSQUARES]);
/**
Populate the pieceAttack table
 */
void fillKingAttackTable(bitboard kingAttackTable[NUMBEROFSQUARES]);
/*
This function computes all index(possible) permutations of the bitsInMask
1's bits in attackMask source :
https://www.youtube.com/watch?v=UnEu5GOiSEs&list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs&index=15
 * */
bitboard setOccupancy(int possibleConfigs, int onesInMask, bitboard attackMask);
/**
Populate the pieceAttack table
 */
void fillRookAttackTable();
/**
Populate the pieceAttack table
 */
void fillbishopAttackTable();
/**
 Getting the rock attack implies doing a lookup
 thats why we need the bitIndex(position) and the the board
 (where are the other pieces)
 */
bitboard getRookAttack(int bitIndex, bitboard board);
/**
 Getting the bishop attack implies doing a lookup
 thats why we need the bitIndex(position) and the the board
 (where are the other pieces)
 */
bitboard getBishopAttack(int bitIndex, bitboard board);

#endif
