#include "primitives/boundingbox_primitive.h"

raytracer::primitives::BoundingBoxAcceleratorImplementation::BoundingBoxAcceleratorImplementation(const Primitive prim) : prim(prim), bounding(prim->bounding_box())
{
}

std::vector<std::shared_ptr<Hit>> raytracer::primitives::BoundingBoxAcceleratorImplementation::find_all_hits(const Ray & ray) const
{
	if (bounding.is_hit_positively_by(ray)) return prim->find_all_hits(ray);
	return std::vector<std::shared_ptr<Hit>>();
}

math::Box raytracer::primitives::BoundingBoxAcceleratorImplementation::bounding_box() const
{
	return bounding;
}



Primitive raytracer::primitives::bounding_box_accelerator(Primitive prim)
{
	return Primitive(std::make_shared<BoundingBoxAcceleratorImplementation>(prim));
}



