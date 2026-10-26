#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

class RPN
{
	private:
		std::stack<long>	_stack;

		void	applyOperator(char op);

	public:
		RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		~RPN();

		long	evaluate(const std::string &expression);
};

#endif
