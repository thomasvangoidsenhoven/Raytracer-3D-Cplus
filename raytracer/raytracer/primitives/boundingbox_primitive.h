#pragma once
#include "primitives/primitive.h"
using namespace math;
using namespace raytracer;

namespace raytracer {
	namespace primitives {

		class BoundingBoxAcceleratorImplementation : public primitives::_private_::PrimitiveImplementation {
		public:
			Primitive prim;
			Box bounding;
			BoundingBoxAcceleratorImplementation(const Primitive prim);
			std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override;
			math::Box bounding_box() const override;
		};

		Primitive raytracer::primitives::bounding_box_accelerator(Primitive prim)
		{
			return Primitive(std::make_shared<BoundingBoxAcceleratorImplementation>(prim));
		}
	}
}