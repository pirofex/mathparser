#pragma once

#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include "math.h"
#include "ParserException.h"

class Node;
class NodeIdent;
class NodeFunc;

typedef ParserException::error_code error_code;
typedef std::unique_ptr<Node, std::default_delete<Node>> NodePtr;
typedef std::unique_ptr<NodeIdent, std::default_delete<NodeIdent>> NodeIdentPtr;
typedef std::unique_ptr<NodeFunc, std::default_delete<NodeFunc>> NodeFuncPtr;

using math::number;
using math::digitsum;

class Node
{
public:
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
	NodeFunc(NodeIdentPtr);

	void addArgument(NodePtr);
	number eval() const override;

private:
	NodeIdentPtr identifier;
	std::vector<NodePtr> arguments;
};

class NodeTerm : public Node
{
public:
	NodeTerm(NodePtr, NodePtr);
	virtual number eval() const = 0;

protected:
	NodePtr right;
	NodePtr left;
};

class NodeAdd : public NodeTerm
{
public:
	NodeAdd(NodePtr, NodePtr);
	number eval() const override;
};

class NodeSub : public NodeTerm
{
public:
	NodeSub(NodePtr, NodePtr);
	number eval() const override;
};

class NodeMul : public NodeTerm
{
public:
	NodeMul(NodePtr, NodePtr);
	number eval() const override;
};

class NodeDiv : public NodeTerm
{
public:
	NodeDiv(NodePtr, NodePtr);
	number eval() const override;
};