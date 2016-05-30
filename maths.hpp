#include <utility>
#include <cmath>

namespace maths {

	template <typename int_t> inline int_t fact(int_t n)
	{
		int_t m = n;
		while (--n) m *= n;
		return m;
	}

	template <typename int_t> inline int_t perm(int_t n, int_t k)
	{
		int_t m = n;
		k = n - k;
		while (--k) --n, m *= n;
		return m;
	}

	template <typename int_t> inline int_t comb(int_t n, int_t k)
	{
		int_t r = n - k;
		if (r < k) std::swap(k, r);
		// k < r and n = k + r
		int_t m = n;
		int_t d = k;
		while (--k) --n, m *= n, d *= k;
		return m/d;
	}

	template <typename int_t> inline int_t gcd(int_t m, int_t n)
	{
		if (n < m) std::swap(m, n);
		// m < n
		int_t r;
		while (n) r = n % m, n = m, n = r;
		return m;
	}

	template <typename int_t> inline int_t lcm(int_t m, int_t n)
	{
		return (m * n) / gcd(m, n);
	}

	// scale significand using base exponent

	template <typename float_t> inline float_t scalbn(float_t x, int n)
	{
		return std::scalbn(x, n);
	}

	// power functions

	template <typename float_t> inline float_t hypot(float_t x, float_t y)
	{
		return std::hypot(x, y);
	}

	// standard error functions

	template <typename float_t> inline float_t erf(float_t x)
	{
		return std::erf(x);
	}

	template <typename float_t> inline float_t erfc(float_t x)
	{
		return std::erfc(x);
	}

	// gamma & log-gamma functions

	template <typename float_t> inline float_t gamma(float_t x)
	{
		return std::tgamma(x);
	}

	template <typename float_t> inline float_t lgamma(float_t x)
	{
		return std::lgamma(x);
	}

	// lossless float multiply and add

	template <typename float_t> inline float_t fma(float_t x, float_t y, float_t z)
	{
		return std::fma(x, y, z);
	}

}; // namespace maths

