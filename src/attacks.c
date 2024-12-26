#include "../include/attacks.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define DEBBUG 0

// THIS CONSTS REPRESENT THE BOARD BELOW THEM
const bitboard NOT_COL_0 = 18374403900871474942ULL;
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0
// 1 1 1 1 1 1 1 0

// Same logic wont put all the boards
const bitboard NOT_COL_7 = 9187201950435737471ULL;
const bitboard NOT_COL_01 = 18229723555195321596ULL;
const bitboard NOT_COL_67 = 4557430888798830399ULL;
// This follows the logic above but with rows
const bitboard NOT_ROW_0 = 18446744073709551360ULL;
const bitboard NOT_ROW_7 = 72057594037927935ULL;
const bitboard NOT_ROW_67 = 281474976710655ULL;
const bitboard NOT_ROW_01 = 18446744073709486080ULL;

// Max number of possible attacks per square for example a rook in h1 can attack
// up to 12 squares
const int occupancyRookMap[NUMBEROFSQUARES] = {
    12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 11, 11, 11, 11, 11, 12,
    10, 9,  10, 11, 11, 11, 11, 12, 9,  8,  9,  10, 11, 11, 11, 12,
    8,  7,  8,  9,  10, 11, 11, 12, 7,  6,  7,  8,  9,  10, 11, 12,
    6,  5,  6,  7,  8,  9,  10, 12, 6,  5,  6,  7,  8,  9,  10, 12};
const int occupancyBishopMap[NUMBEROFSQUARES] = {
    6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7,
    5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7,
    7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};
uint64_t rookMagicNumbers[NUMBEROFSQUARES] = {
    0x84000200000001eULL,  0x42c0015000000028ULL, 0x1002005001400000ULL,
    0x2810040800000100ULL, 0x2200041008200000ULL, 0x8840010042000000ULL,
    0x880022180000000ULL,  0x98060280800000ULL,   0x400404000000001ULL,
    0x844064000000003ULL,  0x8020a11100000000ULL, 0x1004a0000208ULL,
    0x11802400000002ULL,   0x441020200000000ULL,  0x4040491000000ULL,
    0x2c00880000000ULL,    0x600080804000001ULL,  0x809004000000024ULL,
    0x9910002000000008ULL, 0x8025001000000000ULL, 0x3208404b00000ULL,
    0x4000020010080000ULL, 0x808100600004000ULL,  0xb4011000822000ULL,
    0x1080220501000023ULL, 0x10400501008000ULL,   0x60008880001082ULL,
    0x8248c026b000000ULL,  0x4c138088000032cULL,  0xc10c000488000208ULL,
    0x110a0001000ULL,      0x405310001000ULL,     0x1000000010100000ULL,
    0x8000029002000200ULL, 0x401040081000001ULL,  0x1480000000620ULL,
    0x8109a94a00000102ULL, 0x40041100a0000406ULL, 0x2020410280080004ULL,
    0x828a68000002ULL,     0x811c300000430101ULL, 0x20000008800402cULL,
    0x1010042000004020ULL, 0x3001040014800a20ULL, 0x8300892400000100ULL,
    0x1329081000093ULL,    0x2088b0420000010ULL,  0x80c0308a09040000ULL,
    0x20028600208ULL,      0x4001282000500208ULL, 0x18814000051080ULL,
    0x881300280004100ULL,  0x401023080020009ULL,  0x4020801126008000ULL,
    0x2012140018c0000ULL,  0xa0a50800420000ULL,   0x8100802000a8001ULL,
    0x40000190000000a1ULL, 0x8001000100102021ULL, 0x201088404081008ULL,
    0x2810324884c02000ULL, 0x480218c010502240ULL, 0x63084008a00000ULL,
    0xc024804002ULL};

uint64_t bishopMagicNumbers[NUMBEROFSQUARES] = {
    0x202100400840040ULL,  0x5004108411002300ULL, 0x8008820410200000ULL,
    0x1e080a0820000580ULL, 0x8284042014820010ULL, 0x6829101210000004ULL,
    0x2000a80402200000ULL, 0x81010820840400ULL,   0x400300288031420ULL,
    0x2e00200431020030ULL, 0x80821000808116c0ULL, 0x2008041d020b1082ULL,
    0x2004340423000800ULL, 0x4082250100001ULL,    0x404108201064ULL,
    0x80020042280402ULL,   0x6004002020041108ULL, 0x4010000404082049ULL,
    0x90005a040a1820ULL,   0x100a000c202200a2ULL, 0xc064202202011420ULL,
    0x20005018e0110ULL,    0x10208208201a000ULL,  0x1881f200840191ULL,
    0x20224009080100ULL,   0x9914030020024400ULL, 0x18030111100cc205ULL,
    0x480a040008010820ULL, 0x2194082044002002ULL, 0x2008a20001004200ULL,
    0x40908041041004ULL,   0x881002200540404ULL,  0x4001082002082101ULL,
    0x8110408880880ULL,    0x8000404040080200ULL, 0x200020082180080ULL,
    0x1184440400114100ULL, 0xc220008020110412ULL, 0x4088084040090100ULL,
    0x8822104100121080ULL, 0x100111884008200aULL, 0x2844040288820200ULL,
    0x90901088003010ULL,   0x1000a218000400ULL,   0x1102010420204ULL,
    0x8414a3483000200ULL,  0x6410849901420400ULL, 0x201080200901040ULL,
    0x204880808050002ULL,  0x1001008201210000ULL, 0x16a6300a890040aULL,
    0x8049000441108600ULL, 0x2212002060410044ULL, 0x100086308020020ULL,
    0x484241408020421ULL,  0x105084028429c085ULL, 0x4282480801080cULL,
    0x81c098488088240ULL,  0x1400000090480820ULL, 0x4444000030208810ULL,
    0x1020142010820200ULL, 0x2234802004018200ULL, 0xc2040450820a00ULL,
    0x2101021090020ULL};
// To hold all possible attack patterns
bitboard rookMask[NUMBEROFSQUARES];
bitboard bishopMask[NUMBEROFSQUARES];
// A rook can attack at max 12 squares, 2**12 is 4096, this array holds all
// possible attack patterns for a rook in all possible boards
bitboard rookAttacks[NUMBEROFSQUARES][4096];
// Same for BISHOP but at max can attack 9 squares
bitboard bishopAttacks[NUMBEROFSQUARES][512];

bitboard computePawnAttack(int bitIndex, int side) {
  bitboard attacks = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  // side == 1 means black
  if (side) {
    attacks |= (mask >> 9) & NOT_COL_7;
    attacks |= (mask >> 7) & NOT_COL_0;
  } else {
    attacks |= (mask << 7) & NOT_COL_7;
    attacks |= (mask << 9) & NOT_COL_0;
  }
  return attacks;
}

bitboard computePawnForwardMove(int bitIndex, int side) {
  bitboard move = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  // side == 1 means black
  if (side) {
    move |= (mask >> 8);
  } else {
    move |= (mask << 8);
  }
  return move;
}

bitboard computeKnightAttack(int bitIndex) {
  bitboard attacks = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  attacks |= (mask << 17) & NOT_COL_0;
  attacks |= (mask << 10) & NOT_COL_01;
  attacks |= (mask << 15) & NOT_COL_7;
  attacks |= (mask << 6) & NOT_COL_67;
  attacks |= (mask >> 17) & NOT_COL_7;
  attacks |= (mask >> 10) & NOT_COL_67;
  attacks |= (mask >> 15) & NOT_COL_0;
  attacks |= (mask >> 6) & NOT_COL_01;
  return attacks;
}

bitboard computeKingAttack(int bitIndex) {
  bitboard attacks = 0;
  uint64_t mask = (uint64_t)1 << bitIndex;
  attacks |= computePawnAttack(bitIndex, 0);
  attacks |= computePawnAttack(bitIndex, 1);
  attacks |= (mask << 1) & NOT_COL_0;
  attacks |= (mask >> 1) & NOT_COL_7;
  attacks |= (mask << 8) & NOT_ROW_0;
  attacks |= (mask >> 8) & NOT_ROW_7;
  return attacks;
}

bitboard computeBishopAttack(int bitIndex, bitboard blockers) {
  bitboard attacks = 0;
  int col = bitIndex % COLS;
  int row = bitIndex / ROWS;
  int i, j;

  // Northeast direction
  for (i = col + 1, j = row + 1; i <= 7 && j <= 7; i++, j++) {
    attacks |= (1ULL << BOARD_INDEX(j, i));
    if ((1ULL << BOARD_INDEX(j, i)) & blockers)
      break;
  }

  // Northwest direction
  for (i = col - 1, j = row + 1; i >= 0 && j <= 7; i--, j++) {
    attacks |= (1ULL << BOARD_INDEX(j, i));
    if ((1ULL << BOARD_INDEX(j, i)) & blockers)
      break;
  }

  // Southeast direction
  for (i = col + 1, j = row - 1; i <= 7 && j >= 0; i++, j--) {
    attacks |= (1ULL << BOARD_INDEX(j, i));
    if ((1ULL << BOARD_INDEX(j, i)) & blockers)
      break;
  }

  // Southwest direction
  for (i = col - 1, j = row - 1; i >= 0 && j >= 0; i--, j--) {
    attacks |= (1ULL << BOARD_INDEX(j, i));
    if ((1ULL << BOARD_INDEX(j, i)) & blockers)
      break;
  }
  return attacks;
}

bitboard computeRookAttack(int bitIndex, bitboard blockers) {
  bitboard attacks = 0;
  int col = bitIndex % COLS;
  int row = bitIndex / ROWS;
  int i;

  // East direction
  for (i = col + 1; i <= 7; i++) {
    attacks |= (1ULL << BOARD_INDEX(row, i));
    if ((1ULL << BOARD_INDEX(row, i)) & blockers)
      break;
  }

  // West direction
  for (i = col - 1; i >= 0; i--) {
    attacks |= (1ULL << BOARD_INDEX(row, i));
    if ((1ULL << BOARD_INDEX(row, i)) & blockers)
      break;
  }

  // North direction
  for (i = row + 1; i <= 7; i++) {
    attacks |= (1ULL << BOARD_INDEX(i, col));
    if ((1ULL << BOARD_INDEX(i, col)) & blockers)
      break;
  }

  // South direction
  for (i = row - 1; i >= 0; i--) {
    attacks |= (1ULL << BOARD_INDEX(i, col));
    if ((1ULL << BOARD_INDEX(i, col)) & blockers)
      break;
  }

  return attacks;
}

bitboard maskBishopAttack(int bitIndex) {
  bitboard attacks = 0;
  int col = bitIndex % COLS;
  int row = bitIndex / ROWS;
  int i, j;

  // Northeast direction
  for (i = col + 1, j = row + 1; i <= 6 && j <= 6; i++, j++) {
    attacks |= (1ULL << BOARD_INDEX(j, i));
  }

  // Northwest direction
  for (i = col - 1, j = row + 1; i >= 1 && j <= 6; i--, j++) {
    attacks |= (1ULL << BOARD_INDEX(j, i));
  }

  // Southeast direction
  for (i = col + 1, j = row - 1; i <= 6 && j >= 1; i++, j--) {
    attacks |= (1ULL << BOARD_INDEX(j, i));
  }

  // Southwest direction
  for (i = col - 1, j = row - 1; i >= 1 && j >= 1; i--, j--) {
    attacks |= (1ULL << BOARD_INDEX(j, i));
  }

  return attacks;
}

bitboard maskRookAttack(int bitIndex) {
  bitboard attacks = 0;
  int col = bitIndex % COLS;
  int row = bitIndex / ROWS;
  int i;

  // East direction
  for (i = col + 1; i <= 6; i++) {
    attacks |= (1ULL << BOARD_INDEX(row, i));
  }

  // West direction
  for (i = col - 1; i >= 1; i--) {
    attacks |= (1ULL << BOARD_INDEX(row, i));
  }

  // North direction
  for (i = row + 1; i <= 6; i++) {
    attacks |= (1ULL << BOARD_INDEX(i, col));
  }

  // South direction
  for (i = row - 1; i >= 1; i--) {
    attacks |= (1ULL << BOARD_INDEX(i, col));
  }

  return attacks;
}

void fillPawnAttackTable(
    bitboard pawnAttackTable[NUMBEROFCOLORS][NUMBEROFSQUARES]) {
  for (int i = 0; i < NUMBEROFCOLORS; i++) {
    for (int j = 0; j < NUMBEROFSQUARES; j++) {
      pawnAttackTable[i][j] = computePawnAttack(j, i);
    }
  }
}

void fillKnightAttackTable(bitboard knightAttackTable[NUMBEROFSQUARES]) {
  for (int j = 0; j < NUMBEROFSQUARES; j++) {
    knightAttackTable[j] = computeKnightAttack(j);
  }
}
void fillKingAttackTable(bitboard kingAttackTable[NUMBEROFSQUARES]) {
  for (int j = 0; j < NUMBEROFSQUARES; j++) {
    kingAttackTable[j] = computeKingAttack(j);
  }
}

void fillRookAttackTable() {
  for (int i = 0; i < NUMBEROFSQUARES; i++) {
    rookMask[i] = maskRookAttack(i);
    int numberOfBitsInMask = countBits(rookMask[i]);
    int numberOfPossibleConfigsMask = (1 << numberOfBitsInMask);
    for (int j = 0; j < numberOfPossibleConfigsMask; j++) {
      bitboard currentConfig = setOccupancy(j, numberOfBitsInMask, rookMask[i]);
      int magicIndex = (currentConfig * rookMagicNumbers[i]) >>
                       (NUMBEROFSQUARES - occupancyRookMap[i]);
      rookAttacks[i][magicIndex] = computeRookAttack(i, currentConfig);
    }
  }
}

void fillbishopAttackTable() {
  for (int i = 0; i < NUMBEROFSQUARES; i++) {
    bishopMask[i] = maskBishopAttack(i);
    int numberOfBitsInMask = countBits(bishopMask[i]);
    int numberOfPossibleConfigsMask = (1 << numberOfBitsInMask);
    for (int j = 0; j < numberOfPossibleConfigsMask; j++) {
      bitboard currentConfig =
          setOccupancy(j, numberOfBitsInMask, bishopMask[i]);
      int magicIndex = (currentConfig * bishopMagicNumbers[i]) >>
                       (64 - occupancyBishopMap[i]);
      bishopAttacks[i][magicIndex] = computeBishopAttack(i, currentConfig);
    }
  }
}

bitboard getRookAttack(int bitIndex, bitboard board) {
  board &= rookMask[bitIndex];
  board *= rookMagicNumbers[bitIndex];
  board >>= NUMBEROFSQUARES - occupancyRookMap[bitIndex];
  return rookAttacks[bitIndex][board];
}

bitboard getBishopAttack(int bitIndex, bitboard board) {
  board &= bishopMask[bitIndex];
  board *= bishopMagicNumbers[bitIndex];
  board >>= NUMBEROFSQUARES - occupancyBishopMap[bitIndex];
  return bishopAttacks[bitIndex][board];
}

bitboard computeSideBitBoard(int side, chessBoard *board) {
  bitboard result = 0ULL;
  for (int i = 0; i < NUMBEROFDIFFERENTPIECES; i++)
    result |= board->pieces[side][i];
  return result;
}

piece findPieceByBitIndex(int bitIndex, chessBoard *board) {
  // TODO: Union with something to represent not found
  struct piece newPiece;
  int i, j, found;
  found = 0;
  // Find the index of piece to move
  for (i = 0; i < NUMBEROFCOLORS; i++) {
    for (j = 0; j < NUMBEROFDIFFERENTPIECES; j++) {
      bitboard mask = 1ULL << bitIndex;
      if (board->pieces[i][j] & mask) {
        newPiece.type = j;
        newPiece.side = i;
        newPiece.bitIndex = bitIndex;
        found = 1;
        break;
      }
      if (found)
        break;
    }
  }
  return newPiece;
}

bitboard computeLegalMoves(int bitIndex, chessBoard *board) {
  piece piece = findPieceByBitIndex(bitIndex, board);
  bitboard legalMoves, alyBitBoard, generalBitBoard;
  if (DEBBUG) {
    printf("Compute legal moves for side : %d, piece : %d\n", piece.side,
           piece.type);
  }
  // Add castling, mate, passang pawn,
  alyBitBoard = computeSideBitBoard(piece.side, board);
  switch (piece.type) {
  case PAWN:
    legalMoves = computePawnAttack(bitIndex, piece.side) & ~alyBitBoard;
    break;
  case KING:
    legalMoves = computePawnAttack(bitIndex, piece.side) & ~alyBitBoard;
    break;
  case KNIGHT:
    legalMoves = computePawnAttack(bitIndex, piece.side) & ~alyBitBoard;
    break;
  case ROOK:
    generalBitBoard = computeSideBitBoard(!piece.side, board) | alyBitBoard;
    legalMoves = computeRookAttack(bitIndex, generalBitBoard) & ~alyBitBoard;
    break;
  case BISHOP:
    generalBitBoard = computeSideBitBoard(!piece.side, board) | alyBitBoard;
    legalMoves = computeBishopAttack(bitIndex, generalBitBoard) & ~alyBitBoard;
    break;
  }
  return legalMoves;
}

//-------------------------------------------MAGIC NUMBER
// GENERATION-----------
// source: https://www.chessprogramming.org/Magic_Bitboards
bitboard setOccupancy(int possibleConfigs, int onesInMask,
                      bitboard attackMask) {
  // TODO : test what happends when bitPossibleConfigs is -1
  bitboard occupancy = 0;
  for (int i = 0; i < onesInMask; i++) {
    int bitPossibleConfigs = getLSBIndex(attackMask);
    placeBitValue(bitPossibleConfigs, 0, &attackMask);
    if (possibleConfigs & (1 << i))
      occupancy |= (1ULL << bitPossibleConfigs);
  }
  return occupancy;
}

uint64_t findMagicNumber(int bitIndex, int relevantBits, int pieceType) {
  int i, f, j;
  const int COMBINATIONS_OCCUPANCIES = 4096;
  const int NUMBER_OF_TRIES = 100000000;
  bitboard occupancies[COMBINATIONS_OCCUPANCIES];
  bitboard attacks[COMBINATIONS_OCCUPANCIES];
  bitboard usedAttacks[COMBINATIONS_OCCUPANCIES];
  bitboard attackMask =
      pieceType ? maskBishopAttack(bitIndex) : maskRookAttack(bitIndex);
  int numberOfPossibleBoards = 1 << relevantBits;
  for (i = 0; i < numberOfPossibleBoards; i++) {
    occupancies[i] = setOccupancy(i, relevantBits, attackMask);
    attacks[i] = pieceType ? computeBishopAttack(bitIndex, occupancies[i])
                           : computeRookAttack(bitIndex, occupancies[i]);
  }
  for (j = 0; j < NUMBER_OF_TRIES; j++) {
    uint64_t mn = getMagicNumberCandidate();
    if (countBits((attackMask * mn) & 0xFF00000000000000) < 6)
      continue;
    memset(usedAttacks, 0ULL, sizeof(usedAttacks));
    for (i = 0, f = 0; !f && i < numberOfPossibleBoards; i++) {
      int magicIndex = (int)((occupancies[i] * mn) >> (64 - relevantBits));
      if (usedAttacks[magicIndex] == 0ULL)
        usedAttacks[magicIndex] = attacks[i];
      else if (usedAttacks[magicIndex] != attacks[i])
        f = 1;
    }
    if (!f)
      return mn;
  }
  printf("failed \n");
  return 0ULL;
}

void initMagiNumbers() {
  for (int i = 0; i < 64; i++) {
    printf("0x%lxULL,\n", findMagicNumber(i, occupancyRookMap[i], 0));
  }
  printf("\n\n");
  for (int i = 0; i < 64; i++) {
    printf("0x%lxULL,\n", findMagicNumber(i, occupancyBishopMap[i], 1));
  }
}
//---------------------------------------------------------------------------------------------------------
