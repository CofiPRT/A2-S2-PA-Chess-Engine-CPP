#include <iostream>
#include <csignal>
#include <string>

#include "engine.h"

// map a command to its corresponding function
std::map<std::string,
		std::function<int(std::string)>,
		utils::comp_str> engine::func_map = {
	{"xboard", functions::init_game},
	{"new", functions::new_game},
	{"force", functions::force_spectate},
	{"go", functions::force_play},
	{"white", functions::play_as_white},
	{"black", functions::play_as_black},
	{"move", functions::make_move},
	{"resign", functions::resign_game},
	{"quit", functions::quit_game}
};

BoardInstance *engine::currInstance;

bool engine::isWhite;
bool engine::isForced;

void engine::init_engine() {
	// IO buffers
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	// often sent by xboard, ignore it
	signal(SIGINT, SIG_IGN);
}

void engine::term_engine() {
	// TODO (if necessary)
}

int engine::choose_function(std::string input) {
	try {
		return func_map.at(input)(input);
	} catch (std::out_of_range ex) {
		// TODO: add && validateMove(input)
		if (utils::isMove(input)) {
			currInstance->update(utils::toMove(input));

			return functions::make_move(input);
		}
	}
	// TODO: handle out_of_range exception
}