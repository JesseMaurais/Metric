#ifndef Metric_maths
#define Metric_maths

/**
 * The mathematical functions found in the C++ standard header, cmath, are
 * overloaded for each argument type, so they have to be rewritten for all
 * new types. This is how they're implemented for the complex number class
 * and valarrays; using overloads. Here we implement the same functions as
 * templates so each function has the same definition for numbers of every
 * argument type. They should work for any objects for which the operators
 * used in the functions are also supported. For many of them this will be
 * no more than the prefix operators and compound assignment operators. So
 * far they have been tested on POD types.
 *
 * There is no error checking on the validity of the argument. Provided an
 * argument has valid input (values are in range) the algorithms will work
 * as expected. Inputs out of range have undefined behaviour and will most
 * likely result in an infinite loop.
 *
 * I wrote this as a test for myself on numeric computing, to discover how
 * well I could do relative to existing software. The aim is to rewrite as
 * many of the standard library math functions as I can, plus other useful
 * functions that are not currently part of the standard. For example, the
 * incomplete gamma, beta, and zeta functions. Some simpler functions like
 * gcd, lcm, and combinatorial functions are also here.
 *
 * I do not claim that this is the best way to implement them. There might
 * be faster methods, though I tried to make them fast. More accurate ways
 * might also exist. And no doubt there are "safer" methods out there. But
 * they seem to work well enough and I hope they serve as simple reference
 * for how such functions might be implemented.
 */

#include <algorithm>
#include <utility>
#include <cmath>

namespace numeric
{
	// These are not always defined in cmath nor with 128 bit precision
	constexpr auto e       = 2.718281828459045235360287471352662498L;
	constexpr auto ln2     = 0.693147180559945309417232121458176568L;
	constexpr auto ln10    = 2.302585092994045684017991454684364208L;
	constexpr auto log2e   = 1.442695040888963407359924681001892137L;
	constexpr auto log10e  = 0.434294481903251827651128918916605082L;
	constexpr auto pi      = 3.141592653589793238462643383279502884L;
	constexpr auto pi_2    = 1.570796326794896619231321691639751442L;
	constexpr auto pi_4    = 0.785398163397448309615660845819875721L;
	constexpr auto pi2_6   = 1.644934066848226436472415166646025189L;
	constexpr auto sqrt2pi = 2.506628274631000502415765284811045253L;
	constexpr auto sqrt2   = 1.414213562373095048801688724209698079L;
	constexpr auto ngamma  = 0.577215664901532860606512090082402431L;
	
	/// The greatest common divisor; greatest d so that m|d and n|d
	template <typename int_t> int_t gcd(int_t m, int_t n)
	{
		if (n < m) std::swap(m, n);
		int_t r;
		while (m) r = n % m, n = m, m = r;
		return n;
	}

	/// The lowest common multiple, so that gcd(m, n)*lcm(m, n) = m*n
	template <typename int_t> int_t lcm(int_t m, int_t n)
	{
		return m * (n / gcd(m, n));
	}

	/// The factorial of n, n! = n(n - 1)(n - 2)...(2)(1)
	template <typename int_t> int_t fact(int_t n)
	{
		int_t m = 1;
		while (n) m *= n--;
		return m;
	}

	/// The semifactorial of k, (2k)!! = (2k)(2k - 2)(2k - 4)...(4)(2)
	template <typename int_t> int_t facts(int_t k)
	{
		// (2k)!! = (k!)(2^k)
		int_t m = 1, n = 1;
		while (k) m *= k--, n <<= 1;
		return m*n;
	}

	/// The primorial of n, n# = product of primes up to n + 1
	template <typename int_t> int_t prim(int_t n)
	{
		if (n < 2) return 1;
		else ++n;
		int_t p = 2, q = 3;
		while (q < n) {
		 if (gcd(p, q) == 1) p *= q;
		 q += 2;
		};
		return p;
	}

	/// Alternate primorial, p(n)# = product of first n primes
	template <typename int_t> int_t primo(int_t n)
	{
		if (n < 1) return 1;
		else --n;
		int_t p = 2, q = 3;
		while (n) {
		 if (gcd(p, q) == 1) {
		  p *= q;
		  --n;
		 }
		 q += 2;
		}
		return p;
	}

	/// The k permutations of n elements, n!/(n - k)!
	template <typename int_t> int_t perm(int_t n, int_t k)
	{
		k = n - k;
		int_t m = 1;
		while (k--) m *= n--;
		return m;
	}

	/// The k combinations of n elements, n!/k!(n - k)!
	template <typename int_t> int_t comb(int_t n, int_t k)
	{
		k = std::min(k, n - k);
		int_t m = 1, r = 1;
		while (k) m *= n--, r *= k--;
		return m/r;
	}
	
	/// Extends factorials into the real numbers, tgamma(n) = (n - 1)!
	template <typename float_t> float_t tgamma(float_t x)
	{
		return std::tgamma(x);
	}

	/// The natural logarithm of the gamma function
	template <typename float_t> float_t lgamma(float_t x)
	{
		return std::lgamma(x);
	}

	/// The lower incomplete gamma function
	template <typename float_t> float_t igamma(float_t a, float_t x)
	{
		float_t s = 0, t = std::pow(x, a)/a;
		do s += t, t *= x, t /= ++a;
		while (t);
		s /= std::exp(x);
		return s;
	}

	/// The upper incomplete gamma function (lower's complement)
	template <typename float_t> float_t igammac(float_t a, float_t x)
	{
		return std::tgamma(a) - igamma(a, x);
	}
	
	/// Extends combinations into the field of real numbers
	template <typename float_t> float_t beta(float_t a, float_t b)
	{
		return std::tgamma(a)*std::tgamma(b)/std::tgamma(a + b);
	}
	
	/// The lower incomplete beta function
	template <typename float_t> float_t ibeta(float_t a, float_t b, float_t x)
	{
		float_t n = 1, u = 1 - b;
		float_t s = 0, t = std::pow(x, a);
		do s += t/a++, t *= u++, t /= n++, t *= x;
		while (t);
		return s;
	}

	/// The upper incomplete beta function (lower's complement)
	template <typename float_t> float_t ibetac(float_t a, float_t b, float_t x)
	{
		return beta(a, b) - ibeta(a, b, x);
	}

	/// The Dirichlet eta function for real x > 0
	template <typename float_t> float_t eta(float_t x, float_t eps=1e-9)
	{
		bool a = false;
		uintmax_t n = 1;
		float_t s = 0, t = 1;
		do (a = !a) ? s += t : s -= t, t = std::pow(++n, -x);
		while (eps < t);
		return s;
	}

	/// The Reimann zeta function for real x > 1, defined as a discrete sum
	template <typename float_t> float_t zeta(float_t x, float_t eps=1e-9)
	{
		uintmax_t n = 1;
		float_t s = 0, t = 1;
		do s += t, t = std::pow(++n, -x);
		while (eps < t);
		return s;
	}

	/// The Reimann zeta function for real x > 1, using Euler's product
	template <typename float_t> float_t zeta_p(float_t x, float_t eps=1e-9)
	{
		uintmax_t p = 2, q = 3;
		float_t t = std::pow(p, -x);
		float_t s = 1 - t;
		do {
		 if (gcd(p, q) == 1) {
		  t = std::pow(q, -x);
		  s *= 1 - t;
		  p *= q;
		 }
		 q += 2;
		}
		while (eps < t);
		return 1/s;
	}

	/// The Reimann zeta function for real x > 1, Dirichlet's eta identity
	template <typename float_t> float_t zeta_e(float_t x, float_t eps=1e-9)
	{
		// Better convergence with eta identity
		return eta(x, eps)/(1 - std::exp2(1 - x));
	}

	/// The Gaussian hypergeometric function
	template <typename float_t> float_t hyper(float_t a, float_t b, float_t c, float_t x)
	{
		uintmax_t n = 1;
		float_t s = 1, t = x*a*b/c;
		do s += t, t *= ++a, t /= ++c, t *= ++b, t /= ++n, t *= x;
		while (t);
		return s;
	}

	/// Kummer's confluent hypergeometric function
	template <typename float_t> float_t kummer(float_t a, float_t c, float_t x)
	{
		uintmax_t n = 1;
		float_t s = 1, t = x*a/c;
		do s += t, t *= ++a, t /= ++c, t *= x, t /= ++n;
		while (t);
		return s;
	}

	/// Measures the complement of the error function (the tails)
	template <typename float_t> float_t erfc(float_t x)
	{
		constexpr auto isqrtpi = sqrt2/sqrt2pi;
		return igammac<float_t>(0.5, x*x)*isqrtpi;
	}

	/// Measures the area under the bell curve for errors of size x
	template <typename float_t> float_t erf(float_t x)
	{
		return 1.0 - erfc(x);
	}

	/// Euler's number raised to the exponent x
	template <typename float_t> float_t exp(float_t x)
	{
		uintmax_t n = 0;
		float_t s = 0, t = 1;
		do s += t, t *= x, t /= ++n;
		while (t);
		return s;
	}

	/// The number 2 raised to the exponent x
	template <typename float_t> float_t exp2(float_t x)
	{
		return exp(x*ln2);
	}

	/// The natural logarithm of x, so exp(ln(x)) = x
	template <typename float_t> float_t ln(float_t x)
	{
		x = (x - 1)/(x + 1);
		uintmax_t n = 1;
		const float_t xx = x*x;
		float_t r = x, s = 0, t = r;
		do s += t, r *= xx, n += 2, t = r/n;
		while (t);
		return 2*s;
	}

	/// The logarithm of x expressed in base b, so pow(b, log(x, b)) = x
	template <typename float_t> float_t log(float_t x, float_t b)
	{
		return ln(x)/ln(b);
	}

	/// The logarithm of x expressed in base 2, so log2(x) = ln(x)/ln2
	template <typename float_t> float_t log2(float_t x)
	{
		return ln(x)/ln2;
	}

	/// The logarithm of x expressed in base 10, so log10(x) = ln(x)/ln10
	template <typename float_t> float_t log10(float_t x)
	{
		return ln(x)/ln10;
	}	
	
	/// The power of x raised to the exponent p
	template <typename float_t> float_t pow(float_t x, float_t p)
	{
		return exp(ln(x)*p);
	}

	/// The square root of x for real x >= 0
	template <typename float_t> float_t sqrt(float_t x)
	{
		return exp(ln(x)/2);
	}

	/// The cube root of x for real x
	template <typename float_t> float_t cbrt(float_t x)
	{
		return exp(ln(x)/3);
	}

	/// In a right triangle, the leg opposite an angle over the hypotenuse
	template <typename float_t> float_t sin(float_t x)
	{
		uintmax_t n = 1;
		const float_t xx = -x*x;
		float_t s = 0, t = x;
		do s += t, t *= xx, t /= ++n, t /= ++n;
		while (t);
		return s;
	}

	/// In a right triangle, the leg adjacent an angle over the hypotenuse
	template <typename float_t> float_t cos(float_t x)
	{
		uintmax_t n = 0;
		const float_t xx = -x*x;
		float_t s = 0, t = 1;
		do s += t, t *= xx, t /= ++n, t /= ++n;
		while (t);
		return s;
	}

	/// Slope of tangent line on a circle at angle x from the origin
	template <typename float_t> float_t tan(float_t x)
	{
		return sin(x)/cos(x);
	}

	/// Arcsine returns the angle of a given sine
	template <typename float_t> float_t asin(float_t x)
	{
		return x*hyper<float_t>(0.5, 0.5, 1.5, x*x);
	}

	/// Arccosine returns the angle of a given cosine
	template <typename float_t> float_t acos(float_t x)
	{
		return pi_2 - asin(x);
	}

	/// Arctangent returns the angle of a given tangent
	template <typename float_t> float_t atan(float_t x)
	{
		return x*hyper<float_t>(0.5, 1.0, 1.5, -x*x);
	}

	/// Deduces the quadrant correct angle of a given sine and cosine
	template <typename float_t> float_t atan2(float_t y, float_t x)
	{
		if (x > 0) return atan(y/x);
		if (x < 0) return atan(y/x) + (y < 0 ? -pi : +pi);
		if (y > 0) return +pi_2;
		if (y < 0) return -pi_2;
		return NAN;
	}

	/// Rise of the point on an equilateral hyperbola at half of angle x
	template <typename float_t> float_t sinh(float_t x)
	{
		uintmax_t n = 1;
		const float_t xx = x*x;
		float_t s = 0, t = x;
		do s += t, t *= xx, t /= ++n, t /= ++n;
		while (t);
		return s;
	}

	/// Run of the point on equilateral hyperbola at half of angle x
	template <typename float_t> float_t cosh(float_t x)
	{
		uintmax_t n = 0;
		const float_t xx = x*x;
		float_t s = 0, t = 1;
		do s += t, t *= xx, t /= ++n, t /= ++n;
		while (t);
		return s;
	}

	/// Slope of a line meeting a hyperbola at half of angle x from origin
	template <typename float_t> float_t tanh(float_t x)
	{
		return sinh(x)/cosh(x);
	}

	/// The angle with a hyperbolic sine of x
	template <typename float_t> float_t asinh(float_t x)
	{
		return ln(x + sqrt(x*x + 1));
	}

	/// The angle with a hyperbolic cosine of x
	template <typename float_t> float_t acosh(float_t x)
	{
		return ln(x + sqrt(x*x - 1));
	}

	/// The angle with a hyperbolic tangent of x
	template <typename float_t> float_t atanh(float_t x)
	{
		return x*hyper<float_t>(0.5, 1.0, 1.5, x*x);
	}
	
}; // namespace maths

#endif // Metric_maths
	
