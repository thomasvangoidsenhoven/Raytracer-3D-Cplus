#include "math/functions/checkered-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;

Function<bool(const Point2D&)> math::functions::checkered2d(double thickness)
{
	std::function<bool(const Point2D&)> function = [thickness](const Point2D& p)
	{
		auto x = p.x();
		auto y = p.y();

		auto xx = (int)std::floor(x / thickness);
		auto yy = (int)std::floor(y / thickness);
		
		auto truthyx = std::abs(xx % 2);
		auto truthyy = std::abs(yy % 2);

		return truthyx == truthyy;

	};

	return from_lambda<bool, const Point2D&>(function);
}