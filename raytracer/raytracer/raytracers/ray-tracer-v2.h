#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>
#include "raytracers/ray-tracer.h"
#include "materials/material-properties.h"
#include "lights/light-ray.h"
#include "lights/light-source.h"


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

			protected:
				imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;

			private:
				imaging::Color process_lights(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&) const;
				imaging::Color process_light_source(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, LightSource) const;
				imaging::Color compute_diffuse(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
			};
		

		}

		/// <summary>
		/// Creates simplest ray tracer.
		/// </summary>
		RayTracer v2();
	}
}
