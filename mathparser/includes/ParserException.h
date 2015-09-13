#pragma once

#include <exception>

class ParserException :
	public std::exception
{
public:
	enum class error_code
	{
		digit_expected,
		bracket_expected,
		operand_expected,
		unexpected_token,
		function_expected,
		constant_expected
	};

	ParserException(error_code);
	const char *what() const override;
	error_code getErrorcode() const noexcept;

private:
	error_code code;
};

