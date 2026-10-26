#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

RPN::~RPN() {}

void RPN::applyOperator(char op)
{
	long	rhs;
	long	lhs;

	if (_stack.size() < 2)
		throw std::runtime_error("Error");
	rhs = _stack.top();
	_stack.pop();
	lhs = _stack.top();
	_stack.pop();
	if (op == '+')
		_stack.push(lhs + rhs);
	else if (op == '-')
		_stack.push(lhs - rhs);
	else if (op == '*')
		_stack.push(lhs * rhs);
	else
	{
		if (rhs == 0)
			throw std::runtime_error("Error");
		_stack.push(lhs / rhs);
	}
}

// Every token must be a single digit (0-9) or one of + - * /
long RPN::evaluate(const std::string &expression)
{
	std::istringstream	iss(expression);
	std::string			token;
	long				result;

	while (!_stack.empty())
		_stack.pop();
	while (iss >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Error");
		if (std::isdigit(static_cast<unsigned char>(token[0])))
			_stack.push(token[0] - '0');
		else if (std::string("+-*/").find(token[0]) != std::string::npos)
			applyOperator(token[0]);
		else
			throw std::runtime_error("Error");
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error");
	result = _stack.top();
	_stack.pop();
	return (result);
}
