#pragma once

#include "Nodes.h"
#include "Token.h"
#include "Scanner.h"
#include "ParserException.h"

typedef ParserException::error_code error_code;

class Parser
{
public:
	Parser(const std::string& input);
	Node *parse();

private:
	void nextToken();
	std::string text();
	Node *start();
	Node *number();
	Node *multiplication();
	Node *bracket();
	NodeIdent *identifier();
	NodeFunc *function(NodeIdent *);

private:
	Token token;
	Scanner scanner;
};

