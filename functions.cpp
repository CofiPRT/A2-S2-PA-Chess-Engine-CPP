#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

#include "functions.h"
#include "engine.h"

// return MACROS are defined in 'functions.h'

int functions::init_game(std::string) {
	// TODO
	engine::currInstance = NULL;
	srand(time(NULL));
	return FUNC_INIT;
}

int functions::new_game(std::string) {
	// TODO
	if (engine::currInstance == NULL) {
		engine::currInstance = new BoardInstance();
	} else {
		engine::currInstance->resetBoard();
	}

	engine::isWhite = false;
	engine::isForced = false;

	return FUNC_NEW;
}

int functions::force_spectate(std::string) {
	// TODO
	engine::isForced = true;
	return FUNC_FORCE;
}

int functions::force_play(std::string) {
	// TODO
	engine::isForced = false;
	engine::isWhite = engine::currInstance->whiteToMove;
	return FUNC_GO;
}

int functions::play_as_white(std::string input) {
	// TODO
	if ((engine::isWhite = true) == engine::currInstance->whiteToMove) {
		make_move(input);
	}

	return FUNC_WHITE;
}

int functions::play_as_black(std::string input) {
	// TODO
	if ((engine::isWhite = false) == engine::currInstance->whiteToMove) {
		make_move(input);
	}

	return FUNC_BLACK;
}

int functions::make_move(std::string input) {
	// don't move
	if (engine::isForced) return FUNC_MOVE;

	King *myKing = engine::currInstance->getKing(engine::isWhite);

	if (myKing->inCheck) {
		resign_game(input);
		return FUNC_MOVE;
	}

	std::vector<Piece*> *myPieces = engine::currInstance->getPieces(engine::isWhite);

	engine::currInstance->everyMove.clear();

	for (auto piece : *myPieces) {
		// if (piece->getType() != 2) continue;

		piece->poses.clear();

		piece->calcPoses();
		
		for (auto move : piece->poses) {
			engine::currInstance->everyMove.push_back(move);
		}
	}

	if (engine::currInstance->everyMove.empty()) {
		resign_game(input);
		return FUNC_MOVE;
	}

	Move chosenMove = engine::currInstance->everyMove[rand() %
					engine::currInstance->everyMove.size()];
	engine::currInstance->update(chosenMove);

	std::cout << "move " << utils::toString(chosenMove) << std::endl;
	return FUNC_MOVE;
}

int functions::resign_game(std::string) {
	// TODO
	std::cout << "resign" << std::endl;
	return FUNC_RESIGN;
}

int functions::quit_game(std::string) {
	// TODO
	return FUNC_QUIT;
}