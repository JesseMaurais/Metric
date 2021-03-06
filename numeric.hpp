#ifndef numeric_hpp
#define numeric_hpp

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
	
	/// The greatest common divisor d so that m|d and n|d
	template <typename uint_t> uint_t gcd(uint_t m, uint_t n)
	{
		if (n < m) std::swap(m, n);
		while (m) {
		 n %= m;
		 std::swap(m, n);
		}
		return n;
	}

	/// The lowest common multiple, so that gcd(m, n)*lcm(m, n) = m*n
	template <typename uint_t> uint_t lcm(uint_t m, uint_t n)
	{
		return m * (n / gcd(m, n));
	}

	/// The factorial of n, n! = n(n - 1)(n - 2)...(2)(1)
	template <typename uint_t> uint_t fact(uint_t n)
	{
		uint_t m = 1;
		while (n) {
		 m *= n;
		 --n;
		}
		return m;
	}

	/// The semifactorial of k, (2k)!! = (2k)(2k - 2)(2k - 4)...(4)(2)
	template <typename uint_t> uint_t facts(uint_t k)
	{
		// (2k)!! = (k!)(2^k)
		uint_t m = 1, n = 1;
		while (k) {
		 m *= k;
		 --k;
		 n <<= 1;
		}
		return m*n;
	}

	/// Determine whether two number are coprime
	template <typename uint_t> bool coprime(uint_t m, uint_t n)
	{
		return 1 == gcd(m, n);
	}

	/// The primorial of n, n# = product of primes up to n + 1
	template <typename uint_t> uint_t prim(uint_t n)
	{
		if (n < 2) return 1;
		else ++n;
		uint_t p = 2, q = 3;
		while (q < n) {
		 if (coprime(p, q)) p *= q;
		 q += 2;
		}
		return p;
	}

	/// Alternate primorial, p(n)# = product of first n primes
	template <typename uint_t> uint_t primo(uint_t n)
	{
		if (n < 1) return 1;
		else --n;
		uint_t p = 2, q = 3;
		while (n) {
		 if (coprime(p, q)) {
		  p *= q;
		  --n;
		 }
		 q += 2;
		}
		return p;
	}

	/// The k permutations of n elements, n!/(n - k)!
	template <typename uint_t> uint_t perm(uint_t n, uint_t k)
	{
		k = n - k;
		uint_t m = 1;
		while (k) {
		 m *= n;
		 --n;
		 --k;
		}
		return m;
	}

	/// The k combinations of n elements, n!/k!(n - k)!
	template <typename uint_t> uint_t comb(uint_t n, uint_t k)
	{
		k = std::min(k, n - k);
		uint_t m = 1, r = 1;
		while (k) {
		 m *= n;
		 --n;
		 r *= k;
		 --k;
		}
		return m/r;
	}

	/// Euler's number raised to the exponent x
	template <typename num_t> num_t exp(num_t x)
	{
		uintmax_t n = 0;
		num_t s = 0;
		num_t t = 1;
		do {
		 s += t;
		 t *= x;
		 t /= ++n;
		}
		while (t);
		return s;
	}

	/// The number 2 raised to the exponent x
	template <typename num_t> num_t exp2(num_t x)
	{
		return exp(x*ln2);
	}

	/// The natural logarithm of x, so exp(ln(x)) = x
	template <typename num_t> num_t ln(num_t x)
	{
		x = (x - 1)/(x + 1);
		uintmax_t n = 1;
		const num_t xx = x*x;
		num_t r = x;
		num_t s = 0;
		num_t t = r;
		do {
		 s += t;
		 r *= xx;
		 n += 2;
		 t = r/n;
		}
		while (t);
		return 2*s;
	}

	/// The logarithm of x expressed in base b, so pow(b, log(x, b)) = x
	template <typename num_t> num_t log(num_t x, num_t b)
	{
		return ln(x)/ln(b);
	}

	/// The logarithm of x expressed in base 2, so log2(x) = ln(x)/ln2
	template <typename num_t> num_t log2(num_t x)
	{
		return ln(x)/ln2;
	}

	/// The logarithm of x expressed in base 10, so log10(x) = ln(x)/ln10
	template <typename num_t> num_t log10(num_t x)
	{
		return ln(x)/ln10;
	}	
	
	/// The power of x raised to the exponent p
	template <typename num_t> num_t pow(num_t x, num_t p)
	{
		return exp(ln(x)*p);
	}

	/// The square root of x for real x >= 0
	template <typename num_t> num_t sqrt(num_t x)
	{
		return exp(ln(x)/2);
	}

	/// The cube root of x for real x
	template <typename num_t> num_t cbrt(num_t x)
	{
		return exp(ln(x)/3);
	}
	
	/// Extends factorials into the real numbers, tgamma(n) = (n - 1)!
	template <typename num_t> num_t tgamma(num_t x)
	{
		return std::tgamma(x);
	}

	/// The natural logarithm of the gamma function
	template <typename num_t> num_t lgamma(num_t x)
	{
		return std::lgamma(x);
	}

	/// The lower incomplete gamma function
	template <typename num_t> num_t igamma(num_t a, num_t x)
	{
		num_t s = 0;
		num_t t = pow(x, a)/a;
		do {
		 s += t;
		 t *= x;
		 t /= ++a;
		}
		while (t);
		s /= exp(x);
		return s;
	}

	/// The upper incomplete gamma function (lower's complement)
	template <typename num_t> num_t igammac(num_t a, num_t x)
	{
		return tgamma(a) - igamma(a, x);
	}
	
	/// Extends combinations into the field of real numbers
	template <typename num_t> num_t beta(num_t a, num_t b)
	{
		return tgamma(a)*tgamma(b)/tgamma(a + b);
	}
	
	/// The lower incomplete beta function
	template <typename num_t> num_t ibeta(num_t a, num_t b, num_t x)
	{
		num_t n = 1;
		num_t u = 1 - b;
		num_t s = 0;
		num_t t = pow(x, a);
		do {
		 s += t/a;
		 ++a;
		 t *= u;
		 ++u;
		 t /= n;
		 ++n;
		 t *= x;
		}
		while (t);
		return s;
	}

	/// The upper incomplete beta function (lower's complement)
	template <typename num_t> num_t ibetac(num_t a, num_t b, num_t x)
	{
		return beta(a, b) - ibeta(a, b, x);
	}

	/// The Dirichlet eta function for real x > 0
	template <typename num_t> num_t eta(num_t x, num_t eps=1e-9)
	{
		bool a = false;
		uintmax_t n = 1;
		num_t s = 0;
		num_t t = 1;
		do {
		 a = !a;
		 a ? s += t : s -= t;
		 t = pow<num_t>(++n, -x);
		}
		while (eps < t);
		return s;
	}

	/// The Reimann zeta function for real x > 1, defined as a discrete sum
	template <typename num_t> num_t zeta(num_t x, num_t eps=1e-9)
	{
		uintmax_t n = 1;
		num_t s = 0;
		num_t t = 1;
		do {
		 s += t;
		 t = pow<num_t>(++n, -x);
		}
		while (eps < t);
		return s;
	}

	/// The Reimann zeta function for real x > 1, using Euler's product
	template <typename num_t> num_t zeta_p(num_t x, num_t eps=1e-9)
	{
		uintmax_t p = 2, q = 3;
		num_t t = pow<num_t>(p, -x);
		num_t s = 1 - t;
		do {
		 if (coprime(p, q)) {
		  t = pow<num_t>(q, -x);
		  s *= 1 - t;
		  p *= q;
		 }
		 q += 2;
		}
		while (eps < t);
		return 1/s;
	}

	/// The Reimann zeta function for real x > 1, Dirichlet's eta identity
	template <typename num_t> num_t zeta_e(num_t x, num_t eps=1e-9)
	{
		// Better convergence with eta identity
		return eta(x, eps)/(1 - exp2(1 - x));
	}

	/// The Gaussian hypergeometric function
	template <typename num_t> num_t hyper(num_t a, num_t b, num_t c, num_t x)
	{
		uintmax_t n = 1;
		num_t s = 1;
		num_t t = x*a*b/c;
		do {
		 s += t;
		 t *= ++a;
		 t /= ++c;
		 t *= ++b;
		 t /= ++n;
		 t *= x;
		}
		while (t);
		return s;
	}

	/// Kummer's confluent hypergeometric function
	template <typename num_t> num_t kummer(num_t a, num_t c, num_t x)
	{
		uintmax_t n = 1;
		num_t s = 1;
		num_t t = x*a/c;
		do {
		 s += t;
		 t *= ++a;
		 t /= ++c;
		 t *= x;
		 t /= ++n;
		}
		while (t);
		return s;
	}

	/// Measures the complement of the error function (the tails)
	template <typename num_t> num_t erfc(num_t x)
	{
		constexpr auto isqrtpi = sqrt2/sqrt2pi;
		return igammac<num_t>(0.5, x*x)*isqrtpi;
	}

	/// Measures the area under the bell curve for errors of size x
	template <typename num_t> num_t erf(num_t x)
	{
		return 1.0 - erfc(x);
	}

	/// In a right triangle, the leg opposite an angle over the hypotenuse
	template <typename num_t> num_t sin(num_t x)
	{
		uintmax_t n = 1;
		const num_t xx = -x*x;
		num_t s = 0;
		num_t t = x;
		do {
		 s += t;
		 t *= xx;
		 t /= ++n;
		 t /= ++n;
		}
		while (t);
		return s;
	}

	/// In a right triangle, the leg adjacent an angle over the hypotenuse
	template <typename num_t> num_t cos(num_t x)
	{
		uintmax_t n = 0;
		const num_t xx = -x*x;
		num_t s = 0;
		num_t t = 1;
		do {
		 s += t;
		 t *= xx;
		 t /= ++n;
		 t /= ++n;
		}
		while (t);
		return s;
	}

	/// Slope of tangent line on a circle at angle x from the origin
	template <typename num_t> num_t tan(num_t x)
	{
		return sin(x)/cos(x);
	}

	/// Arcsine returns the angle of a given sine
	template <typename num_t> num_t asin(num_t x)
	{
		const num_t a = 0.5, b = 0.5, c = 1.5;
		return x*hyper(a, b, c, x*x);
	}

	/// Arccosine returns the angle of a given cosine
	template <typename num_t> num_t acos(num_t x)
	{
		return pi_2 - asin(x);
	}

	/// Arctangent returns the angle of a given tangent
	template <typename num_t> num_t atan(num_t x)
	{
		const num_t a = 0.5, b = 1.0, c = 1.5;
		return x*hyper(a, b, c, -x*x);
	}

	/// Deduces the quadrant correct angle of a given sine and cosine
	template <typename num_t> num_t atan2(num_t y, num_t x)
	{
		if (x > 0) return atan(y/x);
		if (x < 0) return atan(y/x) + (y < 0 ? -pi : +pi);
		if (y > 0) return +pi_2;
		if (y < 0) return -pi_2;
		return NAN;
	}

	/// Rise of the point on an equilateral hyperbola at half of angle x
	template <typename num_t> num_t sinh(num_t x)
	{
		uintmax_t n = 1;
		const num_t xx = x*x;
		num_t s = 0;
		num_t t = x;
		do {
		 s += t;
		 t *= xx;
		 t /= ++n;
		 t /= ++n;
		}
		while (t);
		return s;
	}

	/// Run of the point on equilateral hyperbola at half of angle x
	template <typename num_t> num_t cosh(num_t x)
	{
		uintmax_t n = 0;
		const num_t xx = x*x;
		num_t s = 0;
		num_t t = 1;
		do {
		 s += t;
		 t *= xx;
		 t /= ++n;
		 t /= ++n;
		}
		while (t);
		return s;
	}

	/// Slope of a line meeting a hyperbola at half of angle x from origin
	template <typename num_t> num_t tanh(num_t x)
	{
		return sinh(x)/cosh(x);
	}

	/// The angle with a hyperbolic sine of x
	template <typename num_t> num_t asinh(num_t x)
	{
		return ln(x + sqrt(x*x + 1));
	}

	/// The angle with a hyperbolic cosine of x
	template <typename num_t> num_t acosh(num_t x)
	{
		return ln(x + sqrt(x*x - 1));
	}

	/// The angle with a hyperbolic tangent of x
	template <typename num_t> num_t atanh(num_t x)
	{
		const num_t a = 0.5, b = 1.0, c = 1.5;
		return x*hyper(a, b, c, x*x);
	}
	
}; // namespace

#endif // file
	
