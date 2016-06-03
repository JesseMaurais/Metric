#include "maths.hpp"

namespace stats
{
	// normal distribution

	template <typename float_t> class norm
	{
		float_t mu, sigma, unit;
		
	 public:
	 
	 	norm(float_t mu=0, float_t sigma=1)
	 	{
	 	 	unit = maths::sqrt2pi*sigma;
	 	 	this->sigma = sigma;
	 		this->mu = mu;
	 	}
	 	
	 	float_t pdf(float_t x)
	 	{
	 		float_t z = (x - mu)/sigma;
	 		return maths::exp(-z*z/2)/unit;
	 	}
	 	
	 	float_t cdf(float_t x)
	 	{
	 		float_t z = (x - mu)/sigma;
	 		return (1 + maths::erf(z/maths::sqrt2))/2/sigma;
	 	}
	};

	template <typename float_t> float_t dnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		return norm<float_t>(mu, sigma).pdf(x);
	}

	template <typename float_t> float_t pnorm(float_t x, float_t mu=0, float_t sigma=1)
	{
		return norm<float_t>(mu, sigma).cdf(x);
	}

}; // namespace stats

