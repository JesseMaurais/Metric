#ifndef Metric_algorithm
#define Metric_algorithm

#include <numeric>
#include <algorithm>

namespace algorithm
{
	// Utility for a reversed range-for loop

	template <typename container> struct reversed_iterable
	{
		container &reference;
	};

	template <typename container> inline
	auto begin(const reversed_iterable<container> &reverse)
	{
		return std::rbegin(reverse.reference);
	}

	template <typename container> inline
	auto end(const reversed_iterable<container> &reverse)
	{
		return std::rend(reverse.reference);
	}

	template <typename container> inline
	reversed_iterable<container> reversed(container &&reference)
	{
		return { reference };
	}

	// Iterate over container algorithms

	template <typename container> inline
	void reverse(container &a)
	{
		std::reverse(std::begin(a), std::end(a));
	}

	template <typename container, typename unary> inline
	bool all_of(container &a, unary predicate)
	{
		return std::all_of(std::begin(a), std::end(a), predicate);
	}

	template <typename container, typename unary> inline
	bool any_of(container &a, unary predicate)
	{
		return std::any_of(std::begin(a), std::end(a), predicate);
	}

	template <typename container, typename type> inline
	type accumulate(container &a, type init=0)
	{
		return std::accumulate(std::begin(a), std::end(a), init);
	}

	template <typename container> inline
	bool lexicographical_compare(container &a, container &b)
	{
		return std::lexicographical_compare(std::begin(a), std::end(a),
		                                    std::begin(b), std::end(b));
	}

}; // namespace algorithm

#endif // Metric_algorithm

