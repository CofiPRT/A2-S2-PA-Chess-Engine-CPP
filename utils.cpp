#include <string>

#include "utils.h"

bool utils::comp_str::operator()(std::string str1, std::string str2) {
	return str1.compare(str2) < 0;
}

// erase trailing newline if present
void utils::trim_newline(std::string str) {
	if (str.back() == '\n') {
		str.back() = '\0';
	}
}

// keep in board
bool utils::inBounds(std::pair<char, char> pos) {
	return inBounds(pos.first) && inBounds(pos.second);
}

bool utils::inBounds(char coord) {
	return coord >= 0 && coord <= 7;
}

bool utils::isFile(char file) {
	return file >= 'a' && file <= 'h';
}

bool utils::isRank(char rank) {
	return rank >= '1' && rank <= '8';
}

bool utils::isMove(std::string input) {
	if (input.length() != 4 ||
		!isFile(input[0]) ||
		!isRank(input[1]) ||
		!isFile(input[2]) ||
		!isRank(input[3])) {

		return false;
	}

	return true;
}

Move utils::toMove(std::string input) {
	Square pos = std::make_pair('8' - input[1], input[0] - 'a');
	Square nextPos = std::make_pair('8' - input[3], input[2] - 'a');

	return std::make_pair(pos, nextPos);
}

Square utils::toSquare(std::string input) {
	return std::make_pair('8' - input[1], input[0] - 'a');
}

Square utils::toSquare(char i, char j) {
	return std::make_pair(i, j);
}

std::string utils::toString(Move move) {
	std::string newString;
	newString.push_back(move.first.second + 'a');
	newString.push_back('8' - move.first.first);
	newString.push_back(move.second.second + 'a');
	newString.push_back('8' - move.second.first);

	return newString;
}

std::string utils::toString(Square square) {
	std::string newString;
	newString.push_back(square.second + 'a');
	newString.push_back('8' - square.first);

	return newString;
}