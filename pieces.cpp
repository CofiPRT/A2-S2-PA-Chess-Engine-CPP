#include <vector>
#include <utility> // pair
#include <cstdlib> // abs()
#include <algorithm> // min()
#include <iostream>

#include "pieces.h"
#include "utils.h"

Piece::Piece() {
	isPinned = 0;
	guards = 0;
}
Piece::~Piece() {

}

void Piece::doMove(Move move) {
	pos = move.second;
	guards = 0;

	poses.clear();
}

bool Piece::testPos(Square nextPos) {
	bool shouldStop = true;

	if (utils::inBounds(nextPos)) {
		Piece *target = board->pieceAt(nextPos);

		if (target == NULL) {
			// free square
			poses.push_back(std::make_pair(pos, nextPos));

			shouldStop = false;
		} else if (target->isWhite == this->isWhite) {
			// square not available, but protected
			(target->guards)++;
		} else if (target->getType() == PIECE_KING) {
			// give check
			King *king = (King *)(target->isWhite ?
									board->whiteKing :
									board->blackKing);

			king->inCheck = true;
		} else {
			// piece available for capture
			poses.push_back(std::make_pair(pos, nextPos));
			// (different 'if' branch for future tweaks)
		}
	}

	return shouldStop;
}

Piece *Piece::withPos(Square pos_) {
	pos = pos_;
	return this;
}

Piece *Piece::withWhite(bool isWhite_) {
	isWhite = isWhite_;
	return this;
}

Piece *Piece::withBoard(BoardInstance *board_) {
	board = board_;
	return this;
}

void Piece::add() {
	board->addPiece(this);
}

Pawn::Pawn():Piece() {
	hasMoved = false;
	enPassant = false;
}

std::vector<Move> Pawn::calcPoses() {
	char direction = isWhite ? -1 : 1;
	// board[0][0] is top-left
	char maxSquares = hasMoved ? 1 : 2;

	for (char i = 1; i <= maxSquares; i++) {
		// one square and two squares forward
		Square nextPos = std::make_pair(pos.first + i*direction,
										pos.second);

		if (utils::inBounds(nextPos) && board->pieceAt(nextPos) == NULL) {
			// free square
			poses.push_back(std::make_pair(pos, nextPos));
		} else {
			// can't advance further
			break;
		}
	}
	
	for (char i = -1; i <= 1; i +=2) {
		// attack squares for pawn
		Square nextPos = std::make_pair(pos.first + direction,
										pos.second + i);

		if (utils::inBounds(nextPos)) {
			Piece *target = board->pieceAt(nextPos);

			if (target == NULL) {
				// not attacking anything
				continue;
			}
			if (target->isWhite == this->isWhite) {
				// square not available, but protected
				(target->guards)++;
			} else if (target->getType() == PIECE_KING) {
				// give check
				King *king = (King *)(target->isWhite ?
										board->whiteKing :
										board->blackKing);

				king->inCheck = true;
			} else {
				// piece available for capture
				poses.push_back(std::make_pair(pos, nextPos));
			}
		}
	}

	return poses;
}

Knight::Knight():Piece() {

}

std::vector<Move> Knight::calcPoses() {
	for (char i = -2; i <= 2; i++) {
		// 4 files
		if (i == 0) continue;

		char otherCoord = 3 - abs(i);
		for (char j = -otherCoord; j <= otherCoord; j += 2*otherCoord) {
			// 2 rows for each file -> total = 8 moves (correct)
			testPos(std::make_pair(pos.first + i, pos.second + j));
		}
	}

	return poses;
}

Bishop::Bishop():Piece() {

}

std::vector<Move> Bishop::calcPoses() {
	for (char i = 1; i <= 7; i++) {
		// go bottom-right
		if (testPos(std::make_pair(pos.first + i, pos.second + i))) {
			break;
		}
	}

	for (char i = -1; i >= -7; i--) {
		// go top-left
		if (testPos(std::make_pair(pos.first + i, pos.second + i))) {
			break;
		}
	}

	for (char i = 1; i <= 7; i++) {
		// go bottom-left
		if (testPos(std::make_pair(pos.first + i, pos.second - i))) {
			break;
		}
	}

	for (char i = -1; i >= -7; i--) {
		// go top-right
		if (testPos(std::make_pair(pos.first + i, pos.second - i))) {
			break;
		}
	}

	return poses;
}

Rook::Rook():Piece() {

}

std::vector<Move> Rook::calcPoses() {
	for (int i = 1; i <= 7; i++) {
		// go right
		if (testPos(std::make_pair(pos.first, pos.second + i))) {
			break;
		}
	}

	for (int i = -1; i >= -7; i--) {
		// go left
		if (testPos(std::make_pair(pos.first, pos.second + i))) {
			break;
		}
	}

	for (int i = 1; i <= 7; i++) {
		// go down
		if (testPos(std::make_pair(pos.first + i, pos.second))) {
			break;
		}
	}

	for (int i = -1; i >= -7; i--) {
		// go up
		if (testPos(std::make_pair(pos.first + i, pos.second))) {
			break;
		}
	}

	return poses;
}

Queen::Queen():Piece() {

}

std::vector<Move> Queen::calcPoses() {
	for (int i = 1; i <= 7; i++) {
		// go right
		if (testPos(std::make_pair(pos.first, pos.second + i))) {
			break;
		}
	}

	for (int i = -1; i >= -7; i--) {
		// go left
		if (testPos(std::make_pair(pos.first, pos.second + i))) {
			break;
		}
	}

	for (int i = 1; i <= 7; i++) {
		// go down
		if (testPos(std::make_pair(pos.first + i, pos.second))) {
			break;
		}
	}

	for (int i = -1; i >= -7; i--) {
		// go up
		if (testPos(std::make_pair(pos.first + i, pos.second))) {
			break;
		}
	}

	for (char i = 1; i <= 7; i++) {
		// go bottom-right
		if (testPos(std::make_pair(pos.first + i, pos.second + i))) {
			break;
		}
	}

	for (char i = -1; i >= -7; i--) {
		// go top-left
		if (testPos(std::make_pair(pos.first + i, pos.second + i))) {
			break;
		}
	}

	for (char i = 1; i <= 7; i++) {
		// go bottom-left
		if (testPos(std::make_pair(pos.first + i, pos.second - i))) {
			break;
		}
	}

	for (char i = -1; i >= -7; i--) {
		// go top-right
		if (testPos(std::make_pair(pos.first + i, pos.second - i))) {
			break;
		}
	}

	return poses;
}

King::King():Piece() {
	canCastle = true;
	inCheck = false;
}

std::vector<Move> King::calcPoses() {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;

			testPos(std::make_pair(pos.first + i, pos.second + j));
		}
	}

	return poses;
}

void Pawn::doMove(Move move) {
	Piece::doMove(move);
	hasMoved = true;

	if (abs(move.first.first - move.second.first) == 2) {
		// has moved two squares, now susceptible to en passant
		enPassant = true;
	}
}

void Knight::doMove(Move move) {
	Piece::doMove(move);
}

void Bishop::doMove(Move move) {
	Piece::doMove(move);
}

void Rook::doMove(Move move) {
	Piece::doMove(move);

	if (isWhite) {
		((King*)(board->whiteKing))->canCastle = false;
	} else {
		((King*)(board->blackKing))->canCastle = false;
	}
}

void Queen::doMove(Move move) {
	Piece::doMove(move);
}

void King::doMove(Move move) {
	if (canCastle) {
		if (move.second.second == move.first.second - 2) {
			// queen side castle
			board->update(utils::toMove(isWhite ? "a1d1" : "a8d8"));
		} else if (move.second.second == move.first.second + 2) {
			// king side castle
			board->update(utils::toMove(isWhite ? "h1f1" : "h8f8"));
		}
	}
	Piece::doMove(move);

	canCastle = false;
}

char Pawn::getType() {
	return PIECE_PAWN;
}

char Knight::getType() {
	return PIECE_KNIGHT;
}

char Bishop::getType() {
	return PIECE_BISHOP;
}

char Rook::getType() {
	return PIECE_ROOK;
}

char Queen::getType() {
	return PIECE_QUEEN;
}

char King::getType() {
	return PIECE_KING;
}