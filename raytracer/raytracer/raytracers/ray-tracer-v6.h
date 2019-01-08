#pragma once
#include "raytracers/ray-tracer-v5.h"
using namespace imaging;
namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV6 : public RayTracerV5
			{
			public:
				//override v5
				TraceResult trace(const Scene& scene, const Ray& ray, double weight)const override;
			protected:
				imaging::Color compute_refraction(const Scene& scene, const MaterialProperties& matProps, const Hit& hit, const Ray& ray, double weight)const;
			};


		}

		/// <summary>
		/// Creates simplest ray tracer.
		/// </summary>
		RayTracer v6();
	}
}
