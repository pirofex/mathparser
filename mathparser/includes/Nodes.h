#pragma once

#include <cmath>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "math.h"
#include "ParserException.h"

class Node;
class NodeIdent;
class NodeFunc;

using NodePtr = std::unique_ptr<Node>;
using NodeIdentPtr = std::unique_ptr<NodeIdent>;
using NodeFuncPtr = std::unique_ptr<NodeFunc>;

using math::number;
using math::digitsum;

using error_code = ParserException::error_code;

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
	const std::string& getName() const noexcept;

private:
	std::string identifier;
};

class NodeFunc : public Node
{
public:
	NodeFunc(NodeIdentPtr);

	void addArgument(NodePtr);
	number eval() const override final;

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
	number eval() const override final;
};

class NodeSub : public NodeTerm
{
public:
	NodeSub(NodePtr, NodePtr);
	number eval() const override final;
};

class NodeMul : public NodeTerm
{
public:
	NodeMul(NodePtr, NodePtr);
	number eval() const override final;
};

class NodeDiv : public NodeTerm
{
public:
	NodeDiv(NodePtr, NodePtr);
	number eval() const override final;
};
