#include "elastic-easing-function.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace math::functions;
# define M_PI           3.14159265358979323846 

math::functions::EasingFunction math::functions::easing::elastic(int oscilations, int energyLoss)
{
	std::function<double(double)> lambda = [=](double t) {
		assert(interval(0.0, 1.0).contains(t));

		double result = -t* energyLoss;
		result = exp(result); // exponential value of
		double tussenstap = sin(M_PI*oscilations*t);
		result *= sin(tussenstap);
		return result;

		//return t;
	};

	return from_lambda(lambda);
}
