#include <algorithm>
#include <utility>
#include <cmath>

namespace maths
{
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

	template <typename float_t> inline float_t erf(float_t x)
	{
		return std::erf(x);
	}

	template <typename float_t> inline float_t erfc(float_t x)
	{
		return std::erfc(x);
	}
	
	template <typename float_t> inline float_t tgamma(float_t x)
	{
		return std::tgamma(x);
	}

	template <typename float_t> inline float_t lgamma(float_t x)
	{
		return std::lgamma(x);
	}

	template <typename float_t> inline float_t igammac(float_t a, float_t x)
	{
		float_t s = 0, t = std::pow(x, a)/a;
		do ++a, s += t, t *= x, t /= a;
		while (0 < t);
		s /= std::exp(x);
		return s;
	}

	template <typename float_t> inline float_t igamma(float_t a, float_t x)
	{
		return std::tgamma(a) - igammac(a, x);
	}
	
	template <typename float_t> inline float_t beta(float_t a, float_t b)
	{
		return std::tgamma(a + b)/std::tgamma(a)/std::tgamma(b);
	}
	
	template <typename float_t> inline float_t ibeta(float_t a, float_t b, float_t p)
	{
		float_t t = std::pow(p, a);
		float_t s = 0, n = 1, u = 1 - b;
		do s += t/a++, t *= u++, t /= n++, t *= p;
		while (t != 0);
		return s;
	}
	
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

	template <typename float_t> inline float_t log(float_t x)
	{
		return std::log(x);
	}

	template <typename float_t> inline float_t logb(float_t x, float_t b)
	{
		return std::log(x)/std::log(b);
	}

	template <typename float_t> inline float_t log2(float_t x)
	{
		return std::log2(x);
	}

	template <typename float_t> inline float_t log10(float_t x)
	{
		return std::log10(x);
	}
	
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

	template <typename float_t> inline float_t fma(float_t x, float_t y, float_t z)
	{
		return std::fma(x, y, z);
	}
	
}; // namespace maths

	