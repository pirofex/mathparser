#include "../includes/Scanner.h"

Scanner::Scanner(const std::string& in) 
	: input(in), last_read(0), pos(0), skip_chars("\n\r\t ")
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
		case '.': nextChar();	return Token(token_type::dot, ".");
		case '(': nextChar();	return Token(token_type::left_parenthesis, "(");
		case ')': nextChar();	return Token(token_type::right_parenthesis, ")");
		case '-': nextChar();	return Token(token_type::minus, "-");
		case '+': nextChar();	return Token(token_type::plus, "+");
		case '*': nextChar();	return Token(token_type::multiplication, "*");
		case '/': nextChar();	return Token(token_type::division, "/");
		case ',': nextChar();	return Token(token_type::comma, ",");
		case '\0':				return Token(token_type::end, "\0");
		default:				return Token(token_type::nil, std::string { last_read });
	}
}

void Scanner::nextChar()
{
	if (pos > input.length())
	{
		last_read = 0;
	}
	else
	{
		last_read = input[pos++];
	}
}

void Scanner::setSkipChars(const std::string& chars)
{
	skip_chars = chars;
}

void Scanner::skipCharacters()
{
	for (auto const &i : skip_chars)
	{
		if (last_read == i)
		{
			nextChar();
			skipCharacters();
			return;
		}
	}
}