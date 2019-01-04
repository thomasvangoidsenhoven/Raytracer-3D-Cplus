#include "ray-tracer-v5.h"
using namespace std;

TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene & scene, const Ray & ray) const
{
	//delegate to trace with weight method with a default of 1;
	return trace(scene, ray, 1.0);
}


TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene & scene, const Ray & ray, double weight) const
{
	Hit hit;
	if (weight > 0.1 && scene.root->find_first_positive_hit(ray, &hit)) {
		//result += compute_ambient
		//result += compute_diffuse
		//result += compute_specular
		//result += compute_reflection
		Color result = colors::black();
		MaterialProperties props = hit.material->at(hit.local_position);
		result += compute_ambient(props);
		result += process_lights(scene,props, hit,ray);
		result += compute_reflection(scene,props,hit,ray,weight);

		return TraceResult(result, hit.group_id, ray, hit.t);


	}


	return TraceResult::no_hit(ray);
}

Color raytracer::raytracers::_private_::RayTracerV5::compute_reflection(const Scene & scene, const MaterialProperties & matProps, const Hit & hit, const Ray & ray, double weight) const
{
	//if material is reflective
	if (matProps.reflectivity > 0.0 && matProps.reflectivity < 0.999) {
		Ray newRay = Ray(hit.position +0.00000001*ray.direction.reflect_by(hit.normal), ray.direction.reflect_by(hit.normal));
		return matProps.reflectivity * trace(scene, newRay,weight*matProps.reflectivity).color;
	}


	return colors::black();
}

RayTracer raytracer::raytracers::v5()
{
	return RayTracer(make_shared<_private_::RayTracerV5>());
}
