#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN &t) : _values(t._values)
{}

RPN &RPN::operator=(const RPN &t)
{
	if (&t != this)
		_values = t._values;
	return (*this);
}

RPN::~RPN() {}

bool	checkVal(const std::string &str)
{
	if (str.size() != 1)
		return (false);
	if (std::isdigit(str[0]))
		return (true);
	if (str[0] == '/' || str[0] == '*' || str[0] == '+' || str[0] == '-')
		return (true);
	return (false);
}

int		doOperation(int a, int b, char operation)
{
	if (operation == '*')
		return (a * b);
	else if (operation == '/')
	{
		if (a == 0)
			throw std::runtime_error("Division by zero!");
		return (b / a);
	}
	else if (operation == '+')
		return (a + b);
	else
		return (b - a);
}

void	RPN::calculate(const std::string &str)
{
	std::string					word;

	std::stringstream s(str);
	while (std::getline(s, word, ' '))
	{
		if (!checkVal(word))
			throw std::runtime_error("Value Whaat?");
		if (std::isdigit((word)[0]))
			_values.push(std::atoi((word).c_str()));
		else
		{
			if (_values.size() < 2)
				throw std::runtime_error("size Whaat?");
			int	a = _values.top();
			_values.pop();
			int b = _values.top();
			_values.pop();
			_values.push(doOperation(a, b, (word)[0]));
		}
	}
	if (_values.size() != 1)
		throw std::runtime_error("end size Whaat?");
	std::cout << _values.top() << std::endl;
	_values.pop();
}
