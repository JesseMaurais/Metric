#ifndef algorithm_hpp
#define algorithm_hpp

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

	template <typename container, typename predicate>
	inline bool all_of(container &c, predicate unary)
	{
		return std::all_of(begin(c), end(c), unary);
	}

	template <typename container, typename predicate>
	inline bool any_of(container &c, predicate unary)
	{
		return std::any_of(begin(c), end(c), unary);
	}

	template <typename container, typename predicate>
	inline bool none_of(container &c, predicate unary)
	{
		return std::none_of(begin(c), end(c), unary);
	}

	template <typename container, typename function>
	inline function for_each(container &c, function unary)
	{
		return std::for_each(begin(c), end(c), unary);
	}

	template <typename from_container, typename to_container>
	inline auto copy(const from_container &from, const to_container &to)
	{
		return std::copy(begin(from), end(from), begin(to));
	}

	template <typename container, typename type>
	inline auto count(const container &c, const type &value)
	{
		return std::count(begin(c), end(c), value);
	}

	template <typename container, typename function>
	inline auto count_if(const container &c, function unary)
	{
		return std::count_if(begin(c), end(c), unary);
	}

	template <typename container> inline
	void reverse(container &a)
	{
		std::reverse(begin(a), end(a));
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

}; // namespace

#endif // file

