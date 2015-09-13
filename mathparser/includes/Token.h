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
	Token() = default;
	Token(token_type);
	Token(token_type, const std::string& value);

	token_type type() const noexcept;
	const std::string& value() const noexcept;

private:
	token_type token_type;
	std::string val;
};

