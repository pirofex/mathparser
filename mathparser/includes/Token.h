#pragma once

#include <string>

enum class token_type
{
	letter,					// a - z, A - Z
	digit,					// 0 - 9
	comma,					// ,
	dot,					// .
	minus,					// -
	plus,					// +
	multiplication,			// *
	division,				// /
	left_parenthesis,		// (
	right_parenthesis,		// )
	end,					// end of input reached
	nil						// not a valid token
};

class Token
{
public:
	Token(token_type t, const std::string& value);

	token_type type() const;
	std::string value() const;

private:
	token_type token_type;
	std::string val;
};

