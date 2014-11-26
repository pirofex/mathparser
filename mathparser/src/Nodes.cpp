#include "../includes/Nodes.h"

NodeNumber::NodeNumber(number value) 
	: value(value) {}

number NodeNumber::eval() const
{
	return value;
}

NodeTerm::NodeTerm(NodePtr left, NodePtr right)
{
	this->right = std::move(right);
	this->left = std::move(left);
}

NodeAdd::NodeAdd(NodePtr left, NodePtr right) 
	: NodeTerm(std::move(left), std::move(right)) {}

number NodeAdd::eval() const
{
	return left->eval() + right->eval();
}

NodeSub::NodeSub(NodePtr left, NodePtr right) 
	: NodeTerm(std::move(left), std::move(right)) {}

number NodeSub::eval() const
{
	return left->eval() - right->eval();
}

NodeMul::NodeMul(NodePtr left, NodePtr right) 
	: NodeTerm(std::move(left), std::move(right)) {}

number NodeMul::eval() const
{
	return left->eval() * right->eval();
}

NodeDiv::NodeDiv(NodePtr left, NodePtr right) 
	: NodeTerm(std::move(left), std::move(right)) {}

number NodeDiv::eval() const
{
	return left->eval() / right->eval();
}

NodeIdent::NodeIdent(const std::string& input) 
	: identifier(input) {}

number NodeIdent::eval() const
{
	if (identifier == "pi")
	{
		return 3.14159265;
	}
	else if (identifier == "e")
	{
		return 2.71828183;
	}
	else
	{
		throw ParserException(error_code::constant_expected);
	}
}

std::string NodeIdent::getName() const
{
	return identifier;
}

NodeFunc::NodeFunc(NodeIdentPtr ident) 
{
	identifier = std::move(ident);
}

void NodeFunc::addArgument(NodePtr node)
{
	arguments.push_back(std::move(node));
}

number NodeFunc::eval() const
{
	if (identifier->getName() == "sin")
	{
		if (arguments.size() == 1)
			return sin(arguments[0]->eval());
	}
	else if (identifier->getName() == "cos")
	{
		if (arguments.size() == 1)
			return cos(arguments[0]->eval());
	}
	else if (identifier->getName() == "tan")
	{
		if (arguments.size() == 1)
			return tan(arguments[0]->eval());
	}
	else if (identifier->getName() == "sqrt")
	{
		if (arguments.size() == 1)
			return sqrt(arguments[0]->eval());
	}
	else if (identifier->getName() == "pow")
	{
		if (arguments.size() == 2)
			return pow(arguments[0]->eval(), arguments[1]->eval());
	}
	else if (identifier->getName() == "log")
	{
		if (arguments.size() == 1)
			return log(arguments[0]->eval());
	}
	else if (identifier->getName() == "ceil")
	{
		if (arguments.size() == 1)
			return ceil(arguments[0]->eval());
	}
	else if (identifier->getName() == "floor")
	{
		if (arguments.size() == 1)
			return floor(arguments[0]->eval());
	}
	else if (identifier->getName() == "digsum")
	{
		if (arguments.size() == 1)
			return digitsum(arguments[0]->eval());
	}

	throw ParserException(error_code::function_expected);
}