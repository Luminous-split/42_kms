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

/*
 * Insertion step for one level.
 * chain:     the sorted big elements of this level (a1 < a2 < ... < am)
 * partner:   partner[offset + a] is the small element paired with a
 * straggler: the unpaired element of this level, or none == vals.size()
 * After the call, chain holds every element of this level, sorted.
 */
template <typename V, typename I>
static void	insertPending(const V &vals, I &chain, const I &partner,
				size_t offset, size_t straggler)
{
	IndexLess<V>	less(vals);
	size_t			none = vals.size();
	size_t			pairs = chain.size();
	I				pend;
	I				sortedBigs(chain);

	// Build the pend chain in the order of the sorted big elements
	for (size_t k = 0; k < pairs; ++k)
		pend.push_back(partner[offset + chain[k]]);
	if (straggler != none)
		pend.push_back(straggler);

	// b1 is smaller than a1, so it goes first without any comparison
	chain.insert(chain.begin(), pend[0]);
	// Insert the rest following the Jacobsthal sequence (1, 3, 5, 11, 21, ...)
	size_t	prev = 1;
	size_t	jPrev = 1;
	size_t	jCurr = 3;
	while (prev < pend.size())
	{
		size_t	hi = std::min(jCurr, pend.size());

		for (size_t j = hi; j > prev; --j)
		{
			size_t						elem = pend[j - 1];
			typename I::iterator		bound = chain.end();

			// b_j only needs to be compared with elements before its partner a_j
			if (j <= pairs)
				bound = std::find(chain.begin(), chain.end(), sortedBigs[j - 1]);
			chain.insert(std::lower_bound(chain.begin(), bound, elem, less), elem);
		}
		prev = hi;
		size_t	next = jCurr + 2 * jPrev;
		jPrev = jCurr;
		jCurr = next;
	}
}

/*
 * Iterative version of the recursion "sort the big elements, then insert the
 * small ones". The pairing of a level never depends on a sorted result, so:
 *  1. Going down: pair the elements level by level until one element is left,
 *     and remember each level's partners and straggler.
 *  2. Going up: from the top level back to level 0, insert that level's
 *     small elements into the sorted chain.
 * Every comparison is the same as in the recursive version.
 */
template <typename V, typename I>
static void	mergeInsert(const V &vals, I &idx)
{
	IndexLess<V>	less(vals);
	size_t			n = vals.size();
	size_t			depth = 0;
	I				level(idx);
	I				partner;	// partner[depth * n + big] = small
	I				stragglers;	// one per level, n when there is none

	if (idx.size() < 2)
		return ;
	// 1. Going down: pair up, keep the bigger of each pair for the next level
	while (level.size() > 1)
	{
		I	bigs;

		partner.resize((depth + 1) * n);
		for (size_t i = 0; i + 1 < level.size(); i += 2)
		{
			size_t	big = level[i];
			size_t	small = level[i + 1];

			if (less(big, small))
				std::swap(big, small);
			bigs.push_back(big);
			partner[depth * n + big] = small;
		}
		stragglers.push_back(level.size() % 2 ? level.back() : n);
		level = bigs;
		++depth;
	}
	// 2. Going up: the top level has one element, so it is already sorted
	while (depth > 0)
	{
		--depth;
		insertPending(vals, level, partner, depth * n, stragglers[depth]);
	}
	idx = level;
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
