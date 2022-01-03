#include <iostream>
#include <csignal>
#include <string>

#include "engine.h"
#include "utils.h"

int main() {
	engine::init_engine();

	std::string input;

	while (true) {
		std::getline(std::cin, input);

		if (input.empty()) {
			// keep waiting for input
			continue;
		}

		utils::trim_newline(input);

		if (engine::choose_function(input) == FUNC_QUIT) {
			// quit command received, terminate the engine
			break;
		}
	}

	engine::term_engine();

	return 0;
}