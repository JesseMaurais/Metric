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
#include <vector>	// std::vector
#include <limits>	// std::numeric_limits
#include <string>	// std::string
#include <utility>	// std::rel_ops
#include <cstring>	// memmove, memset
#include <cstdint>	// uint8_t

namespace arith
{
	template <typename number> inline
	number operator+(const number &a, const number &b)
	{
		number c = a;
		c += b;
		return c;
	}

	template <typename number> inline
	number operator-(const number &a, const number &b)
	{
		number c = a;
		c -= b;
		return c;
	}

	template <typename number> inline
	number operator*(const number &a, const number &b)
	{
		number c = a;
		c *= b;
		return c;
	}

	template <typename number> inline
	number operator/(const number &a, const number &b)
	{
		number c = a;
		c /= b;
		return c;
	}

	template <typename number> inline
	number operator%(const number &a, const number &b)
	{
		number c = a;
		c %= b;
		return c;
	}

	template <typename number> inline
	number operator++(number &a, int postfix)
	{
		number b = a;
		--a;
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
	number operator<<(const number &a, int delta)
	{
		number b = a;
		b <<= delta;
		return b;
	}

	template <typename number> inline
	number operator>>(const number &a, int delta)
	{
		number b = a;
		b >>= delta;
		return b;
	}
	
	using namespace std::rel_ops;


	template <size_t size> class integer
	{
		using base = uint8_t;
		// We need the upper limit of the base type for our digits
		static constexpr int max = std::numeric_limits<base>::max();
		// Store digits in an array
		std::array<base, size> digits;

	public:

		integer operator+=(const integer &that)
		{
			int carry = 0;
			for (size_t i = 0; i < size; ++i) {
				int num = digits[i] + that.digits[i] + carry;
				if (max < num) {
					auto div = std::div(num, max);
					digits[i] = div.rem;
					carry = div.quot;	
				} else {
					digits[i] = num;
					carry = 0;
				}
			}
			return *this;
		}

		integer operator-=(const integer &that)
		{
			int carry = 0;
			for (size_t i = 0; i < size; ++i) {
				int num = digits[i] - that.digits[i] - carry;
				carry = 0;
				while (num < 0) {
					num += max;
					++carry;
				}
				digits[i] = num;
			}
			return *this;
		}

		integer operator*=(const integer &that)
		{
			int carry = 0;
			int sums[size*2] = {0};
			for (size_t i = 0; i < size; ++i) {
			 for (size_t j = 0; j < size; ++j) {
				int num = digits[i] * that.digits[j] + carry;
				if (max < num) {
					auto div = std::div(num, max);
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
			for (auto &d : digits) {
				if (d < max) {
					++d;
					break;
				}
				d = 0;
			}
			return *this;
		}

		integer operator--()
		{
			for (auto &d : digits) {
				if (0 < d) {
					--d;
					break;
				}
				d = max;
			}
			return *this;
		}

		integer operator<<=(int delta)
		{
			// Find whole and partial move
			auto div = std::div(delta, max);
			if (div.quot) {
				// Move whole bytes
				base *ptr = digits.data();
				size_t range = size - div.quot;
				size_t bytes = range * sizeof(base);
				std::memmove(ptr + div.quot, ptr, bytes);
				std::memset(ptr, base(0), div.quot);
			}
			if (div.rem) {
				// Move partial bits
				const base mask = ~base(0) << div.rem;
				base carry = 0;
				for (size_t i = div.quot; i < size; ++i) {
					base bits = carry >> div.rem;
					carry = digits[i] bitand mask;
					digits[i] <<= div.rem;
					digits[i] |= bits; 
				}
			}
			return *this;
		}

		integer operator>>=(int delta)
		{
			// Find whole and partial move
			auto div = std::div(delta, max);
			size_t range = size - div.quot;
			if (div.quot) {
				// Move whole bytes
				base *ptr = digits.data();
				size_t bytes = range * sizeof(base);
				std::memmove(ptr, ptr + div.quot, bytes);
				std::memset(ptr + range, base(0), div.quot);
			}
			if (div.rem) {
				// Move partial bits
				const base mask = ~base(0) >> div.rem;
				base carry = 0;
				for (size_t i = range - 1; i > -1; --i) {
					base bits = carry << div.rem;
					carry = digits[i] bitand mask;
					digits[i] >>= div.rem;
					digits[i] |= bits;
				} 
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

		integer operator=(const std::string &string)
		{
			int carry = 0, order = 1, index = 0;
			for (const auto ch : string) {
				int num = ch - '0';
				carry += order * num;
				if (max < carry) {
					auto div = std::div(carry, max);
					digits[index] = div.rem;
					carry = div.quot;
					++index;
				}
				order *= 10;
			}
			return *this;
		}

		integer operator=(int value)
		{
			int index = 0;
			while (value) {
				auto div = std::div(value, max);
				digits[index] = div.rem;
				value = div.quot;
				++index;
			}
			return *this;
		}

		operator std::string() const
		{
			std::string string;
			int carry = 0;
			size_t index = size;
			for (size_t i = 0; i < size; ++i) {
				base dig = digits[--index];
				do {
					auto div = std::div(dig, 10);
					string += '0' + div.rem;
					dig = div.quot;
				}
				while (dig);
			}
			return string;
		}

		operator int() const
		{
			size_t index = 0;
			int value = 0, order = 1;
			while (index < size) {
				value += order * digits[index];
				order *= max;
				++index;
			}
			return value;
		}

		integer()
		{
			digits.fill(0);
		}

		integer(int value)
		{
			*this = value;
		}

		integer(const std::string &string)
		{
			*this = string;
		}

		inline void swap(integer &that)
		{
			std::swap(digits, that.digits);
		}
	};

	
	template <> class integer<0>
	{
		using base = uint8_t;
		// We need the upper limit of the base type for our digits
		static constexpr int max = std::numeric_limits<base>::max();
		// Store digits in a vector
		std::vector<base> digits;

	public:

		integer operator++()
		{
			for (auto &dig : digits) {
				if (dig < max) {
				 ++dig;
				 return *this;
				}
				dig = 0;
			}
			digits.push_back(1);
			return *this;
		}

		integer operator--()
		{
			for (auto &dig : digits) {
				if (0 < dig) {
				 ++dig;
				 return *this;
				}
				dig = 0;
			}
			digits.push_back(1);
			return *this;
		}
	};


}; // namespace arith

#endif // Metric_arith

