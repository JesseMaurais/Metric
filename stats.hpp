#include "maths.hpp"

namespace stats
{
	// Normal distribution

	template <typename float_t> inline
	float_t dnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		float_t z = (x -  mu)/sigma;
		return maths::exp(-z*z/2)/maths::sqrt2pi/sigma;
	}

	template <typename float_t> inline
	float_t pnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		float_t z = (x - mu)/sigma;
		return (1 + maths::erf(z/maths::sqrt2))/2/sigma;
	}

	// Gamma distribution

	template <typename float_t> inline
	float_t dgamma(float_t x, float_t a, float_t b)
	{
		float_t unity = maths::pow(b, a)/maths::tgamma(a);
		return maths::pow(x, a - 1)*maths::exp(-x*b)*unity;
	}

	template <typename float_t> inline
	float_t pgamma(float_t x, float_t a, float_t b)
	{
		return maths::igamma(a, x*b)/maths::tgamma(a);
	}

	// Exponential distribution

	template <typename float_t> inline
	float_t dexp(float_t x, float_t mu=1)
	{
		return maths::exp(-x/mu)/mu;
	}

	template <typename float_t> inline
	float_t pexp(float_t x, float_t mu=1)
	{
		return 1 - maths::exp(-x/mu);
	}

	// Chi-squared distribution

	template <typename float_t> inline
	float_t dchisq(float_t x, float_t nu=1)
	{
		return dgamma(x, nu/2, 0.5);
	}

	template <typename float_t> inline
	float_t pchisq(float_t x, float_t nu=1)
	{
		return pgamma(x, nu/2, 0.5);
	}

	// Beta distribution

	template <typename float_t> inline
	float_t dbeta(float_t x, float_t a, float_t b)
	{
		return maths::pow(x, a-1)*maths::pow(1-x, b-1)/maths::beta(a,b);
	}

	template <typename float_t> inline
	float_t pbeta(float_t x, float_t a, float_t b)
	{
		return maths::ibeta(a, b, x)/maths::beta(a, b);
	}

	// Fisher distribution

	template <typename float_t> inline
	float_t df(float_t x, float_t num, float_t den)
	{
		float_t y = x*num/den;
		float_t p = maths::pow(y, num/2);
		float_t q = maths::pow(1 + y, -(num + den)/2);
		return p*q/maths::beta(num/2, den/2)/(x?x:1);
	}

	template <typename float_t> inline
	float_t pf(float_t x, float_t num, float_t den)
	{
		return 1 - pbeta(num/(den + num*x), den/2, num/2);
	}

}; // namespace stats

