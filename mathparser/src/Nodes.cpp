#include "../includes/Nodes.h"

NodeNumber::NodeNumber(number value) 
	: value(value) {}

number NodeNumber::eval() const
{
	return value;
}

NodeTerm::NodeTerm(NodePtr left, NodePtr right)
	: right(std::move(right)), left(std::move(left))
{
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
	std::map<std::string, number> identifiers =
	{
		{"pi", 3.14159265},
		{"e", 2.71828183}
	};

	try
	{
		return identifiers.at(identifier);
	}
	catch (const std::out_of_range&)
	{
		throw ParserException(error_code::constant_expected);
	}
}

const std::string& NodeIdent::getName() const noexcept
{
	return identifier;
}

NodeFunc::NodeFunc(NodeIdentPtr ident) 
{
	identifier = std::move(ident);
}

void NodeFunc::addArgument(NodePtr node)
{
	arguments.emplace_back(std::move(node));
}

number NodeFunc::eval() const
{
	std::map<std::string, std::function<number()>> functions =
	{
		{"sin",	[this]() { return sin(arguments.at(0)->eval()); }},
		{"cos",	[this]() { return cos(arguments.at(0)->eval()); }},
		{"tan",	[this]() { return tan(arguments.at(0)->eval()); }},
		{"sqrt", [this]() { return sqrt(arguments.at(0)->eval()); }},
		{"pow",	[this]() { return pow(arguments.at(0)->eval(), arguments.at(1)->eval()); }},
		{"log",	[this]() { return log(arguments.at(0)->eval()); }},
		{"ceil", [this]() { return ceil(arguments.at(0)->eval()); }},
		{"floor", [this]() { return floor(arguments.at(0)->eval()); }},
		{"digsum", [this]() { return digitsum(arguments.at(0)->eval()); }},
	};

	auto name = identifier->getName();

	try {
		auto func = functions.at(name);
		return func();
	}
	catch (const std::out_of_range&)
	{
		throw ParserException(error_code::function_expected);
	}
}