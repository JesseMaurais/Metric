/**
 * Function overloads are insufficient for emitting with Lux since the C++
 * compiler does not know which overload to use. Simply wrapping functions
 * in a template allows us to specify the type explicitly when wrapped. We
 * export most of the math functions of C++11 
 */

#include <algorithm>
#include <utility>
#include <cmath>

namespace maths
{
	// common factors

	template <typename int_t> inline int_t gcd(int_t m, int_t n)
	{
		if (n < m) std::swap(m, n);
		int_t r;
		while (m) r = n % m, n = m, m = r;
		return n;
	}

	template <typename int_t> inline int_t lcm(int_t m, int_t n)
	{
		return m * (n / gcd(m, n));
	}

	// combinatorial

	template <typename int_t> inline int_t fact(int_t n)
	{
		int_t m = 1;
		while (n) m *= n, --n;
		return m;
	}

	template <typename int_t> inline int_t perm(int_t n, int_t k)
	{
		k = n - k;
		int_t m = 1;
		while (k--) m *= n, --n;
		return m;
	}

	template <typename int_t> inline int_t comb(int_t n, int_t k)
	{
		k = std::min(k, n - k);
		int_t m = 1, r = 1;
		while (k) m *= n, r *= k, --n, --k;
		return m/r;
	}

	// error & complement

	template <typename float_t> inline float_t erf(float_t x)
	{
		return std::erf(x);
	}

	template <typename float_t> inline float_t erfc(float_t x)
	{
		return std::erfc(x);
	}

	// gamma & log-gamma & beta & incomplete-gamma

	template <typename float_t> inline float_t tgamma(float_t x)
	{
		return std::tgamma(x);
	}

	template <typename float_t> inline float_t lgamma(float_t x)
	{
		return std::lgamma(x);
	}

	template <typename float_t> inline float_t igammac(uintmax_t a, float_t x)
	{
		float_t s = 0, t = std::pow(x, a)/a;
		do ++a, s += t, t *= x, t /= a;
		while (0 < t);
		s /= std::exp(x);
		return s;
	}

	template <typename float_t> inline float_t igamma(uintmax_t a, float_t x)
	{
		return std::tgamma(a) - igammac(a, x);
	}

	template <typename float_t> inline float_t beta(float_t a, float_t b)
	{
		return std::tgamma(a + b)/std::tgamma(a)/std::tgamma(b);
	}

	// power

	template <typename float_t> inline float_t pow(float_t x, float_t exp)
	{
		return std::pow(x, exp);
	}

	template <typename float_t> inline float_t sqrt(float_t x)
	{
		return std::sqrt(x);
	}

	template <typename float_t> inline float_t cbrt(float_t x)
	{
		return std::cbrt(x);
	}

	template <typename float_t> inline float_t hypot(float_t x, float_t y)
	{
		return std::hypot(x, y);
	}

	// exponential

	template <typename float_t> inline float_t exp(float_t x)
	{
		return std::exp(x);
	}

	template <typename float_t> inline float_t exp2(float_t x)
	{
		return std::exp2(x);
	}

	template <typename float_t> inline float_t ldexp(float_t x, int exp)
	{
		return std::ldexp(x, exp);
	}

	// logarithmic

	template <typename float_t> inline float_t log(float_t x)
	{
		return std::log(x);
	}

	template <typename float_t> inline float_t log2(float_t x)
	{
		return std::log2(x);
	}

	template <typename float_t> inline float_t log10(float_t x)
	{
		return std::log10(x);
	}

	// trigonometric

	template <typename float_t> inline float_t sin(float_t x)
	{
		return std::sin(x);
	}

	template <typename float_t> inline float_t cos(float_t x)
	{
		return std::cos(x);
	}

	template <typename float_t> inline float_t tan(float_t x)
	{
		return std::tan(x);
	}

	template <typename float_t> inline float_t asin(float_t x)
	{
		return std::asin(x);
	}

	template <typename float_t> inline float_t acos(float_t x)
	{
		return std::acos(x);
	}

	template <typename float_t> inline float_t atan(float_t x)
	{
		return std::atan(x);
	}

	template <typename float_t> inline float_t atan2(float_t y, float_t x)
	{
		return std::atan2(y, x);
	}

	template <typename float_t> inline float_t sinh(float_t x)
	{
		return std::sinh(x);
	}

	template <typename float_t> inline float_t cosh(float_t x)
	{
		return std::cosh(x);
	}

	template <typename float_t> inline float_t tanh(float_t x)
	{
		return std::tanh(x);
	}

	template <typename float_t> inline float_t asinh(float_t x)
	{
		return std::asinh(x);
	}

	template <typename float_t> inline float_t acosh(float_t x)
	{
		return std::acosh(x);
	}

	template <typename float_t> inline float_t atanh(float_t x)
	{
		return std::atanh(x);
	}

	// lossless linear

	template <typename float_t> inline float_t fma(float_t x, float_t y, float_t z)
	{
		return std::fma(x, y, z);
	}

}; // namespace maths

