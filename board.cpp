#include <string>
#include <stdio.h>

#include "board.h"
#include "pieces.h"
#include "utils.h"

BoardInstance::BoardInstance() {
	whiteToMove = true;	
	defaultBoard();
}

Piece *BoardInstance::pieceAt(Square pos) {
	return board[pos.first][pos.second];
}

std::vector<Piece*> *BoardInstance::getPieces(bool isWhite) {
	return isWhite ? &whitePieces : &blackPieces;
}

King *BoardInstance::getKing(bool isWhite) {
	return (King*)(isWhite ? whiteKing : blackKing);
}

void BoardInstance::update(Move move) {
	Square pos = move.first;
	Square nextPos = move.second;

	if (pieceAt(pos)->getType() == PIECE_KING) {
		printf("KING IS MOVING\n");
	}

	capturePiece(pieceAt(nextPos));

	pieceAt(pos)->doMove(move);

	board[nextPos.first][nextPos.second] = pieceAt(pos);
	board[pos.first][pos.second] = NULL;

	whiteToMove = !whiteToMove;

	pieceAt(nextPos)->poses.clear();
	// give check if necessary
	pieceAt(nextPos)->calcPoses();
	pieceAt(nextPos)->poses.clear();
}

void BoardInstance::capturePiece(Piece *piece) {
	if (piece) {
		Square pos = piece->pos;
		board[pos.first][pos.second] = NULL;

		std::vector<Piece*> *opponentPieces = (whiteToMove ? &blackPieces :
															&whitePieces);

		for (int i = 0; i < opponentPieces->size(); i++) {
			if ((*opponentPieces)[i]->pos == pos) {
				opponentPieces->erase(opponentPieces->begin() + i);
				break;
			}
		}

		if (!piece) printf("successfully deleted piece\n");
	}
}

void BoardInstance::resetBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = NULL;
		}
	}
	
	whitePieces.clear();
	blackPieces.clear();
	everyMove.clear();
	defaultBoard();
}

void BoardInstance::addPiece(Piece *piece) {
	Square pos = piece->pos;
	board[pos.first][pos.second] = piece;

	if (piece->isWhite) {
		whitePieces.push_back(piece);
	} else {
		blackPieces.push_back(piece);
	}

	if (piece->getType() == PIECE_KING) {
		if (piece->isWhite) {
			whiteKing = piece;
		} else {
			blackKing = piece;
		}
	}
}

void BoardInstance::defaultBoard() {
	// WHITE PIECES
	ROOK("a1", true);
	KNIGHT("b1", true);
	BISHOP("c1", true);
	QUEEN("d1", true);
	KING("e1", true);
	BISHOP("f1", true);
	KNIGHT("g1", true);
	ROOK("h1", true);

	// WHITE PAWNS
	PAWN("a2", true);
	PAWN("b2", true);
	PAWN("c2", true);
	PAWN("d2", true);
	PAWN("e2", true);
	PAWN("f2", true);
	PAWN("g2", true);
	PAWN("h2", true);

	// BLACK PIECES
	ROOK("a8", false);
	KNIGHT("b8", false);
	BISHOP("c8", false);
	QUEEN("d8", false);
	KING("e8", false);
	BISHOP("f8", false);
	KNIGHT("g8", false);
	ROOK("h8", false);

	// BLACK PAWNS
	PAWN("a7", false);
	PAWN("b7", false);
	PAWN("c7", false);
	PAWN("d7", false);
	PAWN("e7", false);
	PAWN("f7", false);
	PAWN("g7", false);
	PAWN("h7", false);
}

void BoardInstance::printBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == NULL) {
				printf("0 ");
			} else {
				printf("%d ", board[i][j]->getType());
			}
		}

		printf("\n");
	}
}