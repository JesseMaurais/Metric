#include "maths.hpp"

namespace stats
{
	// normal distribution

	template <typename float_t>
	float_t dnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		float_t z = (x -  mu)/sigma;
		return maths::exp(-z*z/2)/maths::sqrt2pi/sigma;
	}

	template <typename float_t>
	float_t pnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		float_t z = (x - mu)/sigma;
		return (1 + maths::erf(z/maths::sqrt2))/2/sigma;
	}

	// gamma distribution

	template <typename float_t>
	float_t dgamma(float_t x, float_t a, float_t b)
	{
		return maths::pow(x*b, a)*maths::exp(-x*b)/maths::tgamma(a)/x;
	}

	template <typename float_t>
	float_t pgamma(float_t x, float_t a, float_t b)
	{
		return maths::igamma(a, x*b)/maths::tgamma(a);
	}

}; // namespace stats

