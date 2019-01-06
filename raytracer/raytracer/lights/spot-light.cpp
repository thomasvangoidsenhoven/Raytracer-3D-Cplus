#include "lights/spot-light.h"
using namespace math;
using namespace raytracer;
using namespace imaging;
namespace
{
	
	class SpotLight : public lights::_private_::PointLightImplementation
	{
		private:
			Point3D finish;
			Angle angle;
			Color color;
			
			
		public:
			SpotLight(const Point3D& start, const Point3D& finish, const Angle& angle, const Color& color)
				: PointLightImplementation(start), finish(finish), angle(angle), color(color) { }

		protected:
			LightRay cast_lightray_to(const Point3D& p) const override
			{
				// Create ray starting at the light source's position and going through p
				const Ray ray(m_position, p);

				Vector3D u = (finish - m_position).normalized();
				Vector3D v = (p - m_position).normalized();
				if (u.dot(v) >= cos(angle / 2))
				{
					return LightRay(ray, color);
				}
				else
				{
					return LightRay(ray, colors::black());
				}
			}

	};
}

LightSource raytracer::lights::spot(const Point3D& start, const Point3D& finish, const Angle& angle, const Color& color)
{
	return LightSource(std::make_shared<SpotLight>(start, finish, angle, color));
}