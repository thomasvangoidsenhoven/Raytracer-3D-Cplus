#include "quadratic-function.h"

using namespace math::functions;
#include <iostream>

EasingFunction math::functions::easing::quadratic_in()
{
	std::function<double(double)> lambda = [=](double t) {
		return t*t;
	};

	return from_lambda(lambda);
}

EasingFunction math::functions::easing::quadratic_out()
{
	std::function<double(double)> lambda = [=](double t) {
		return 2*t-(t*t);
	};

	return from_lambda(lambda);
}

EasingFunction math::functions::easing::quadratic_in_out()
{
	
	std::function<double(double)> lambda = [=](double t) {
		//increase speed pre half
		//decrease speed after half
		
		if (t <= 0.5) {
			return (t * t)*2;
		}
		

		return -1 + (4 - 2 * t) * t;
		
		

	};

	return from_lambda(lambda);
}
