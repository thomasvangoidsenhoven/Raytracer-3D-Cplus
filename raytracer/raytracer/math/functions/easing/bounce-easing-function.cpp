
#include "bounce-easing-function.h"
#include "math/interval.h"
#include <assert.h>

#include "math/angle.h"
using namespace math;
using namespace math::functions;

math::functions::EasingFunction math::functions::easing::bounce(int bounces, int absorption)
{

	std::function<double(double)> lambda = [=](double t) {
		assert(interval(0.0, 1.0).contains(t));

		math::Angle angle = Angle().degrees(180);
		//absolute waarde van teller nemen anders vallen ze door de grond
		auto teller = abs(cos((2 * bounces - 1) * angle / 2 * t));
		auto noemer = pow(t + 1, absorption);
		auto functionF = teller / noemer;
		return (1 - functionF);

		//return t;
	};

	return from_lambda(lambda);
}
