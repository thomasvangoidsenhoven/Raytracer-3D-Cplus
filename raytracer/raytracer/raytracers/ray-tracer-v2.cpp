#include "raytracers/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV2::trace(const Scene& scene, const Ray& ray) const
{
	Hit hit;

	// Ask the scene for the first positive hit, i.e. the closest hit in front of the eye
	// If there's a hit, find_first_positive_hit returns true and updates the hit object with information about the hit
	if (scene.root->find_first_positive_hit(ray, &hit))
	{

		// There's been a hit
		// Fill in TraceResult object with information about the trace
		Material mat = hit.material;
		// This ray tracer always returns white in case of a hit
		
		Color result = colors::black();

		result = hit.material->at(hit.local_position).ambient;
		
		result += this->process_lights(scene, hit.material->at(hit.local_position), hit,ray);

		// The hit object contains the group id, just copy it (group ids are important for edge detection)
		unsigned group_id = hit.group_id;

		// The t-value indicates where the ray/scene intersection took place.
		// You can use ray.at(t) to find the xyz-coordinates in space.
		double t = hit.t;

		// Group all this data into a TraceResult object.
		return TraceResult(result, group_id, ray, t);
	}
	else
	{
		// The ray missed all objects in the scene
		// Return a TraceResult object representing "no hit found"
		// which is basically the same as returning black
		return TraceResult::no_hit(ray);
	}
}
Color raytracer::raytracers::_private_::RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit,  const Ray& ray) const
{
	Color result = colors::black();
	for each(LightSource light_source in scene.light_sources) {
		result += process_light_source(scene, properties, hit, ray, light_source);

	}

	return result;
}

Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightSource lightSource) const
{
	Color result = colors::black();
	for each(LightRay lightray in lightSource->lightrays_to(hit.position)) {
		result += process_light_ray(scene, properties, hit, ray, lightray);
	}	

	return result;
}

Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay& lightRay) const
{
	Color result = colors::black();
	result += compute_diffuse(properties, hit, ray, lightRay);
	return result;
}

Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, const LightRay& lightRay) const
{
	Color lightRayColor = lightRay.color;
	Point3D lightRayOrigin = lightRay.ray.origin;
	Point3D hitPosition = hit.position;
	Color materialColor = properties.diffuse;

	Vector3D tussenstap = (lightRayOrigin - hitPosition).normalized();
	//calculate the angle
	auto angle = tussenstap.dot(hit.normal);
	
	if (angle > 0) return lightRayColor*materialColor*angle;
	return colors::black();
}






raytracer::RayTracer raytracer::raytracers::v2()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}