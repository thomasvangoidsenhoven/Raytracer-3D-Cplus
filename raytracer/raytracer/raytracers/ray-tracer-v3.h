#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>
#include "raytracers/ray-tracer.h"
#include "materials/material-properties.h"
#include "lights/light-ray.h"
#include "lights/light-source.h"
#include "ray-tracer-v2.h"


namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV3 : public RayTracerV2
			{

			protected:
				virtual imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
				virtual imaging::Color compute_specular(const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const;
			};


		}

		/// <summary>
		/// Creates simplest ray tracer.
		/// </summary>
		RayTracer v3();
	}
}
