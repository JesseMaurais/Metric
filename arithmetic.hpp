#ifndef Metric_arithmetic
#define Metric_arithmetic

/**
 * This file defines global operator overloads which reduce common arithmetic
 * operations to their compound assignment form. This way we write the latter
 * and we get the former for free. We take compound assignment as the primary
 * operation because in some cases it's more efficient to implement. All this
 * is specific to the namespace. Only types defined in the same namespace are
 * invoked on argument dependent lookup.
 */

#include <utility>

namespace arithmetic
{
	using namespace std::rel_ops;

	template <typename number> inline
	number operator+(number a, const number &b)
	{
		return a += b;
	}

	template <typename number> inline
	number operator-(number a, const number &b)
	{
		return a -= b;
	}

	template <typename number> inline
	number operator*(number a, const number &b)
	{
		return a *= b;
	}

	template <typename number> inline
	number operator/(number a, const number &b)
	{
		return a /= b;
	}

	template <typename number> inline
	number operator%(number a, const number &b)
	{
		return a %= b;
	}

	template <typename number> inline
	number operator++(number &a, int postfix)
	{
		number b = a;
		++a;
		return b;
	}

	template <typename number> inline
	number operator--(number &a, int postfix)
	{
		number b = a;
		--a;
		return b;
	}

	template <typename number> inline
	number operator<<(number a, unsigned b)
	{
		return a <<= b;
	}

	template <typename number> inline
	number operator>>(number a, unsigned b)
	{
		return a >>= b;
	}

}; // namespace arithmetic

#endif // Metric_arithmetic

