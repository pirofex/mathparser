#include "../includes/Token.h"

Token::Token(::token_type t)
	: token_type(t) {}

Token::Token(::token_type t, const std::string& value)
	: token_type(t), val(value) {}

token_type Token::type() const noexcept
{
	return token_type;
}

const std::string& Token::value() const noexcept
{
	return val;
}
