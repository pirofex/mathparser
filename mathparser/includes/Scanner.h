#pragma once

#include <cctype>
#include <locale>
#include <string>

#include "Token.h"

class Scanner
{
public:
	Scanner(const std::string& input);
	Token nextToken();
	void setSkipChars(const std::string& chars);

private:
	void nextChar();
	void skipCharacters();

	char last_read;
	std::string input;
	std::size_t pos;
	std::string skip_chars;
};

