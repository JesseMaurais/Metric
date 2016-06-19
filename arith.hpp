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

		
	};

}; // namespace arith

#endif // Metric_arith

