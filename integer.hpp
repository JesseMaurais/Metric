#ifndef Metric_integer
#define Metric_integer

#include <cinttypes>
#include <cstdint>
#include <string>
#include <array>
#include <limits>
#include <stdexcept>

#include "algorithm.hpp"
#include "arithmetic.hpp"

namespace arithmetic
{
	template <size_t size> class integer
	{
		using base = uint8_t;
		using int_t = intmax_t;
		using uint_t = uintmax_t;
		using storage = std::array<base, size>;
		using overflow = std::overflow_error;
		using underflow = std::underflow_error;
		static constexpr auto divide = std::imaxdiv;
		static const uint_t max = std::numeric_limits<base>::max();
		static const uint_t mod = max + 1;

		storage digits;

	public:

		integer operator+=(const integer &that)
		{
			uint_t carry = 0;
			for (size_t i = 0; i < size; ++i) {
				carry += digits[i] + that.digits[i];
				if (max < carry) {
					auto div = divide(carry, mod);
					digits[i] = div.rem;
					carry = div.quot;	
				} else {
					digits[i] = carry;
					carry = 0;
				}
			}
			if (0 < carry) {
				throw overflow("+");
			}
			return *this;
		}

		integer operator-=(const integer &that)
		{
			uint_t carry = 0;
			for (size_t i = 0; i < size; ++i) {
				int_t diff = digits[i] - that.digits[i] - carry;
				for (carry = 0; diff < 0; ++carry) {
					diff += mod;
				}
				digits[i] = diff;
			}
			if (0 < carry) {
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
					carry += digits[i] * that.digits[j];
					if (max < carry) {
						auto div = divide(carry, mod);
						sums[i+j] += div.rem;
						carry = div.quot;
					} else {
						sums[i+j] += carry;
						carry = 0;
					}
				}
				if (0 < carry) {
					throw overflow("*");
				}
				digits[i] = sums[i];
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
			for (base & digit : digits) {
				if (digit < max) {
					++digit;
					return *this;
				}
				digit = 0;
			}
			throw overflow("++");
			return *this;
		}

		integer operator--()
		{
			for (base & digit : digits) {
				if (0 < digit) {
					--digit;
					return *this;
				}
				digit = max;
			}
			throw underflow("--");
			return *this;
		}

		integer operator=(const std::string &string)
		{
			digits.fill(0);
			for (char code : string) {
				uint_t carry = code - '0';
				for (size_t i = 0; i < size; ++i) {
					carry += digits[i] * 10;
					if (max < carry) {
						auto div = divide(carry, mod);
						digits[i] = div.rem;
						carry = div.quot;
					} else {
						digits[i] = carry;
						carry = 0;
					}
				}
				if (0 < carry) {
					throw overflow("=string");
				}
			}
			return *this;
		}

		integer operator=(uint_t number)
		{
			digits.fill(0);
			for (size_t i = 0; 0 < number; ++i) {
				if (size == i) {
					throw overflow("=int");
				}
				auto div = divide(number, mod);
				digits[i] = div.rem;
				number = div.quot;
			}
			return *this;
		}

		operator std::string() const
		{
			std::string string;
			integer number = *this;
			auto reversed = algorithm::reversed(number.digits);
			bool zero = !number;
			while (!zero)
			{
				zero = true;
				uint_t carry = 0;
				for (base & digit : reversed) {
					carry *= mod;
					carry += digit;
					auto div = divide(carry, 10);
					digit = div.quot;
					carry = div.rem;
					if (0 < digit) {
						zero = false;
					}
				}
				string += char(carry + '0');
			}
			algorithm::reverse(string);
			return string;
		}

		operator uint_t() const
		{
			uint_t carry = 0;
			for (auto digit : algorithm::reversed(digits)) {
				uint_t check = carry * mod + digit;
				if (check < carry) {
					throw overflow("int=");
				}
				carry = check;
			}
			return carry;
		}

		integer()
		{
			digits.fill(0);
		}

		integer(uint_t num)
		{
			*this = num;
		}

		integer(const storage &array)
		{
			*this = array;
		}

		integer(const std::string &string)
		{
			*this = string;
		}

		void swap(integer &that)
		{
			digits.swap(that.digits);
		}

		bool operator==(const integer &that)
		{
			return digits == that.digits;
		}

		bool operator<(const integer &that)
		{
			auto A = algorithm::reversed(digits);
			auto B = algorithm::reversed(that.digits);
			return algorithm::lexicographical_compare(A, B);
		}

		bool operator!()
		{
			auto zero = [](base dig){return !dig;};
			return algorithm::all_of(digits, zero);
		}
	};

}; // namespace arithmetic

#endif // Metric_integer

