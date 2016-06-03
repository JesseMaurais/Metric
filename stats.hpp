#include "maths.hpp"

namespace stats
{
	template <typename float_t>
	float_t dnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		float_t z = (x - mu)/sigma;
		const float_t SQRT2PI = maths::sqrt(M_PI*2); // not in cmath
		return maths::exp(-z*z/2)/SQRT2PI/sigma;
	}

	template <typename float_t>
	float_t pnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		float_t z = (x - mu)/sigma;
		return (1 + maths::erf(z/M_SQRT2))/2/sigma;
	}

}; // namespace stats

