#pragma once
#pragma once
#include "math/vector.h"
#include "math/point.h"

namespace math
{
	class Quaternion
	{
	private:

	public:
		double a, b, c, d;
		Quaternion(double a, double b, double c, double d);
		Quaternion conjugate();
		Quaternion operator * ( Quaternion& q);
		Quaternion operator + ( Quaternion& q);
		Quaternion operator - ( Quaternion& q);
		Quaternion& operator += ( Quaternion& q);
		Quaternion& operator -= ( Quaternion& q);
		Quaternion operator * (double q);
		Quaternion operator / (double q);
		Quaternion& operator *= (double q);
		Quaternion& operator /= (double q);
		
		

	};
	// overloading both sides requires it to be put outside the class definition
	Quaternion operator * (double q, Quaternion& quat);
	Quaternion rotation(Angle theta, const Vector3D& axis);
}