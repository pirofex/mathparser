#include "../includes/Scanner.h"

Scanner::Scanner(const std::string& in) 
	: input(in)
{
	nextChar();
}

Token Scanner::nextToken()
{
	skipCharacters();

	if (std::isalpha(last_read))
	{
		auto tmp = last_read;
		nextChar();
		return Token(token_type::letter, std::string { tmp });
	}

	if (std::isalnum(last_read))
	{
		auto tmp = last_read;
		nextChar();
		return Token(token_type::digit, std::string { tmp });
	}
	
	switch (last_read)
	{
		case '.': nextChar();	return Token(token_type::dot);
		case '(': nextChar();	return Token(token_type::left_parenthesis);
		case ')': nextChar();	return Token(token_type::right_parenthesis);
		case '-': nextChar();	return Token(token_type::minus);
		case '+': nextChar();	return Token(token_type::plus);
		case '*': nextChar();	return Token(token_type::multiplication);
		case '/': nextChar();	return Token(token_type::division);
		case ',': nextChar();	return Token(token_type::comma);
		case '\0':				return Token(token_type::end);
		default:				return Token(token_type::nil, std::string { last_read });
	}
}

void Scanner::nextChar()
{
	if (pos > input.length())
	{
		last_read = 0;
		return;
	}
	
	last_read = input[pos++];
}

void Scanner::setSkipChars(const std::string& chars)
{
	skip_chars = chars;
}

void Scanner::skipCharacters()
{
	std::for_each(std::begin(skip_chars), std::end(skip_chars), [this](const char& c) {
		if (last_read == c)
		{
			nextChar();
			skipCharacters();
		}
	});
}