#include <algorithm>
#include <utility>
#include <cmath>

namespace maths
{
	/// The greatest common divisor, so that m|gcd(m, n) and n|gcd(m, n)
	template <typename int_t> inline int_t gcd(int_t m, int_t n)
	{
		if (n < m) std::swap(m, n);
		int_t r;
		while (m) r = n % m, n = m, m = r;
		return n;
	}

	/// The lowest common multiple, so that gcd(m, n)*lcm(m, n) = m*n
	template <typename int_t> inline int_t lcm(int_t m, int_t n)
	{
		return m * (n / gcd(m, n));
	}

	/// The factorial of n, n! = n(n - 1)(n - 2)...
	template <typename int_t> inline int_t fact(int_t n)
	{
		int_t m = 1;
		while (n) m *= n, --n;
		return m;
	}

	/// The k permutations of n elements, n!/(n - k)!
	template <typename int_t> inline int_t perm(int_t n, int_t k)
	{
		k = n - k;
		int_t m = 1;
		while (k--) m *= n, --n;
		return m;
	}

	/// The k combinations of n elements, n!/k!(n - k)!
	template <typename int_t> inline int_t comb(int_t n, int_t k)
	{
		k = std::min(k, n - k);
		int_t m = 1, r = 1;
		while (k) m *= n, r *= k, --n, --k;
		return m/r;
	}

	/// Measures the area for errors of size x under the bell curve
	template <typename float_t> inline float_t erf(float_t x)
	{
		return std::erf(x);
	}

	/// Measures the complement of the error function
	template <typename float_t> inline float_t erfc(float_t x)
	{
		return std::erfc(x);
	}
	
	/// Extends factorials into the real numbers, gamma(n) = (n - 1)!
	template <typename float_t> inline float_t tgamma(float_t x)
	{
		return std::tgamma(x);
	}

	/// The natural logarithm of the gamma function
	template <typename float_t> inline float_t lgamma(float_t x)
	{
		return std::lgamma(x);
	}

	/// The lower incomplete gamma function
	template <typename float_t> inline float_t igamma(float_t a, float_t x)
	{
		float_t s = 0, t = std::pow(x, a)/a;
		do ++a, s += t, t *= x, t /= a;
		while (0 < t);
		s /= std::exp(x);
		return s;
	}

	/// The upper incomplete gamma function
	template <typename float_t> inline float_t igammac(float_t a, float_t x)
	{
		return std::tgamma(a) - igammac(a, x);
	}
	
	/// Extends combinations into the field of real numbers
	template <typename float_t> inline float_t beta(float_t a, float_t b)
	{
		return std::tgamma(a + b)/std::tgamma(a)/std::tgamma(b);
	}
	
	/// The lower incomplete beta function
	template <typename float_t> inline float_t ibeta(float_t a, float_t b, float_t p)
	{
		float_t t = std::pow(p, a);
		float_t s = 0, n = 1, u = 1 - b;
		do s += t/a++, t *= u++, t /= n++, t *= p;
		while (t != 0);
		return s;
	}
	
	/// The power of x raised to the exponent p
	template <typename float_t> inline float_t pow(float_t x, float_t p)
	{
		return std::pow(x, p);
	}

	/// The square root of x
	template <typename float_t> inline float_t sqrt(float_t x)
	{
		return std::sqrt(x);
	}

	/// The cube root of x
	template <typename float_t> inline float_t cbrt(float_t x)
	{
		return std::cbrt(x);
	}

	/// The square root of the sum of the squares of x and y
	template <typename float_t> inline float_t hypot(float_t x, float_t y)
	{
		return std::hypot(x, y);
	}

	/// Equivalent to x*y + z but more precise
	template <typename float_t> inline float_t fma(float_t x, float_t y, float_t z)
	{
		return std::fma(x, y, z);
	}


	/// Euler's number raised to the exponent x
	template <typename float_t> inline float_t exp(float_t x)
	{
		return std::exp(x);
	}

	/// The number 2 raised to the exponent x
	template <typename float_t> inline float_t exp2(float_t x)
	{
		return std::exp2(x);
	}

	/// Equivalent to x*exp2(p) but more precise
	template <typename float_t> inline float_t ldexp(float_t x, int p)
	{
		return std::ldexp(x, p);
	}

	/// The natural logarithm of x, so exp(log(x)) = x
	template <typename float_t> inline float_t log(float_t x)
	{
		return std::log(x);
	}

	/// The logarithm of x expressed in base b, so pow(b, log(x, b)) = x
	template <typename float_t> inline float_t logb(float_t x, float_t b)
	{
		return std::log(x)/std::log(b);
	}

	/// The logarithm of x expressed in base 2, so log2(x) = log(x, 2)
	template <typename float_t> inline float_t log2(float_t x)
	{
		return std::log2(x);
	}

	/// The logarithm of x expressed in base 10, so log10(x) = log(x, 10)
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
	
}; // namespace maths

	
