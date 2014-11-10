#include "../includes/Parser.h"

Parser::Parser(const std::string& input) 
	: token(token_type::nil, ""), scanner(input)
{
	nextToken();
}

void Parser::nextToken()
{
	token = scanner.nextToken();
}

Node *Parser::parse()
{
	auto result = start();

	if (token.type() == token_type::end)
		return result;
	else
		throw ParserException(error_code::unexpected_token);
}

Node *Parser::start()
{
	auto result = multiplication();

	while (token.type() == token_type::minus || token.type() == token_type::plus)
	{
		switch (token.type())
		{
			case token_type::minus: nextToken(); result = new NodeSub(result, multiplication()); break;
			case token_type::plus:	nextToken(); result = new NodeAdd(result, multiplication());
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

Node *Parser::number()
{
	std::string buf = "";

	while (token.type() == token_type::digit || (token.type() == token_type::dot && !buf.empty() && std::string { buf.back() } != token.value()))
	{
		buf += token.value();
		nextToken();
	}

	auto number = std::strtold(buf.c_str(), nullptr);

	if (number == 0.0 && buf.find("0") == std::string::npos)
	{
		throw ParserException(error_code::operand_expected);
	}

	return new NodeNumber(number);
}

Node *Parser::multiplication()
{
	auto result = bracket();

	while (token.type() == token_type::multiplication || token.type() == token_type::division)
	{
		switch (token.type())
		{
			case token_type::division:		 nextToken(); result = new NodeDiv(result, bracket()); break;
			case token_type::multiplication: nextToken(); result = new NodeMul(result, bracket());	
		}
	}

	return result;
}

Node *Parser::bracket()
{
	// positive sign
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

		auto node = new NodeMul(new NodeNumber(sign), start());

		if (token.type() == token_type::right_parenthesis)
		{
			nextToken();
			return node;
		}
		else
		{
			throw ParserException(error_code::bracket_expected);
		}
	}
	else if (token.type() == token_type::letter)
	{
		auto ident = identifier();

		if (token.type() == token_type::left_parenthesis)
		{
			return function(ident);
		}
		else
		{
			return ident;
		}
	}
	
	return new NodeMul(new NodeNumber(sign), number());
}

NodeIdent *Parser::identifier()
{
	return new NodeIdent(text());
}

NodeFunc *Parser::function(NodeIdent *ident)
{
	auto func = new NodeFunc(ident);

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