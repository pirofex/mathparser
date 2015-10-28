#include "../includes/Parser.h"

Parser::Parser(const std::string& input) 
	: scanner(input)
{
	nextToken();
}

void Parser::nextToken()
{
	token = scanner.nextToken();
}

NodePtr Parser::parse()
{
	/**
	 *  start = (multiplication) { ("+" | "-") (multiplication) };
	 *	multiplication = (bracket) { ("*" | "/") (bracket) };
	 *	bracket = ["+" | "-"]((function) | (text) | (number) | "(" (start) ")");
	 *	function = (text) '('[(start) { ',' (start) }] ')';
	 *	text = (('a' - 'Z')) { ('a' - 'Z') };
	 *	number = (digit)['.']{ (digit) };
	 *	digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
	*/

	auto result = start();

	if (token.type() == token_type::end)
	{
		return result;
	}

	throw ParserException(error_code::unexpected_token);
}

NodePtr Parser::start()
{
	auto result = multiplication();

	while (token.type() == token_type::minus || token.type() == token_type::plus)
	{
		switch (token.type())
		{
			case token_type::minus: nextToken(); result = std::make_unique<NodeSub>(std::move(result), multiplication()); break;
			case token_type::plus:	nextToken(); result = std::make_unique<NodeAdd>(std::move(result), multiplication());
		}
	}

	return result;
}

std::string Parser::text()
{
	std::string buf;

	while (token.type() == token_type::letter)
	{
		buf += token.value();
		nextToken();
	}

	return buf;
}

NodePtr Parser::number()
{
	std::string buf;

	while (token.type() == token_type::digit || token.type() == token_type::dot)
	{
		buf += token.value();
		nextToken();
	}

	std::istringstream str(buf);
	long double number;

	str >> number;

	if (!str || str.rdbuf()->in_avail())
		throw ParserException(error_code::operand_expected);

	return std::make_unique<NodeNumber>(number);
}

NodePtr Parser::multiplication()
{
	auto result = bracket();

	while (token.type() == token_type::multiplication || token.type() == token_type::division)
	{
		switch (token.type())
		{
			case token_type::division:		 nextToken(); result = std::make_unique<NodeDiv>(std::move(result), bracket()); break;
			case token_type::multiplication: nextToken(); result = std::make_unique<NodeMul>(std::move(result), bracket());
		}
	}

	return result;
}

NodePtr Parser::bracket()
{
	math::number sign = 1;

	if (token.type() == token_type::plus)
	{
		nextToken();
	}
	else if (token.type() == token_type::minus)
	{
		sign = -1;
		nextToken();
	}

	if (token.type() == token_type::left_parenthesis)
	{
		nextToken();

		auto node = std::make_unique<NodeMul>(std::make_unique<NodeNumber>(sign), start());

		if (token.type() == token_type::right_parenthesis)
		{
			nextToken();
			return std::move(node);
		}

		throw ParserException(error_code::bracket_expected);
	}
	else if (token.type() == token_type::letter)
	{
		auto ident = identifier();

		if (token.type() == token_type::left_parenthesis)
		{
			return function(std::move(ident));
		}

		return std::move(ident);
	}
	
	return std::make_unique<NodeMul>(std::make_unique<NodeNumber>(sign), number());
}

NodeIdentPtr Parser::identifier()
{
	return std::make_unique<NodeIdent>(text());
}

NodeFuncPtr Parser::function(NodeIdentPtr ident)
{
	auto func = std::make_unique<NodeFunc>(std::move(ident));

	if (token.type() != token_type::right_parenthesis)
	{
		nextToken();
		func->addArgument(start());

		while (token.type() == token_type::comma)
		{
			nextToken();
			func->addArgument(start());
		}

		if (token.type() != token_type::right_parenthesis)
		{
			throw ParserException(error_code::bracket_expected);
		}

		nextToken();
	}

	return func;
}