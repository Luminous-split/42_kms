#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <ctime>
#include <string>

PmergeMe::PmergeMe() : _vecTime(0), _deqTime(0) {}

PmergeMe::PmergeMe(const PmergeMe &other)
	: _vec(other._vec), _deq(other._deq), _vecTime(other._vecTime), _deqTime(other._deqTime) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
		_vecTime = other._vecTime;
		_deqTime = other._deqTime;
	}
	return (*this);
}

PmergeMe::~PmergeMe() {}

/* ---------------------------------------------------------------------------
 * Ford-Johnson (merge-insertion) sort.
 * The algorithm works on positions into the value container, so that every
 * element stays uniquely identifiable even with duplicate values.
 * V is the value container, I the matching index container.
 * ------------------------------------------------------------------------- */

template <typename V>
struct IndexLess
{
	const V	&vals;

	IndexLess(const V &v) : vals(v) {}
	bool operator()(size_t a, size_t b) const { return (vals[a] < vals[b]); }
};

template <typename V, typename I>
static void	mergeInsert(const V &vals, I &idx)
{
	IndexLess<V>	less(vals);
	size_t			n = idx.size();
	I				mainChain;
	I				pend;
	I				partner(vals.size());

	if (n < 2)
		return ;
	// 1. Pair up elements, keep the larger of each pair in the main chain
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		size_t	big = idx[i];
		size_t	small = idx[i + 1];

		if (less(big, small))
			std::swap(big, small);
		mainChain.push_back(big);
		partner[big] = small;
	}
	// 2. Recursively sort the larger elements
	mergeInsert(vals, mainChain);
	// 3. Build the pend chain in the order of the sorted larger elements
	size_t	pairs = mainChain.size();
	for (size_t k = 0; k < pairs; ++k)
		pend.push_back(partner[mainChain[k]]);
	if (n % 2)
		pend.push_back(idx[n - 1]);

	I	sortedBigs(mainChain);

	// b1 is smaller than a1, so it goes first without any comparison
	mainChain.insert(mainChain.begin(), pend[0]);
	// 4. Insert the rest following the Jacobsthal sequence (1, 3, 5, 11, 21, ...)
	size_t	prev = 1;
	size_t	jPrev = 1;
	size_t	jCurr = 3;
	while (prev < pend.size())
	{
		size_t	hi = std::min(jCurr, pend.size());

		for (size_t j = hi; j > prev; --j)
		{
			size_t						elem = pend[j - 1];
			typename I::iterator		bound = mainChain.end();

			// b_j only needs to be compared with elements before its partner a_j
			if (j <= pairs)
				bound = std::find(mainChain.begin(), mainChain.end(), sortedBigs[j - 1]);
			mainChain.insert(std::lower_bound(mainChain.begin(), bound, elem, less), elem);
		}
		prev = hi;
		size_t	next = jCurr + 2 * jPrev;
		jPrev = jCurr;
		jCurr = next;
	}
	idx = mainChain;
}

template <typename V, typename I>
static void	fordJohnsonSort(V &vals)
{
	I	idx;
	V	sorted;

	for (size_t i = 0; i < vals.size(); ++i)
		idx.push_back(i);
	mergeInsert(vals, idx);
	for (size_t i = 0; i < idx.size(); ++i)
		sorted.push_back(vals[idx[i]]);
	vals = sorted;
}

/* ------------------------------------------------------------------------- */

template <typename C>
static void	parseInput(int argc, char **argv, C &out)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string	arg(argv[i]);
		char		*end;
		long		value;

		if (arg.empty() || arg.find_first_not_of("0123456789") != std::string::npos)
			throw std::runtime_error("Error");
		errno = 0;
		value = std::strtol(arg.c_str(), &end, 10);
		if (*end != '\0' || errno == ERANGE || value > INT_MAX)
			throw std::runtime_error("Error");
		out.push_back(static_cast<int>(value));
	}
}

template <typename C>
static void	printSequence(const std::string &label, const C &c)
{
	std::cout << label;
	for (typename C::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

static double	elapsedUs(std::clock_t start, std::clock_t end)
{
	return (static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

void PmergeMe::run(int argc, char **argv)
{
	std::clock_t	start;
	std::vector<int>	before;

	if (argc < 2)
		throw std::runtime_error("Error");
	parseInput(argc, argv, before);

	start = std::clock();
	_vec.clear();
	parseInput(argc, argv, _vec);
	fordJohnsonSort<std::vector<int>, std::vector<size_t> >(_vec);
	_vecTime = elapsedUs(start, std::clock());

	start = std::clock();
	_deq.clear();
	parseInput(argc, argv, _deq);
	fordJohnsonSort<std::deque<int>, std::deque<size_t> >(_deq);
	_deqTime = elapsedUs(start, std::clock());

	printSequence("Before:", before);
	printSequence("After:", _vec);
	std::cout << "Time to process a range of " << _vec.size()
		<< " elements with std::vector : " << _vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
		<< " elements with std::deque  : " << _deqTime << " us" << std::endl;
}
