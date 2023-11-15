#ifndef RPN_HPP
# define RPN_HPP
# include <stack>
# include <list>
# include <string>
# include <sstream>
# include <iostream>
# include <stdexcept>
# include <cstdlib>

class RPN
{
	private:
		std::stack<int> _values;
	public:
		RPN();
		RPN(const RPN &t);
		~RPN();
		RPN &operator=(const RPN &t);
		void calculate(const std::string &str);
};

#endif
