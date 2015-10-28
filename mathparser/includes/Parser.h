#pragma once

#include "Nodes.h"
#include "Scanner.h"
#include "ParserException.h"

#include <iostream>
#include <sstream>

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

