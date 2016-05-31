#include <algorithm>
#include <utility>
#include <cmath>

namespace maths
{
	// numeric

	template <typename int_t> inline int_t gcd(int_t m, int_t n)
	{
		if (n < m) std::swap(m, n);
		int_t r;
		while (m) r = n % m, n = m, m = r;
		return n;
	}

	template <typename int_t> inline int_t lcm(int_t m, int_t n)
	{
		return (m * n) / gcd(m, n);
	}

	// combinatorial

	template <typename int_t> inline int_t fact(int_t n)
	{
		int_t m = n;
		while (--n) m *= n;
		return m;
	}

	template <typename int_t> inline int_t perm(int_t n, int_t k)
	{
		if (n < k) std::swap(n, k);
		int_t m = n;
		k = n - k;
		while (--k) --n, m *= n;
		return m;
	}

	template <typename int_t> inline int_t comb(int_t n, int_t k)
	{
		if (n < k) std::swap(n, k);
		k = std::min(k, n - k);
		int_t m = n;
		int_t r = k;
		while (--k) --n, m *= n, r *= k;
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

	// gamma & log-gamma & beta functions

	template <typename float_t> inline float_t tgamma(float_t x)
	{
		return std::tgamma(x);
	}

	template <typename float_t> inline float_t lgamma(float_t x)
	{
		return std::lgamma(x);
	}

	template <typename float_t> inline float_t beta(float_t a, float_t b)
	{
		return tgamma(a + b)/tgamma(a)/tgamma(b);
	}

	// lossless linear & hypotenuse

	template <typename float_t> inline float_t fma(float_t x, float_t y, float_t z)
	{
		return std::fma(x, y, z);
	}

	template <typename float_t> inline float_t hypot(float_t x, float_t y)
	{
		return std::hypot(x, y);
	}

}; // namespace maths

