#include "fisheye-camera.h"
using namespace raytracer;
using namespace std;



Camera raytracer::cameras::fisheye(const math::Point3D & eye, const math::Point3D & look_at, const math::Vector3D & up, Angle & horizontalAngle, Angle & verticalAngle)
{	
	//no need to do anything special here
	//same as perspective without its parameters
	Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);
	return Camera(make_shared<_private_::FisheyeCamera>(transformation,horizontalAngle,verticalAngle));
}

void raytracer::cameras::_private_::FisheyeCamera::enumerate_untransformed_rays(const math::Point2D &, std::function<void(const math::Ray&)>) const
{
}
