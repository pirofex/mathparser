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
	NodePtr parse();

private:
	void nextToken();
	std::string text();
	NodePtr start();
	NodePtr number();
	NodePtr multiplication();
	NodePtr bracket();
	NodeIdentPtr identifier();
	NodeFuncPtr function(NodeIdentPtr);

private:
	Token token;
	Scanner scanner;
};

