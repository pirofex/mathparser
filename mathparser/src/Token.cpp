#include "../includes/Token.h"

Token::Token(::token_type t, const std::string& value) 
	: token_type(t), val(value) {}

token_type Token::type() const
{
	return token_type;
}

std::string Token::value() const
{
	return val;
}
