#ifndef Metric_algorithm
#define Metric_algorithm

namespace algorithm
{
	// Iterator over container algorithms

	template <typename container, typename unary> inline
	bool all_of(container &to, unary predicate)
	{
		return std::all_of(std::begin(to), std::end(to), predicate);
	}

	template <typename container, typename unary> inline
	bool any_of(container &to, unary predicate)
	{
		return std::any_of(std::begin(to), std::end(to), predicate);
	}

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

}; // namespace algorithm

#endif // Metric_algorithm

