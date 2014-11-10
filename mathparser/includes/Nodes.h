#pragma once

#include <cmath>
#include <string>
#include <vector>

#include "math.h"
#include "ParserException.h"

typedef ParserException::error_code error_code;
using namespace math;

class Node
{
public:
	Node() = default;
	Node& operator=(const Node&) = delete;
	Node(const Node&) = delete;

	virtual ~Node() = default;
	virtual number eval() const = 0;
};

class NodeNumber : public Node
{
public:
	NodeNumber(number value);
	number eval() const override;

private:
	number value;
};

class NodeIdent : public Node
{
public:
	NodeIdent(const std::string&);
	number eval() const override;
	std::string getName() const;

private:
	std::string identifier;
};

class NodeFunc : public Node
{
public:
	NodeFunc(NodeIdent*);
	~NodeFunc() override;

	void addArgument(Node*);
	number eval() const override;

private:
	NodeIdent *identifier;
	std::vector<Node*> arguments;
};

class NodeTerm : public Node
{
public:
	NodeTerm(Node *left, Node *right);
	~NodeTerm() override;
	virtual number eval() const = 0;

protected:
	Node *right;
	Node *left;
};

class NodeAdd : public NodeTerm
{
public:
	NodeAdd(Node *left, Node *right);
	number eval() const override;
};

class NodeSub : public NodeTerm
{
public:
	NodeSub(Node *left, Node *right);
	number eval() const override;
};

class NodeMul : public NodeTerm
{
public:
	NodeMul(Node *left, Node *right);
	number eval() const override;
};

class NodeDiv : public NodeTerm
{
public:
	NodeDiv(Node *left, Node *right);
	number eval() const override;
};