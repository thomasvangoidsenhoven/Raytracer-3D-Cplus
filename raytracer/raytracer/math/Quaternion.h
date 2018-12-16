#pragma once
#include "math/vector.h"
#include "math/point.h"

namespace math {
	class Quaternion
	{
	public:
		Quaternion(double a, double b, double c, double d);
		Point3D rotate(const Point3D& p);
		void rotation(Angle theta, const Vector3D& axis);
		
	};

}


