#include "camera.h"
#include "samplers/samplers.h"
using namespace math;




namespace raytracer {
	namespace cameras {
		Camera depth_of_field_perspective(const Point3D& eye, const Point3D& look_at, const Vector3D& up, double distance, double aspect_ratio, double eye_size, Sampler sampler);
	}
}