#include "raytracers/ray-tracer-v4.h"


using namespace imaging;
using namespace math;
using namespace raytracer;




raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene& scene, const MaterialProperties& material, const Hit& hit, const math::Ray& ray, const LightRay& lightRay) const
{
	Hit hitted;

	scene.root->find_first_positive_hit(lightRay.ray, &hitted);
	if (hitted.t >= 0.0 && hitted.t < 1.0) {
		return colors::black();
	}
	
	
	
	return RayTracerV3::process_light_ray(scene, material, hit, ray, lightRay);


}
