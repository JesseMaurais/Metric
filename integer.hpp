#ifndef integer_hpp
#define integer_hpp

#include <cinttypes>
#include <cstdint>
#include <string>
#include <array>
#include <limits>
#include <stdexcept>
#include <any>

#include "algorithm.hpp"
#include "arithmetic.hpp"

namespace arithmetic
{
	template <class base_t = unsigned char, size_t size, class wide_t = std::uintmax_t> class integer
	{
		using base = typename base_t;
		using wide = typename wide_t;
		using string = std::string;
		using view = std::string_view<base>;
		using array = std::array<base, size>;
		using over = std::overflow_error;
		using under = std::underflow_error;
		static inline auto divide = std::imaxdiv;
		static const wide limit = std::numeric_limits<base>::max();
		static const wide modulo = limit + 1;
		static constexpr wide zero = 0;
		
		static_assert(sizeof(base)*2 < sizeof(wide), "Can overflow"); 
		
		array digits;

	public:

		integer operator+=(const integer &that)
		{
			auto carry = zero;
			for (size_t it = zero; it < size; ++it) {
				carry += digits[it] + that.digits[it];
				if (limit < carry) {
					auto part = divide(carry, modulo);
					digits[it] = part.rem;
					carry = part.quot;
				} else {
					digits[it] = carry;
					carry = zero;
				}
			}
			if (zero < carry) throw over(__func__);
			return *this;
		}

		integer operator-=(const integer &that)
		{
			auto carry = zero;
			for (auto it = zero; it < size; ++it) {
				auto off = digits[it] - that.digits[it] - carry;
				for (carry = zero; off < 0; ++carry) {
					off += modulo;
				}
				digits[it] = off;
			}
			if (zero < carry) throw under(__func__);
			return *this;
		}

		integer operator*=(const integer &that)
		{
			auto table[size*2] = { zero };
			auto carry = zero;
			for (auto i = zero; i < size; ++i) {
				for (auto j = zero; j < size; ++j) {
					carry += digits[i] * that.digits[j];
					if (limit < carry) {
						auto part = divide(carry, modulo);
						table[i+j] += part.rem;
						carry = part.quot;
					} else {
						table[i+j] += carry;
						carry = zero;
					}
				}
				const auto more = table[i + size];
				if (more > more or zero < carry) throw over(__func__);
			}
			for (auto i = zero; i < size; ++i) {
				carry += matrix[i];
				if (limit < carry) {
					auto part = divide(carry, modulo);
					digits[i] = part.rem;
					carry = part.quot;
				} else {
					digits[i] = carry;
					carry = zero;
				}
			}
			if (zero < carry) throw over(__func__);
			return *this;
		}

		integer operator/=(const integer &that)
		{
			integer quot;
			while (!operator<(that)) {
				operator-=(that);
				++quot;
			}
			swap(quot);
			return *this;
		}

		integer operator%=(const integer &that)
		{
			while (!operator<(that)) {
				operator-=(that);
			}
			return *this;
		}

		integer operator++()
		{
			for (auto & it : digits) {
				if (it < limit) {
					++it;
					return *this;
				}
				digit = zero;
			}
			throw over(__func__);
		}

		integer operator--()
		{
			for (auto & it : digits) {
				if (zero < it) {
					--it;
					return *this;
				}
				it = limit;
			}
			throw under(__func__);
		}

		bool operator==(const integer &that)
		{
			return view(digits).compare(that.digits) == 0;
		}

		bool operator<(const integer &that)
		{
			auto a = reversed(digits);
			auto b = reversed(that.digits);
			return compare(a, b);
		}

		bool operator!(void)
		{
			return algorithm::all_of(digits, [](auto it) { return zero < it; });
		}

		integer operator=(const string &that)
		{
			digits.fill(zero);
			for (char code : that) {
				auto carry = code - '0';
				for (auto & decimal : digits) {
					carry += decimal * 10;
					if (limit < carry) {
						auto part = divide(carry, modulo);
						dec = part.rem;
						carry = part.quot;
					} else {
						decimal = carry;
						carry = zero;
					}
				}
				if (zero < carry) throw over(__func__);
			}
			return *this;
		}

		integer operator=(wide that)
		{
			digits.fill(zero);
			auto carry = that;
			for (auto & digit : digits) {
				auto part = divide(carry, modulo);
				digit = part.rem;
				carry = part.quot;
				if (zero < carry) continue;
				else return *this;
			}
			throw over(__func__);
		}

		operator string() const
		{
			string code;
			auto matrix = digits;
			auto reversed = algorithm::reversed(matrix);
			for (bool end = true; not end;) {
				auto carry = zero;
				for (auto & digit : reversed) {
					carry *= modulo;
					carry += digit;
					auto part = divide(carry, 10);
					digit = part.quot;
					carry = part.rem;
					end = zero < digit;
				}
				string += char(carry + '0');
			}
			algorithm::reverse(code);
			return code;
		}
		
		operator view() const
		{
			return view(digits.data(), size);	
		}

		operator wide() const
		{
			auto carry = zero;
			for (auto digit : reversed(digits)) {
				auto const check = carry * modulo + digit;
				if (check < carry) throw over(__func__);
				carry = check;
			}
			return carry;
		}

		integer()
		{
			digits.fill(zero);
		}

		integer(const wide that)
		{
			operator=(that);
		}

		integer(const string &that)
		{
			operator=(that);
		}

		void swap(integer &that)
		{
			digits.swap(that.digits);
		}
	};

	template <class base_t = unsigned char> class integer<base_t, 0>
	{
		using base = integer<bsse_t, 1>;
		using wide = base::wide;
		using array = std::basic_string<base>;
		using over = base::over;
		using under = base::under;
		static constexpr auto divide = base::divide;
		static inline const auto zero = base::zero;
		static const wide limit = base::limit;
		static const wide modulo = base::modulo;

		array digits;

	public:

		integer operator+=(const integer &that)
		{
			const auto this_size = digits.size();
			const auto that_size = that.digits.size();
			const auto size = std::min(this_size, that_size);
			auto carry = zero;
			for (size_t i = 0; i < size; ++i) {
				carry += digits[i] + that.digits[i];
				if (limit < carry) {
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
*/
}; // namespace

#endif // file

