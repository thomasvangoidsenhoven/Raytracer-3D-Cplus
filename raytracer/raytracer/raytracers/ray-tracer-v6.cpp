#include "ray-tracer-v6.h"
#include "easylogging++.h"
using namespace std;

//identical to v5, except you also add compute_refraction to the result
TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene & scene, const Ray & ray, double weight) const
{
	Hit hit;
	if (weight > 0.1 && scene.root->find_first_positive_hit(ray,&hit)) {

		Color result = colors::black();
		MaterialProperties props = hit.material->at(hit.local_position);
		result += compute_ambient(props);
		result += process_lights(scene, props, hit, ray);
		result += compute_reflection(scene, props, hit, ray, weight);
		result += compute_refraction(scene, props, hit, ray, weight);

		return TraceResult(result, hit.group_id, ray, hit.t);
	}

	return TraceResult::no_hit(ray);
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_refraction(const Scene & scene, const MaterialProperties & matProps, const Hit & hit, const Ray & ray, double weight) const
{
	if (matProps.transparency > 0) {
		// Ray enters transparent object, compute how it is bent at point P1
		auto normal = hit.normal;
		auto rayDirection = ray.direction.normalized();
		auto Ox = (1/matProps.refractive_index)*(rayDirection -(rayDirection.dot(normal)*normal));
		auto Ox² = 1 - pow(Ox.norm(),2);
		//if total internal reflection occurred
		if (Ox² < 0) return colors::black();

		auto Oy = -sqrt(Ox²)*normal;
		//no auto this time to make sure we actually get a vector
		Vector3D o = Ox + Oy;

		//  small "nudges" here and there
		Ray refractedRay = Ray(hit.position + 0.0001*o, o);

		Hit newHit;
		if (scene.root->find_first_positive_hit(refractedRay, &newHit)) {
			auto normal2 = newHit.normal;
			auto rayDirection2 = refractedRay.direction.normalized();
			auto Ox2 = matProps.refractive_index / 1 * (rayDirection2 - (rayDirection2.dot(normal2)*normal2));
			auto Ox²2 = 1 - pow(Ox2.norm(), 2);
			//if total internal reflection occurred
			if (Ox²2 < 0) return colors::black();

			auto Oy2 = -sqrt(Ox²)*normal;
			//no auto this time to make sure we actually get a vector
			Vector3D o2 = Ox2 + Oy2;
			// small "nudges" here and there
			Ray exitRay = Ray(newHit.position + 0.0001 * o2, o2);
			return RayTracerV6::trace(scene, exitRay, weight*matProps.transparency).color;
		}

		
	}

	return colors::black();
}

RayTracer raytracer::raytracers::v6()
{
	return RayTracer(make_shared<_private_::RayTracerV6>());
}
