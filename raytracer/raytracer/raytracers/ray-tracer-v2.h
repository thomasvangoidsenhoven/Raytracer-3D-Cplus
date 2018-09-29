#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>


namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV2 : public RayTracerImplementation
			{
			public:
				TraceResult trace(const Scene&, const math::Ray&) const override;

			private:
				Color process_lights(const Scene&, const MaterialProperties&, const Hit&, const Ray&) const;
				Color process_light_source(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, LightSource&) const;
				Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
				Color compute_diffuse(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
			};
		

		}

		/// <summary>
		/// Creates simplest ray tracer.
		/// </summary>
		RayTracer v2();
	}
}
