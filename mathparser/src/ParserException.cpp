#include "../includes/ParserException.h"

ParserException::ParserException(error_code code)
	: code(code)
{

}

const char *ParserException::what() const
{
	switch (code)
	{
		case error_code::bracket_expected:	return "Bracket expected.";
		case error_code::unexpected_token:	return "Unexpected token.";
		case error_code::digit_expected:	return "Digit expected.";
		case error_code::operand_expected:	return "Operand expected.";
		case error_code::function_expected:	return "Function expected.";
		case error_code::constant_expected:	return "Valid constant expected.";
		default:							return "An unknown Parser error occurred.";
	}
}

ParserException::error_code ParserException::getErrorcode() const
{
	return code;
}