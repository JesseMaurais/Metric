#ifndef Metric_algorithm
#define Metric_algorithm

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

	template <typename container, typename type> inline
	type accumulate(container &from, type init=0)
	{
		return std::accumulate(std::begin(from), std::end(from), init);
	}

	template <typename containerA, typename containerB> inline
	bool lexicographical_compare(containerA &a, containerB &B)
	{
		auto Abegin = std::begin(a);
		auto Aend = std::end(a);
		auto Bbegin = std::begin(b);
		auto Bend = std::end(b);
		return std::lexicographical_compare(Abegin, Aend, Bbegin, Bend);
	}

}; // namespace algorithm

#endif // Metric_algorithm

