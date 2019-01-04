#pragma once
#include "cameras/displaceable-camera.h"
#include "math/vector.h"
#include "math/point.h"
#include "math/point.h"
#include "math/rectangle3d.h"
#include <memory>

using namespace math;
namespace raytracer
{
	namespace cameras
	{
		namespace _private_
		{
			
			class FisheyeCamera : public DisplaceableCamera
			{
			public:
				const Angle horizontalAngle;
				const Angle verticalAngle;
				// put angles in instances and delegate 
				FisheyeCamera(const math::Matrix4x4 transformation, const Angle& horizontalAngle, const Angle& verticalAngle)
					:DisplaceableCamera(transformation)
					,verticalAngle(verticalAngle), horizontalAngle(horizontalAngle) 
				{

				};

			protected:
				void enumerate_untransformed_rays(const math::Point2D&, std::function<void(const math::Ray&)>) const;

			
			};
		}

		/// <summary>
		/// Creates a fisheye camera.
		/// </summary>
		/// <param name="eye">The camera's location</param>
		/// <param name="look_at">The point the camera is directed at</param>
		/// <param name="up">Specifies how the camera is tilted sideways. (0,1,0) is standard.</param>
		/// <param name="horizontalAngle">How wide you can see horizontally.</param>
		/// <param name="vertivalAngle">How wide you can see vertically.</param>
		Camera fisheye(
			const math::Point3D& eye,
			const math::Point3D& look_at,
			const math::Vector3D& up,
			Angle& horizontalAngle,
			Angle& verticalAngle);
	}
}