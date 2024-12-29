#include "../../include/moveGeneration/attacks.h"
#include "../test.h"

// NOTE : Refactor to one general test function to attack generation, CLAUDE has
// help me a lot to change the calls from the individual test functions to
// this one
//----------------------------------------------------------------------------------------
int testPieceAttack(piece *piece, bitboard expectedResult, char testNumber,
                    bitboard blockers) {
  bitboard result;
  char *functionName;
  switch (piece->type) {
  case PAWN:
    result = computePawnAttack(piece->bitIndex, piece->side);
    functionName = "computePawnAttack";
    break;
  case KING:
    result = computeKingAttack(piece->bitIndex);
    functionName = "computeKingAttack";
    break;
  case KNIGHT:
    result = computeKnightAttack(piece->bitIndex);
    functionName = "computeKnightAttack";
    break;
  case ROOK:
    result = computeRookAttack(piece->bitIndex, blockers);
    functionName = "computeRookAttack";
    break;
  case BISHOP:
    result = computeBishopAttack(piece->bitIndex, blockers);
    functionName = "computeBishopAttack";
    break;
  default:
    break;
  }
  return compareBitBoard(expectedResult, result, testNumber, functionName);
}

int testBishopAttacks() {
  // Create a bishop piece struct - color doesn't matter for bishops
  piece bishopPiece = {WHITE, BISHOP, 0};
  // empty board
  bitboard blockers = 0ULL;

  // Test case 0 - bishop at position 0 with empty board
  bishopPiece.bitIndex = 0;
  int c0 = testPieceAttack(&bishopPiece, 9241421688590303744ULL, '0', blockers);

  // Test case 1 - bishop at position 7 with empty board bishopPiece.bitIndex =
  // 7;
  bishopPiece.bitIndex = 7;
  int c1 = testPieceAttack(&bishopPiece, 72624976668147712ULL, '1', blockers);

  // Test case 2 - bishop at position 56 with empty board
  bishopPiece.bitIndex = 56;
  int c2 = testPieceAttack(&bishopPiece, 567382630219904ULL, '2', blockers);

  // Test case 3 - bishop at position 63 with empty board
  bishopPiece.bitIndex = 63;
  int c3 = testPieceAttack(&bishopPiece, 18049651735527937ULL, '3', blockers);

  // Test cases with blockers
  // Test case 4 - bishop at position 0 with blocker at 9
  bishopPiece.bitIndex = 0;
  blockers = BIT(9);
  int c4 = testPieceAttack(&bishopPiece, BIT(9), '4', blockers);

  // Test case 5 - bishop at position 7 with blocker at 14
  bishopPiece.bitIndex = 7;
  blockers = BIT(14);
  int c5 = testPieceAttack(&bishopPiece, BIT(14), '5', blockers);

  // Test case 6 - bishop at position 56 with blocker at 49
  bishopPiece.bitIndex = 56;
  blockers = BIT(49);
  int c6 = testPieceAttack(&bishopPiece, BIT(49), '6', blockers);

  // Test case 7 - bishop at position 63 with blocker at 54
  bishopPiece.bitIndex = 63;
  blockers = BIT(54);
  int c7 = testPieceAttack(&bishopPiece, BIT(54), '7', blockers);

  // Test case 8 - bishop at position 20 with blocker at 27
  bishopPiece.bitIndex = 20;
  blockers = BIT(27);
  int c8 = testPieceAttack(&bishopPiece, 141013037361220ULL, '8', blockers);

  return c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8;
}

int testRookAttacks() {
  // Create a rook piece struct - color doesn't matter for rooks
  piece rookPiece = {WHITE, ROOK, 0};
  // empty board
  bitboard blockers = 0ULL;

  // Test cases with empty board
  // Test case 0 - rook at position 0
  rookPiece.bitIndex = 0;
  int c0 = testPieceAttack(&rookPiece, 72340172838076926ULL, '0', blockers);

  // Test case 1 - rook at position 7
  rookPiece.bitIndex = 7;
  int c1 = testPieceAttack(&rookPiece, 9259542123273814143ULL, '1', blockers);

  // Test case 2 - rook at position 56
  rookPiece.bitIndex = 56;
  int c2 = testPieceAttack(&rookPiece, 18302911464433844481ULL, '2', blockers);

  // Test case 3 - rook at position 63
  rookPiece.bitIndex = 63;
  int c3 = testPieceAttack(&rookPiece, 9187484529235886208ULL, '3', blockers);

  // Test case 4 - rook at position 20
  rookPiece.bitIndex = 20;
  int c4 = testPieceAttack(&rookPiece, 1157442765423841296, '4', blockers);

  // Test cases with blockers
  // Test case 5 - rook at position 0 with blockers at 1 and 8
  rookPiece.bitIndex = 0;
  blockers = BIT(1) + BIT(8);
  int c5 = testPieceAttack(&rookPiece, BIT(1) + BIT(8), '5', blockers);

  // Test case 6 - rook at position 7 with blockers at 6 and 15
  rookPiece.bitIndex = 7;
  blockers = BIT(6) + BIT(15);
  int c6 = testPieceAttack(&rookPiece, BIT(6) + BIT(15), '6', blockers);

  // Test case 7 - rook at position 56 with blockers at 57 and 48
  rookPiece.bitIndex = 56;
  blockers = BIT(57) + BIT(48);
  int c7 = testPieceAttack(&rookPiece, BIT(57) + BIT(48), '7', blockers);

  // Test case 8 - rook at position 63 with blockers at 62 and 55
  rookPiece.bitIndex = 63;
  blockers = BIT(62) + BIT(55);
  int c8 = testPieceAttack(&rookPiece, BIT(62) + BIT(55), '8', blockers);

  // Test case 9 - rook at position 20 with multiple blockers
  rookPiece.bitIndex = 20;
  blockers = BIT(19) + BIT(21) + BIT(28) + BIT(12);
  int c9 = testPieceAttack(&rookPiece, BIT(19) + BIT(21) + BIT(28) + BIT(12),
                           '9', blockers);

  // Test case 10 - rook at position 29 with multiple blockers
  rookPiece.bitIndex = 29;
  blockers = BIT(31) + BIT(45) + BIT(21);
  int c10 = testPieceAttack(&rookPiece, 35325554458624, 'a', blockers);

  return c0 && c1 && c2 && c3 && c4 && c5 && c6 && c7 && c8 && c9 && c10;
}

int testPawnAttacks() {
  // Create a pawn piece struct - we'll update the side and position for each
  // test
  piece pawnPiece = {WHITE, PAWN, 0};
  // Pawns don't use blockers, so we'll keep it as 0
  bitboard blockers = 0ULL;

  // Test case 0 - black pawn at position 9
  pawnPiece.bitIndex = 9;
  pawnPiece.side = BLACK;
  int c0 = testPieceAttack(&pawnPiece, BIT(0) + BIT(2), '0', blockers);

  // Test case 1 - black pawn at position 1 (edge case)
  pawnPiece.bitIndex = 1;
  pawnPiece.side = BLACK;
  int c1 = testPieceAttack(&pawnPiece, 0, '1', blockers);

  // Test case 2 - white pawn at position 0 (edge case)
  pawnPiece.bitIndex = 0;
  pawnPiece.side = WHITE;
  int c2 = testPieceAttack(&pawnPiece, BIT(9), '2', blockers);

  // Test case 3 - white pawn at position 7 (edge case)
  pawnPiece.bitIndex = 7;
  pawnPiece.side = WHITE;
  int c3 = testPieceAttack(&pawnPiece, BIT(14), '3', blockers);

  // Test case 4 - black pawn at position 56
  pawnPiece.bitIndex = 56;
  pawnPiece.side = BLACK;
  int c4 = testPieceAttack(&pawnPiece, BIT(49), '4', blockers);

  // Test case 5 - black pawn at position 63
  pawnPiece.bitIndex = 63;
  pawnPiece.side = BLACK;
  int c5 = testPieceAttack(&pawnPiece, BIT(54), '5', blockers);

  // Test case 6 - white pawn at position 54
  pawnPiece.bitIndex = 54;
  pawnPiece.side = WHITE;
  int c6 = testPieceAttack(&pawnPiece, BIT(63) + BIT(61), '6', blockers);

  return c1 && c0 && c3 && c2 && c4 && c5 && c6;
}

int testKnightAttacks() {
  // Create a knight piece struct - color doesn't matter for knights
  piece knightPiece = {WHITE, KNIGHT, 0};
  // Knights don't use blockers
  bitboard blockers = 0ULL;

  // Test case 0 - knight at position 0 (corner)
  knightPiece.bitIndex = 0;
  int c0 = testPieceAttack(&knightPiece, BIT(17) + BIT(10), '0', blockers);

  // Test case 1 - knight at position 7 (corner)
  knightPiece.bitIndex = 7;
  int c1 = testPieceAttack(&knightPiece, BIT(22) + BIT(13), '1', blockers);

  // Test case 2 - knight at position 56 (corner)
  knightPiece.bitIndex = 56;
  int c2 = testPieceAttack(&knightPiece, BIT(50) + BIT(41), '2', blockers);

  // Test case 3 - knight at position 63 (corner)
  knightPiece.bitIndex = 63;
  int c3 = testPieceAttack(&knightPiece, BIT(46) + BIT(53), '3', blockers);

  return c0 && c1 && c2 && c3;
}

int testKingAttacks() {
  // Create a king piece struct - color doesn't matter for king movement
  piece kingPiece = {WHITE, KING, 0};
  // Kings don't use blockers
  bitboard blockers = 0ULL;

  // Test case 0 - king at position 0 (corner)
  kingPiece.bitIndex = 0;
  int c0 = testPieceAttack(&kingPiece, BIT(1) + BIT(8) + BIT(9), '0', blockers);

  // Test case 1 - king at position 7 (corner)
  kingPiece.bitIndex = 7;
  int c1 =
      testPieceAttack(&kingPiece, BIT(6) + BIT(15) + BIT(14), '1', blockers);

  // Test case 2 - king at position 56 (corner)
  kingPiece.bitIndex = 56;
  int c2 =
      testPieceAttack(&kingPiece, BIT(57) + BIT(48) + BIT(49), '2', blockers);

  // Test case 3 - king at position 63 (corner)
  kingPiece.bitIndex = 63;
  int c3 =
      testPieceAttack(&kingPiece, BIT(62) + BIT(55) + BIT(54), '3', blockers);

  return c0 && c1 && c2 && c3;
}

void testAttacks() {
  int resultTestPawnAttack = testPawnAttacks();
  int resultTestKnightAttack = testKnightAttacks();
  int resultTestKingAttack = testKingAttacks();
  int resultTestRookAttack = testRookAttacks();
  int resultTestBishopAttack = testBishopAttacks();
  if (resultTestPawnAttack && resultTestKnightAttack && resultTestKingAttack &&
      resultTestRookAttack && resultTestBishopAttack) {
    printf("Tested attacks successfully \n");
  }
}
