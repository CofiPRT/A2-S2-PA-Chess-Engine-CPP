#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <utility>

typedef std::pair<char, char> Square; // CAREFUL: matrix standard: a1 = [7][0]
typedef std::pair<Square, Square> Move; // <before, after>

namespace utils {
	struct comp_str {
		bool operator()(std::string str1, std::string str2);
	};

	void trim_newline(std::string);

	bool inBounds(std::pair<char, char> pos);
	bool inBounds(char coord);

	bool isFile(char file);
	bool isRank(char rank);
	bool isMove(std::string input);

	Move toMove(std::string input);
	Square toSquare(std::string input);
	Square toSquare(char i, char j);

	std::string toString(Move move);
	std::string toString(Square square);
}

#endif