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
		return maths::pow(x*b, a)*maths::exp(-x*b)/maths::tgamma(a)/x;
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
		return dgamma(x, 2, nu/2);
	}

	template <typename float_t> inline
	float_t pchisq(float_t x, float_t nu=1)
	{
		return pgamma(x, 2, nu/2);
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
		return maths::ibeta(x, a, b)/maths::beta(a, b);
	}

	// Fisher distribution

	template <typename float_t> inline
	float_t pf(float_t x, float_t dfnum, float_t dfden)
	{
		return pbeta(dfden/(dfden + dfnum*x), dfden/2, dfnum/2);
	}

}; // namespace stats

