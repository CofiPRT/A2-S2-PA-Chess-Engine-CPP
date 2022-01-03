#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <utility>

#include "pieces.h"
#include "utils.h"

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8

#define PAWN(a,b) ((new Pawn()))->withPos(utils::toSquare(a))->withWhite(b)->withBoard(this)->add()
#define KNIGHT(a,b) ((new Knight()))->withPos(utils::toSquare(a))->withWhite(b)->withBoard(this)->add()
#define BISHOP(a,b) ((new Bishop()))->withPos(utils::toSquare(a))->withWhite(b)->withBoard(this)->add()
#define ROOK(a,b) ((new Rook()))->withPos(utils::toSquare(a))->withWhite(b)->withBoard(this)->add()
#define QUEEN(a,b) ((new Queen()))->withPos(utils::toSquare(a))->withWhite(b)->withBoard(this)->add()
#define KING(a,b) ((new King()))->withPos(utils::toSquare(a))->withWhite(b)->withBoard(this)->add()

struct Piece;
struct King;

struct BoardInstance {
	Piece *board[BOARD_HEIGHT][BOARD_WIDTH];
	bool whiteToMove;

	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;

	Piece *whiteKing;
	Piece *blackKing;

	std::vector<Move> everyMove;

	BoardInstance();
	~BoardInstance();

	std::vector<Piece*> *getPieces(bool isWhite);
	King *getKing(bool isWhite);

	Piece *pieceAt(Square pos);
	void update(Move move);
	void resetBoard();
	void capturePiece(Piece *piece);
	void defaultBoard();
	void addPiece(Piece *piece);
	void printBoard();
};

#endif