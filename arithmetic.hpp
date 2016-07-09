#ifndef Metric_arith
#define Metric_arith

/**
 * This file will contain classes for doing arithmetic on numbers of arbitrary
 * or user defined precision. The integer class is based on the concept of the
 * digit in base 256. Our common decimal system is base 10, which means that a
 * digit can have symbols 0 to 9. A base 256 system has digits that are from 0
 * to 255, which is just enough to fit inside a byte. The usual algorithms for
 * numbers, such as addition and multiplication, work the same way as decmial,
 * only in a different base. So an array of bytes serves to store our numbers,
 * and the array size gives the precision of the integer.
 */

#include <array>	// std::array
#include <limits>	// std::numeric_limits
#include <string>	// std::string, std::to_string
#include <utility>	// std::rel_ops
#include <algorithm>	// std::reverse, std::all_of
#include <stdexcept>	// std::overflow_error, std::underflow_error
#include <cinttypes>	// imaxdiv
#include <cstdint>	// uint8_t

namespace arithmetic
{
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
	
	using namespace std::rel_ops;


	template <size_t size> class integer
	{
		using base = uint8_t;
		using int_t = intmax_t;
		using uint_t = uintmax_t;

		using overflow = std::overflow_error;
		using underflow = std::underflow_error;

		static constexpr uint_t max = std::numeric_limits<base>::max();

		std::array<base, size> digits;

	public:

		integer operator+=(const integer &that)
		{
			uint_t carry = 0;
			for (size_t i = 0; i < size; ++i) {
				uint_t num = digits[i] + that.digits[i] + carry;
				if (max < num) {
					auto div = std::imaxdiv(num, max);
					digits[i] = div.rem;
					carry = div.quot;	
				} else {
					digits[i] = num;
					carry = 0;
				}
			}
			if (carry) {
				throw overflow("+");
			}
			return *this;
		}

		integer operator-=(const integer &that)
		{
			uint_t carry = 0;
			for (size_t i = 0; i < size; ++i) {
				int_t num = digits[i] - that.digits[i] - carry;
				carry = 0;
				while (num < 0) {
					num += max;
					++carry;
				}
				digits[i] = num;
			}
			if (carry) {
				throw underflow("-");
			}
			return *this;
		}

		integer operator*=(const integer &that)
		{
			uint_t carry = 0;
			uint_t sums[size*2] = {0};
			for (size_t i = 0; i < size; ++i) {
			 for (size_t j = 0; j < size; ++j) {
				uint_t num = digits[i] * that.digits[j] + carry;
				if (max < num) {
					auto div = std::imaxdiv(num, max);
					sums[i + j] += div.rem;
					carry = div.quot;
				} else {
					sums[i + j] += num;
					carry = 0;
				}
			 }
			 digits[i] = sums[i];
			 sums[size + i] += carry;
			 carry = 0;
			}
			return *this;
		}

		integer operator/=(const integer &that)
		{
			integer quot;
			while (*this >= that) {
				*this -= that;
				++quot;
			}
			swap(quot);
			return *this;
		}

		integer operator%=(const integer &that)
		{
			while (*this >= that) {
				*this -= that;
			}
			return *this;
		}

		integer operator++()
		{
			for (base &dig : digits) {
				if (dig < max) {
					++dig;
					break;
				}
				dig = 0;
			}
			return *this;
		}

		integer operator--()
		{
			for (base &dig : digits) {
				if (0 < dig) {
					--dig;
					break;
				}
				dig = max;
			}
			return *this;
		}

		bool operator==(const integer &that)
		{
			return digits == that.digits;
		}

		bool operator<(const integer &that)
		{
			bool equal = true;
			for (size_t i = 0; i < size; ++i) {
				if (digits[i] > that.digits[i]) {
					return false;
				}
				if (digits[i] < that.digits[i]) {
					equal = false;
				}
			}
			return !equal;
		}

		bool operator!()
		{
			auto zero = [](base dig){ return !dig; };
			return std::all_of(digits.begin(), digits.end(), zero);
		}

		integer operator=(const std::string &string)
		{
			digits.fill(0);
			size_t index = 0;
			uint_t carry = 0;
			uint_t order = 1;
			for (auto it=string.rend(); it!=string.rbegin(); ++it) {
				uint_t num = *it - '0';
				carry += num * order;
				order *= 10;
				if (max < carry) {
					auto div = std::imaxdiv(carry, max);
					digits[index] = div.rem;
					carry = div.quot;
					++index;
				}
			}
			return *this;
		}

		integer operator=(uint_t num)
		{
			digits.fill(0);
			size_t index = 0;
			while (num) {
				auto div = std::imaxdiv(num, max);
				digits[index] = div.rem;
				num = div.quot;
				++index;
				if (size == index) {
					throw overflow("=int");
				}
			}
			return *this;
		}

		operator std::string() const
		{
			std::string string;
			for (base dig : digits) {
				string += ":" + std::to_string(dig);
			}
			return string;
		}

		operator uint_t() const
		{
			size_t index = 0;
			uint_t num = 0, order = 1;
			while (index < size) {
				num += order * digits[index];
				order *= max;
				++index;
			}
			return num;
		}

		integer()
		{
			digits.fill(0);
		}

		integer(uint_t num)
		{
			*this = num;
		}

		integer(const std::string &string)
		{
			*this = string;
		}

		inline void swap(integer &that)
		{
			digits.swap(that.digits);
		}
	};

}; // namespace arithmetic

#endif // Metric_arithmetic

