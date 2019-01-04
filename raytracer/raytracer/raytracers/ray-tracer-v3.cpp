#include "raytracers/ray-tracer-v3.h"


using namespace imaging;
using namespace math;
using namespace raytracer;




raytracer::RayTracer raytracer::raytracers::v3()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}

imaging::Color raytracer::raytracers::_private_::RayTracerV3::process_light_ray(const Scene& scene, const MaterialProperties& material, const Hit& hit, const math::Ray& ray, const LightRay& lightray) const 
{
	Color result = RayTracerV2::process_light_ray(scene, material, hit, ray, lightray);
	result += compute_specular(material, hit, ray, lightray);
	return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const MaterialProperties& material, const Hit& hit, const math::Ray& ray, const LightRay& lightray) const
{
	
	const Point3D rayOrigin = lightray.ray.origin;
	const Color rayColor = lightray.color;

	const Color specularColor = material.specular;

	const Point3D hitPosition = hit.position;

	const Point3D eyePosition = ray.origin;

	 double specularExponent = material.specular_exponent;

	Vector3D lightDirection = (hitPosition - rayOrigin).normalized();
	Vector3D reflectionDirection = lightDirection.reflect_by(hit.normal);
	
	Vector3D tussenstap = (eyePosition - hitPosition).normalized();
	double cos = tussenstap.dot(reflectionDirection);
	if (cos > 0) return rayColor * specularColor * pow(cos, specularExponent);
	return colors::black();
}
