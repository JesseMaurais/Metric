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
			uint_t sums[size*2] = {0};
			uint_t carry = 0;
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
			}
			for (size_t i = 0; i < size; ++i) {
				carry += sums[i];
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
				throw overflow("*");
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


	template <> class integer<0>
	{
		using base = uint8_t;
		using int_t = intmax_t;
		using uint_t = uintmax_t;
		using storage = std::vector<base>;
		using overflow = std::overflow_error;
		using underflow = std::underflow_error;
		static constexpr auto divide = std::imaxdiv;
		static const uint_t max = std::numeric_limits<base>::max();
		static const uint_t mod = max + 1;

		storage digits;

	public:

		integer operator+=(const integer &arg)
		{
			const size_t digit_size = digits.size();
			const size_t arg_size = arg.digits.size();
			const size_t size = std::min(digit_size, arg_size);
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
			for (size_t i = size; i < digit_size; ++i) {
				carry += digits[i];
				if (max < carry) {
					auto div = divide(carry, mod);
					digits[i] = div.rem;
					carry = div.quot;
				} else {
					digits[i] = carry;
					carry = 0;
					break;
				}
			}
			for (size_t i = size; i < arg_size; ++i) {
				carry += arg.digits[i];
				if (max < carry) {
					auto div = divide(carry, mod);
					digits.push_back(div.rem);
					carry = div.quot;
				}
			}
			while (carry) {
				auto div = divide(carry, mod);
				digits.push_back(div.rem);
				carry = div.quot;
			}
			return *this;
		}

		integer operator-=(const integer &arg)
		{
			const size_t digit_size = digits.size();
			const size_t arg_size = arg.digits.size();
			const size_t size = std::min(digit_size, arg_size);
			uint_t carry = 0;
			for (size_t i = 0; i < size; ++i) {
				int_t diff = digits[i] - arg.digits[i] - carry;
				for (carry = 0; diff < 0; ++carry) {
					diff += mod;
				}
				digits[i] = diff;
			}
			for (size_t i = size; i < digit_size; ++i) {
				int_t diff = digits[i] - carry;
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
			const size_t digit_size = digits.size();
			const size_t arg_size = arg.digits.size();
			const size_t size = digit_size + arg_size;
			uint_t sums[size] = {0};
			uint_t carry = 0;
			for (size_t i = 0; i < digit_size; ++i) {
				for (size_t j = 0; j < arg_size; ++j) {
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
				sums[arg_size + i] += carry;
				carry = 0;
			}
			digits.clear();
			for (size_t k = 0; k < size; ++k) {
				carry += sums[k];
				if (max < carry) {
					auto div = divide(carry, mod);
					digits.push_back(div.rem);
					carry = div.quot;
				} else {
					digits.push_back(carry);
					carry = 0;
				}
			}
			while (carry) {
				auto div = divide(carry, mod);
				digits.push_back(div.rem);
				carry = div.quot;
			}
			while (digits.back() == 0) {
				digits.pop_back();
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
			}
			digits.push_back(1);
			return *this;
		}

		integer operator--()
		{
			for (base & digit : digits) {
				if (0 < digit) {
					--digit;
					return *this;
				}
			}
			throw underflow("--"); // todo
		}

		integer operator~()
		{
			size_t size = digits.size();
			integer arg;
			arg.digits.resize(size);
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
			size_t this_size = digits.size();
			size_t that_size = arg.digits.size();
			if (this_size < that_size) return true;
			if (that_size < this_size) return false;
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
			digits.clear();
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
					digits.push_back(carry);
				}
			}
			return *this;
		}

		integer operator=(uint_t arg)
		{
			digits.clear();
			uint_t carry = arg;
			do {
				auto div = divide(carry, mod);
				digits.push_back(div.rem);
				carry = div.quot;
			}
			while (carry);
			return *this;
		}

		operator std::string() const
		{
			std::string string;
			storage copy = digits;
			auto reversed = algorithm::reversed(copy);
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
			digits.push_back(0);
		}

		integer(uint_t arg)
		{
			operator=(arg);
		}

		integer(const std::string &arg)
		{
			operator=(arg);
		}

		template <size_t size> integer(const integer<size> &arg)
		{
			digits.resize(arg.digits.size());
			algorithm::copy(arg.digits, digits);
		}

		void swap(integer &arg)
		{
			digits.swap(arg.digits);
		}
	};

}; // namespace arithmetic

#endif // Metric_integer

