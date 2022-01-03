#ifndef _PIECES_H_
#define _PIECES_H_

#include <vector>
#include <utility>

#include "board.h"
#include "utils.h"

#define PIECE_PAWN 1
#define PIECE_KNIGHT 2
#define PIECE_BISHOP 3
#define PIECE_ROOK 4
#define PIECE_QUEEN 5
#define PIECE_KING 6

struct BoardInstance;

struct Piece {
	Square pos;

	bool isWhite;
	bool isPinned; // O(1) future pin tests

	char guards; // how many pieces are directly protecting it

	BoardInstance *board; // quick board access
	std::vector<Move> poses; // O(1) future access

	Piece();
	~Piece();

	virtual char getType() = 0;
	virtual std::vector<Move> calcPoses() = 0;
	virtual void doMove(Move move);
	bool testPos(Square nextPos);

	Piece *withPos(Square pos_);

	Piece *withWhite(bool isWhite_);

	Piece *withBoard(BoardInstance *board_);

	void add();
};

struct Pawn: public Piece {
	bool hasMoved;
	bool enPassant; // true if it can be captured by en passant

	Pawn();
	~Pawn();

	char getType();
	std::vector<Move> calcPoses();
	void doMove(Move move);

	void promote() {
		// TODO
	}
};

struct Knight: public Piece {
	Knight();
	~Knight();

	char getType();
	std::vector<Move> calcPoses();
	void doMove(Move move);
};

struct Bishop: public Piece {
	Bishop();
	~Bishop();

	char getType();
	std::vector<Move> calcPoses();
	void doMove(Move move);
};

struct Rook: public Piece {
	Rook();
	~Rook();

	char getType();
	std::vector<Move> calcPoses();
	void doMove(Move move);
};

struct Queen: public Piece {
	Queen();
	~Queen();

	char getType();
	std::vector<Move> calcPoses();
	void doMove(Move move);
};

struct King: public Piece {
	bool canCastle;
	bool inCheck;

	King();
	~King();

	char getType();
	std::vector<Move> calcPoses();
	void doMove(Move move);
};

#endif