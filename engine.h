#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <string>
#include <map>
#include <functional>

#include "utils.h"
#include "functions.h"
#include "board.h"

namespace engine {
	extern std::map<std::string,
					std::function<int(std::string)>,
					utils::comp_str> func_map;

	extern BoardInstance *currInstance;
	extern bool isWhite;
	extern bool isForced;

	void init_engine();
	void term_engine();
	int choose_function(std::string input);
}

#endif