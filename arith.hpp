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

#include <array>
#include <limits>
#include <cstdint>
#include <string>

namespace arith
{
	template <size_t size> class integer
	{
		// Use bytes as digits
		using base = uint8_t;
		// We need the upper limit for the base type for digits
		constexpr size_t max = std::numeric_limits<base>::max();
		// Store digits in an array
		std::array<base, size> digits;

	public:

		// Column style addition, digit-by-digit
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

		// Classical "long" multiplication
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
					sums[i + j] = num;
					carry = 0;
				}
			 }
			 sums[size + i] += carry;
			 digits[i] = sums[i];
			 carry = 0;
			}
			return *this;
		}

		// Convert from a decimal number in a string
		integer operator=(const std::string &string)
		{
			size_t dig = 0, dec = 1, n = string.size();
			int carry = 0;
			while (--n and dig < size) {
				carry += dec * std::stoi(string[n]);
				if (max < carry) {
					auto div = std::div(carry, max);
					digits[dig++] = div.rem;
					carry = div.quot;
				}
				dec *= 10;
			}
		}

		// Convert from a true integer
		integer operator=(int value)
		{
			// should be easy
		}
	};

}; // namespace arith

#endif // Metric_arith

