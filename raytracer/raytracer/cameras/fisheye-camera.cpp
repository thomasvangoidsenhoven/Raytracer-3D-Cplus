#include "fisheye-camera.h"
#include "math/interval-mapper.h"
using namespace raytracer;
using namespace std;


Camera raytracer::cameras::fisheye(const math::Point3D & eye, const math::Point3D & look_at, const math::Vector3D & up, Angle & horizontalAngle, Angle & verticalAngle)
{	
	//no need to do anything special here
	//same as perspective without its parameters
	Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);
	return Camera(make_shared<_private_::FisheyeCamera>(transformation,horizontalAngle,verticalAngle));
}

void raytracer::cameras::_private_::FisheyeCamera::enumerate_untransformed_rays(const math::Point2D& p, std::function<void(const math::Ray&)> someKindOfFunctionCall) const
{
	//divide by 2 so we dont dubbel our range
	//90 to center view on the horizontal plane
	auto horizontalRange = interval(-horizontalAngle.degrees()/2-90, horizontalAngle.degrees()/2-90);
	auto verticalRange = interval(-verticalAngle.degrees() / 2, verticalAngle.degrees() / 2);
	auto defaultInterval = interval(0.0,1.0);
	IntervalMapper<double, double> horIntervalMap = IntervalMapper<double, double>(defaultInterval, horizontalRange);
	IntervalMapper<double, double> verIntervalMap = IntervalMapper<double, double>(defaultInterval, verticalRange);

	Angle a = Angle::degrees(horIntervalMap[p.x()]);
	Angle a2 = Angle::degrees(verIntervalMap[p.y()]);

	//first param is radius, hori, then elevation
	auto onespheryboy = Point3D::spherical(100, a, a2);
	Ray ray = Ray(Point3D(0, 0, 0), onespheryboy);
	someKindOfFunctionCall(ray);


}
