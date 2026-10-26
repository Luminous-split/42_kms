#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <cstddef>

class PmergeMe
{
	private:
		std::vector<int>	_vec;
		std::deque<int>		_deq;
		double				_vecTime;
		double				_deqTime;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void	run(int argc, char **argv);
};

#endif
