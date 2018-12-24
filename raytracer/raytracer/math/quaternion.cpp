#include "quaternion.h"
using namespace math;


Quaternion::Quaternion(double a, double b, double c, double d)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

Quaternion math::Quaternion::operator+( Quaternion & q)
{
	auto quat = Quaternion(1, 2, 3, 4);
	auto test = 2 * quat;

	return Quaternion(a + q.a, b + q.b, c + q.c, d + q.d);
}

Quaternion math::Quaternion::operator-( Quaternion & q)
{
	return Quaternion(a- q.a, b -q.b,c-q.c,d-q.d);
}

Quaternion & math::Quaternion::operator-=( Quaternion & q)
{
	this->a -= q.a;
	this->b -= q.b;
	this->c -= q.c;
	this->d -= q.d;
	
	return *this;
}

Quaternion math::Quaternion::operator*(double q)
{

	return Quaternion(a*q, b*q, c*q,d*q);
}

Quaternion math::Quaternion::operator/(double q)
{
	return Quaternion(a/q,b/q,c/q,d/q);
}

Quaternion & math::Quaternion::operator*=(double q)
{
	this->a *= q;
	this->b *= q;
	this->c *= q;
	this->d *= q;

	return *this;
}

Quaternion & math::Quaternion::operator/=(double q)
{
	this->a /= q;
	this->b /= q;
	this->c /= q;
	this->d /= q;

	return *this;
}




Quaternion & math::Quaternion::operator+=( Quaternion & q)
{
	this->a += q.a;
	this->b += q.b;
	this->c += q.c;
	this->d += q.d;

	return *this;
}


Quaternion math::Quaternion::conjugate()
{
	
	return Quaternion(a,-b,-c,-d);
}



Quaternion math::operator*(double q, Quaternion & quat)
{
	return Quaternion(quat.a *q, quat.b*q, quat.c *q, quat.d *q);
}

Quaternion math::Quaternion::operator*(Quaternion & q)
{
	// "easy assignment"
	auto newA = a * q.a - b * q.b - c * q.c - d * q.d;
	auto newB = a * q.b + b * q.a + c * q.d - d * q.c;
	auto newC = a * q.c - b * q.d + c * q.a + d * q.b;
	auto newD = a * q.d + b * q.c - c * q.b + d * q.a;

	return Quaternion(newA, newB, newC, newD);
}

Quaternion math::rotation(Angle theta, const Vector3D & axis)
{
	Quaternion squatternionP = Quaternion(0, axis.x(), axis.y(), axis.z());
	Quaternion squatternionQ = Quaternion(cos(theta / 2), sin(theta / 2)*axis.x(), sin(theta / 2)*axis.y(), sin(theta / 2)*axis.z());
	Quaternion result = squatternionP * squatternionQ;
	
	return result;
}
