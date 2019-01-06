#pragma once


#include "lights/lights.h"
using namespace math;
using namespace imaging;

namespace raytracer
{
	namespace lights
	{
		LightSource spot(const Point3D& start, const Point3D& finish, const Angle& angle, const Color& color);
	}
}
