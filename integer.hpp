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

		integer operator+=(const integer &arg)
		{
			uint_t carry = 0;
			for (size_t i = 0; i < size; ++i) {
				carry += digits[i] + arg.digits[i];
				if (max < carry) {
					auto div = divide(carry, mod);
					digits[i] = div.rem;
					carry = div.quot;	
				} else {
					digits[i] = carry;
					carry = 0;
				}
			}
			if (carry) {
				throw overflow("+");
			}
			return *this;
		}

		integer operator-=(const integer &arg)
		{
			uint_t carry = 0;
			for (size_t i = 0; i < size; ++i) {
				int_t diff = digits[i] - arg.digits[i] - carry;
				for (carry = 0; diff < 0; ++carry) {
					diff += mod;
				}
				digits[i] = diff;
			}
			if (carry) {
				throw underflow("-");
			}
			return *this;
		}

		integer operator*=(const integer &arg)
		{
			uint_t carry = 0;
			uint_t sums[size*2] = {0};
			for (size_t i = 0; i < size; ++i) {
				for (size_t j = 0; j < size; ++j) {
					carry += digits[i] * arg.digits[j];
					if (max < carry) {
						auto div = divide(carry, mod);
						sums[i+j] += div.rem;
						carry = div.quot;
					} else {
						sums[i+j] += carry;
						carry = 0;
					}
				}
				if (carry) {
					throw overflow("*");
				}
				digits[i] = sums[i];
				carry = 0;
			}
			return *this;
		}

		integer operator/=(const integer &arg)
		{
			integer quot;
			while (!operator<(arg)) {
				operator-=(arg);
				++quot;
			}
			swap(quot);
			return *this;
		}

		integer operator%=(const integer &arg)
		{
			while (!operator<(arg)) {
				operator-=(arg);
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
		}

		integer operator&=(const integer &arg)
		{
			for (size_t i = 0; i < size; ++i) {
				digits[i] &= arg.digits[i];
			}
			return *this;
		}

		integer operator|=(const integer &arg)
		{
			for (size_t i = 0; i < size; ++i) {
				digits[i] |= arg.digits[i];
			}
			return *this;
		}

		integer operator^=(const integer &arg)
		{
			for (size_t i = 0; i < size; ++i) {
				digits[i] ^= arg.digits[i];
			}
			return *this;
		}

		integer operator~()
		{
			integer arg;
			for (size_t i = 0; i < size; ++i) {
				arg.digits[i] = ~digits[i];
			}
			return arg;
		}

		bool operator==(const integer &arg)
		{
			return digits == arg.digits;
		}

		bool operator<(const integer &arg)
		{
			auto a = algorithm::reversed(digits);
			auto b = algorithm::reversed(arg.digits);
			return algorithm::lexicographical_compare(a, b);
		}

		bool operator!(void)
		{
			auto zero = [](base digit){ return !digit; };
			return algorithm::all_of(digits, zero);
		}

		integer operator=(const std::string &arg)
		{
			digits.fill(0);
			for (char code : arg) {
				uint_t carry = code - '0';
				for (base & digit : digits) {
					carry += digit * 10;
					if (max < carry) {
						auto div = divide(carry, mod);
						digit = div.rem;
						carry = div.quot;
					} else {
						digit = carry;
						carry = 0;
					}
				}
				if (carry) {
					throw overflow("=string");
				}
			}
			return *this;
		}

		integer operator=(uint_t arg)
		{
			digits.fill(0);
			uint_t carry = arg;
			for (base & digit : digits) {
				auto div = divide(carry, mod);
				digit = div.rem;
				carry = div.quot;
				if (!carry) {
					return *this;
				}
			}
			throw overflow("=int");
		}

		operator std::string() const
		{
			std::string string;
			storage array = digits;
			auto reversed = algorithm::reversed(array);
			bool zero;
			do {
				zero = true;
				uint_t carry = 0;
				for (base & digit : reversed) {
					carry *= mod;
					carry += digit;
					auto div = divide(carry, 10);
					digit = div.quot;
					carry = div.rem;
					if (digit) {
						zero = false;
					}
				}
				string += char(carry + '0');
			}
			while (!zero);
			algorithm::reverse(string);
			return string;
		}

		operator uint_t() const
		{
			uint_t carry = 0;
			for (base digit : algorithm::reversed(digits)) {
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

		integer(uint_t arg)
		{
			operator=(arg);
		}

		integer(const std::string &arg)
		{
			operator=(arg);
		}

		void swap(integer &arg)
		{
			digits.swap(arg.digits);
		}
	};

}; // namespace arithmetic

#endif // Metric_integer

