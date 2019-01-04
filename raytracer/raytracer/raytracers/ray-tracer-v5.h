#pragma once
#include "raytracers/ray-tracer-v4.h"
using namespace imaging;
namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV5 : public RayTracerV4
			{
				public:
					//override original (v0 method)
					TraceResult trace(const Scene& scene, const Ray& ray) const override;

					TraceResult trace(const Scene& scene, const Ray& ray, double weight)const;
				protected:
					Color compute_reflection(const Scene& scene, const MaterialProperties& matProps, const Hit& hit, const Ray& ray, double weight) const;
			};


		}

		/// <summary>
		/// Creates simplest ray tracer.
		/// </summary>
		RayTracer v5();
	}
}
