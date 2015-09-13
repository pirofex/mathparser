#pragma once

#include <algorithm>
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

	std::string input;
	std::size_t pos = 0;
	char last_read = '\0';
	std::string skip_chars = "\n\r\t ";
};