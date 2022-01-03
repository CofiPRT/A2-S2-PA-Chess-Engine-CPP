#ifndef _FUNC_H_
#define _FUNC_H_

#include <string>

#define FUNC_INIT 0
#define FUNC_NEW 1
#define FUNC_FORCE 2
#define FUNC_GO 3
#define FUNC_WHITE 4
#define FUNC_BLACK 5
#define FUNC_MOVE 6
#define FUNC_RESIGN 7
#define FUNC_QUIT 8

namespace functions {
	int init_game(std::string);
	int new_game(std::string);
	int force_spectate(std::string);
	int force_play(std::string);
	int play_as_white(std::string);
	int play_as_black(std::string);
	int make_move(std::string);
	int resign_game(std::string);
	int quit_game(std::string);
}

#endif