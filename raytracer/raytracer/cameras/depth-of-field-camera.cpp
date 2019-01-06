#include "depth-of-field-camera.h"
using namespace raytracer;
using namespace std;
using namespace math;
#include "cameras.h"

namespace {
	class DepthOfFieldPerspectiveCamera : public raytracer::cameras::_private_::DisplaceableCamera {
	private:
		vector<Camera>& cameras;
	public:
		DepthOfFieldPerspectiveCamera(const Matrix4x4& transformation, vector<Camera>& cameras) :DisplaceableCamera(transformation), cameras(cameras)
		{

		}

		void enumerate_untransformed_rays(const math::Point2D& p, std::function<void(const math::Ray&)> someKindOfFunctionCall) const
		{
			for each(Camera camera in cameras) {
				camera->enumerate_rays(p, someKindOfFunctionCall);
			}
		}


	};
}

namespace raytracer {
	namespace cameras {
		Camera depth_of_field_perspective(const Point3D & eye, const Point3D & look_at, const Vector3D & up, double distance, double aspect_ratio, double eye_size, Sampler sampler)
		{
			assert(up.is_unit());
			//no need to do anything special here
			//same as perspective without its parameters
			Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);

			//Canonical lookat point, lies on the Z axis, as far way from 0,0,0
			double newDistance = math::distance(eye, look_at);
			Point3D canonPoint = Point3D(0, 0, newDistance);
			vector<Camera> cameras = vector<Camera>();
			Point2D origin = Point2D(-eye_size / 2, -eye_size / 2);
			Rectangle2D eye_area = Rectangle2D(origin, Vector2D(eye_size, 0), Vector2D(0, eye_size));
			auto somePointyBoys = sampler->sample(eye_area);

			for each(auto pointyBoy in somePointyBoys) {
				cameras.push_back(perspective(Point3D(pointyBoy.x(), pointyBoy.y(), 0), canonPoint, Vector3D(0, 1, 0), distance, aspect_ratio));
			}

			return Camera(make_shared<DepthOfFieldPerspectiveCamera>(transformation, cameras));
		}
	}
}
