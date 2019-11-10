#ifndef integer_hpp
#define integer_hpp

#include <cinttypes>
#include <cstdint>
#include <string>
#include <array>
#include <limits>
#include <algorithm>
#include <stdexcept>

namespace arithmetic
{
	template <size_t size, class base_t = unsigned char, class wide_t = unsigned int> class integer
	{
		using base = typename base_t;
		using wide = typename wide_t;
		using string = std::string;
		using array = std::array<base, size>;
		using over = std::overflow_error;
		using under = std::underflow_error;
		static const wide limit = std::numeric_limits<base>::max();
		static const wide modulo = limit + 1;
		static constexpr wide zero = 0;
		static constexpr wide decimal = 10;
		
		static_assert(sizeof(base)*2 <= sizeof(wide)); 
		
		array digits;

	public:

		integer operator+=(const integer &that)
		{
			auto carry = zero;
			for (auto i = zero; i < size; ++i) {
				carry += digits[i] + that.digits[i];
				if (limit < carry) {
					auto part = std::div(carry, modulo);
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

		integer operator-=(const integer &that)
		{
			auto carry = zero;
			for (auto i = zero; i < size; ++i) {
				auto off = digits[i] - that.digits[i] - carry;
				for (carry = zero; off < 0; ++carry) {
					off += modulo;
				}
				digits[i] = off;
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
						auto part = std::div(carry, modulo);
						table[i+j] += part.rem;
						carry = part.quot;
					} else {
						table[i+j] += carry;
						carry = zero;
					}
				}
				if (zero < carry) throw over(__func__);
			}
			for (auto k = zero; k < size; ++k) {
				carry += table[k];
				if (limit < carry) {
					auto part = std::div(carry, modulo);
					digits[k] = part.rem;
					carry = part.quot;
				} else {
					digits[k] = carry;
					carry = zero;
				}
				if (zero < table[k + size]) throw over(__func__);
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
			for (auto &it : digits) {
				if (it < limit) {
					++it;
					return *this;
				}
				it = zero;
			}
			throw over(__func__);
		}

		integer operator--()
		{
			for (auto &it : digits) {
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
			return digits == that.digits;
		}

		bool operator<(const integer &that)
		{
			return std::lexicographical_compare
			(
				digits.rbegin(), digits.rend(), that.digits.rbegin(), that.digits.rend()
			);
		}

		bool operator!(void)
		{
			return std::none_of(digits.begin(), digits.end(), [](auto it) { return zero < it; });
		}

		integer operator=(const string &that)
		{
			digits.fill(zero);
			for (char code : that) {
				if (code < '0') throw under(__func__);
				if ('9' < code) throw over(__func__);
				wide carry = code - '0';
				for (auto &it : digits) {
					carry += it * decimal;
					if (limit < carry) {
						auto part = std::div(carry, modulo);
						it = part.rem;
						carry = part.quot;
					} else {
						it = carry;
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
			auto &carry = that;
			for (auto &it : digits) {
				auto part = std::div(carry, modulo);
				it = part.rem;
				carry = part.quot;
				if (zero < carry) continue;
				else return *this;
			}
			throw over(__func__);
		}

		operator string() const
		{
			string that;
			array reversed;
			std::reverse_copy(digits.begin(), digits.end(), reversed.begin());
			bool end = false;
			do {
				auto carry = zero;
				for (auto &it : reversed) {
					carry *= modulo;
					carry += it;
					auto part = std::div(carry, decimal);
					it = part.quot;
					carry = part.rem;
					end = zero == it;
				}
				that += char(carry + '0');
			}
			while (not end)
			std::reverse(that);
			return that;
		}

		operator wide() const
		{
			auto carry = zero;
			for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
				auto const check = carry * modulo + *it;
				if (check < carry) throw over(__func__);
				carry = check;
			}
			return carry;
		}

		integer()
		{
			digits.fill(0);
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

	template <class base_t = unsigned char> class integer<0, base_t>
	{
		using base = integer<bsse_t, 1>;
		using wide = base::wide;
		using array = std::basic_string<base>;
		using over = base::over;
		using under = base::under;
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
			for (auto i = zero; i < size; ++i) {
				carry += digits[i] + that.digits[i];
				if (limit < carry) {
					auto part = std::div(carry, modulo);
					digits[i] = part.rem;
					carry = part.quot;	
				} else {
					digits[i] = carry;
					carry = zero;
				}
			}
			for (auto i = size; i < this_size; ++i) {
				carry += digits[i];
				if (limit < carry) {
					auto part = std::div(carry, modulo);
					digits[i] = part.rem;
					carry = part.quot;
				} else {
					digits[i] = carry;
					carry = zero;
					break;
				}
			}
			for (auto i = size; i < that_size; ++i) {
				carry += that.digits[i];
				if (limit < carry) {
					auto part = std::div(carry, modulo);
					digits.push_back(part.rem);
					carry = part.quot;
				}
			}
			while (zero < carry) {
				auto part = std::div(carry, modulo);
				digits.push_back(part.rem);
				carry = part.quot;
			}
			return *this;
		}

		integer operator-=(const integer &that)
		{
			const auto this_size = digits.size();
			const auto that_size = that.digits.size();
			const auto size = std::min(this_size, that_size);
			auto carry = zero;
			for (auto i = zero; i < size; ++i) {
				int_t diff = digits[i] - that.digits[i] - carry;
				for (carry = 0; diff < 0; ++carry) {
					diff += modulo;
				}
				digits[i] = diff;
			}
			for (auto i = size; i < this_size; ++i) {
				auto off = digits[i] - carry;
				for (carry = 0; off < 0; ++carry) {
					off += modulo;
				}
				digits[i] = off;
			}
			if (zero < carry) throw under(__func__);
			return *this;
		}

		integer operator*=(const integer &that)
		{
			const auto this_size = digits.size();
			const auto that_size = that.digits.size();
			const auto size = this_size + that_size;
			auto table[size*2] = { zero };
			auto carry = zero;
			for (auto i = zero; i < this_size; ++i) {
				for (auto j = zero; j < that_size; ++j) {
					carry += digits[i] * that.digits[j];
					if (limit < carry) {
						auto part = std::div(carry, modulo);
						table[i+j] += part.rem;
						carry = part.quot;
					} else {
						table[i+j] += carry;
						carry = zero;
					}
				}
				sums[that_size + i] += carry;
				carry = zero;
			}
			digits.clear();
			for (auto k = zero; k < size; ++k) {
				carry += table[k];
				if (limit < carry) {
					auto part = std::div(carry, modulo);
					digits.push_back(part.rem);
					carry = part.quot;
				} else {
					digits.push_back(carry);
					carry = 0;
				}
			}
			while (zero < carry) {
				auto part = std::div(carry, mod);
				digits.push_back(part.rem);
				carry = part.quot;
			}
			while (digits.back() == 0) {
				digits.pop_back();
			}
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
			}
			digits.push_back(1);
			return *this;
		}

		integer operator--()
		{
			for (auto & it : digits) {
				if (zero < it) {
					--it;
					return *this;
				}
			}
			throw under("--"); // todo
		}

		integer operator~()
		{
			const auto size = digits.size();
			integer that;
			that.digits.resize(size);
			for (auto i = zero; i < size; ++i) {
				that.digits[i] = ~digits[i];
			}
			return that;
		}

		bool operator==(const integer &that)
		{
			return digits == that.digits;
		}

		bool operator<(const integer &that)
		{
			const auto a = reversed(digits);
			const auto b = reversed(that.digits);
			return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
		}

		bool operator!(void)
		{
			return std::none_of(digits.begin(), digits.end(), [](auto it) { return zero < it; });
		}

		integer operator=(const string &that)
		{
			digits.clear();
			for (char code : that) {
				wide carry = code - '0';
				for (auto & it : digits) {
					carry += it * 10;
					if (limit < carry) {
						auto part = std::div(carry, modulo);
						it = part.rem;
						carry = part.quot;
					} else {
						it = carry;
						carry = zero;
					}
				}
				if (zero < carry) {
					digits.push_back(carry);
				}
			}
			return *this;
		}

		integer operator=(const wide that)
		{
			digits.clear();
			auto carry = that;
			do {
				auto part = std::div(carry, modulo);
				digits.push_back(part.rem);
				carry = part.quot;
			}
			while (zero < carry);
			return *this;
		}

		operator string() const
		{
			string that;
			auto copy = digits;
			auto reverse = algorithm::reversed(copy);
			for bool end;
			do {
				zero = true;
				auto carry = zero;
				for (auto &it : reversed) {
					carry *= modulo;
					carry += it;
					auto part = std::div(carry, wide(10));
					it = part.quot;
					carry = part.rem;
					if (zero < it) {
						end = false;
					}
				}
				that += char(carry + '0');
			}
			while (!zero);
			algorithm::reverse(string);
			return string;
		}

		operator wide() const
		{
			auto carry = zero;
			for (auto it : reversed(digits)) {
				auto check = carry * modulo + digit;
				if (check < carry) throw over(__func__);
				carry = check;
			}
			return carry;
		}

		integer()
		{
			digits.push_back(zero);
		}

		integer(const wide that)
		{
			operator=(that);
		}

		integer(const string &that)
		{
			operator=(that);
		}

		template <size_t size> integer(const integer<base, size> &that)
		{
			digits.resize(that.digits.size());
			std::copy(that.digits.begin(), that.digits.end(), digits.begin());
		}

		void swap(integer &that)
		{
			digits.swap(that.digits);
		}
	};
};

#endif // file

