#ifndef Metric_stats
#define Metric_stats

/**
 * This is an R-like interface for calculating probabilities and densities/mass
 * for the common random variable distributions. Like numeric.hpp this is more
 * to test myself at numerical and statistical computing than it is intended
 * for a high-performance computing library.
 */

#include "numeric.hpp"

namespace statistics
{
	// Normal distribution

	template <typename float_t> float_t dnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		float_t z = (x -  mu)/sigma;
		return numeric::exp(-z*z/2)/numeric::sqrt2pi/sigma;
	}

	template <typename float_t> float_t pnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		float_t z = (x - mu)/sigma;
		return (1 + numeric::erf(z/numeric::sqrt2))/2/sigma;
	}

	// Gamma distribution

	template <typename float_t> float_t dgamma(float_t x, float_t a, float_t b)
	{
		float_t unity = numeric::pow(b, a)/numeric::tgamma(a);
		return numeric::pow(x, a - 1)*numeric::exp(-x*b)*unity;
	}

	template <typename float_t> float_t pgamma(float_t x, float_t a, float_t b)
	{
		return numeric::igamma(a, x*b)/numeric::tgamma(a);
	}

	// Exponential distribution

	template <typename float_t> float_t dexp(float_t x, float_t mu=1)
	{
		return numeric::exp(-x/mu)/mu;
	}

	template <typename float_t> float_t pexp(float_t x, float_t mu=1)
	{
		return 1 - numeric::exp(-x/mu);
	}

	// Chi-squared distribution

	template <typename float_t> float_t dchisq(float_t x, float_t nu=1)
	{
		return dgamma(x, nu/2, 0.5);
	}

	template <typename float_t> float_t pchisq(float_t x, float_t nu=1)
	{
		return pgamma(x, nu/2, 0.5);
	}

	// Beta distribution

	template <typename float_t> float_t dbeta(float_t x, float_t a, float_t b)
	{
		return numeric::pow(x, a-1)*numeric::pow(1-x, b-1)/numeric::beta(a,b);
	}

	template <typename float_t> float_t pbeta(float_t x, float_t a, float_t b)
	{
		return numeric::ibeta(a, b, x)/numeric::beta(a, b);
	}

	// Fisher distribution

	template <typename float_t> float_t df(float_t x, float_t num, float_t den)
	{
		float_t y = x*num/den;
		float_t p = numeric::pow(y, num/2);
		float_t q = numeric::pow(1 + y, -(num + den)/2);
		return p*q/numeric::beta(num/2, den/2)/(x?x:1);
	}

	template <typename float_t> float_t pf(float_t x, float_t num, float_t den)
	{
		return 1 - pbeta(num/(den + num*x), den/2, num/2);
	}

}; // namespace statistics

#endif // Metric_statistics

