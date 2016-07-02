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
#include <cstring>	// memmove, memset
#include <cstdint>	// uint8_t

namespace arith
{
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
			for (int i = 0; i < size; ++i) {
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
			for (int i = 0; i < size; ++i) {
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
			for (int i = 0; i < size; ++i) {
			 for (int j = 0; j < size; ++j) {
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
				for (int i = div.quot; i < size; ++i) {
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
				for (int i = range - 1; i > -1; --i) {
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
			return std::lexicographical_compare(
				digits.rbegin(), digits.rend(),
				that.digits.rbegin(), that.digits.rend()
				);
		}

		integer operator=(const std::string &string)
		{
			int carry = 0, dec = 1;
			size_t dig = 0, n = string.size();
			while (n-- and dig < size) {
				int num = std::stoi(string.substr(n, 1));
				carry += dec * num;
				if (max < carry) {
					auto div = std::div(carry, max);
					digits[dig] = div.rem;
					carry = div.quot;
					++dig;
				}
				dec *= 10;
			}
			return *this;
		}

		integer operator=(int value)
		{
			int dig = 0;
			while (value) {
				auto div = std::div(value, max);
				digits[dig] = div.rem;
				value = div.quot;
				++dig;
			}
			return *this;
		}

		operator std::string() const
		{
			return "0";
		}

		operator int() const
		{
			size_t dig = 0;
			int value = 0, dec = 1;
			while (dig < size) {
				value += dec * digits[dig];
				dec *= max;
				++dig;
			}
			return value;
		}

		integer()
		{
			digits.fill(0);
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
			for (auto &d : digits) {
				if (d < max) {
				 ++d;
				 return *this;
				}
				d = 0;
			}
			digits.push_back(1);
			return *this;
		}

		integer operator--()
		{
			for (auto &d : digits) {
				if (0 < d) {
				 ++d;
				 return *this;
				}
				d = 0;
			}
			digits.push_back(1);
			return *this;
		}
	};


}; // namespace arith

#endif // Metric_arith

