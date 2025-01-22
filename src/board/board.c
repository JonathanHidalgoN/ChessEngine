#include "../../include/board/board.h"

void removePiece(board *board, int square, int side, int piece) {
  placeBitValue(square, 0, &board->bitBoardsList.pieces[side][piece]);
  board->pieceList.pieces[square] = PIECE_EMPTY;
  board->gameState.zobristKey ^=
      board->zobristRandoms.pieceRandoms[square][side][piece];
}

void putPiece(board *board, int square, int side, int piece) {
  placeBitValue(square, 1, &board->bitBoardsList.pieces[side][piece]);
  board->pieceList.pieces[square] = piece;
  board->gameState.zobristKey ^=
      board->zobristRandoms.pieceRandoms[square][side][piece];
}

void movePiece(board *board, int from, int to, int side, int piece) {
  removePiece(board, from, side, piece);
  putPiece(board, to, side, piece);
}

void changePassant(board *board, int passantCode) {
  board->gameState.zobristKey ^=
      board->zobristRandoms.passantRandoms[board->gameState.enPassantCode];
  board->gameState.enPassantCode = passantCode;
  board->gameState.zobristKey ^=
      board->zobristRandoms.passantRandoms[board->gameState.enPassantCode];
}

void changePlayingSide(board *board) {
  board->gameState.zobristKey ^=
      board->zobristRandoms.sidesRandoms[board->gameState.playingSide];
  board->gameState.playingSide ^= 1;
  board->gameState.zobristKey ^=
      board->zobristRandoms.sidesRandoms[board->gameState.playingSide];
}

void changeCastling(board *board, int castlingCode) {
  board->gameState.zobristKey ^=
      board->zobristRandoms.castlingRandoms[board->gameState.castlingCode];
  board->gameState.castlingCode = castlingCode;
  board->gameState.zobristKey ^=
      board->zobristRandoms.castlingRandoms[board->gameState.castlingCode];
}

void initBoard(board *board) {
  fillZobristRandoms(&board->zobristRandoms);
  cleanBoard(board);
}

void cleanBoard(board *board) {
  cleanBitBoardList(&board->bitBoardsList);
  cleanPieceList(&board->pieceList);
  cleanHistory(&board->history);
  cleanGameState(board);
}

void cleanGameState(board *board) {
  board->gameState.playingSide = COLOR_WHITE;
  board->gameState.castlingCode = NO_CASTLING;
  board->gameState.halfMoveCounter = 0;
  board->gameState.fullMoveCounter = 0;
  board->gameState.enPassantCode = NO_PASSANT;
  board->gameState.phaseValue = 0;
  board->gameState.zobristKey = computeZobristFromState(
      &board->zobristRandoms, &board->bitBoardsList,
      board->gameState.playingSide, board->gameState.castlingCode,
      board->gameState.enPassantCode);
}
