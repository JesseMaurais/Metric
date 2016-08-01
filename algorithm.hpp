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
		std::reverse(begin(a), end(a));
	}

	template <typename container, typename predicate> inline
	bool all_of(container &a, predicate unary)
	{
		return std::all_of(begin(a), end(a), unary);
	}

	template <typename container, typename predicate> inline
	bool any_of(container &a, predicate unary)
	{
		return std::any_of(begin(a), end(a), unary);
	}

	template <typename container, typename type> inline
	type accumulate(container &a, type init=0)
	{
		return std::accumulate(begin(a), end(a), init);
	}

	template <typename containerA, typename containerB> inline
	bool lexicographical_compare(containerA &a, containerB &b)
	{
		return std::lexicographical_compare(begin(a), end(a),
		                                    begin(b), end(b));
	}

}; // namespace algorithm

#endif // Metric_algorithm

