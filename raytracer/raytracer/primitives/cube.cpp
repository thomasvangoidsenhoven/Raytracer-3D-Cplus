#include "primitives/cube.h"
#include "primitives/transformer-primitive.h"
#include "primitives/square-primitive.h"
#include "primitives/union-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

Primitive raytracer::primitives::cube(){
	Primitive x[] = {
		translate(math::Vector3D(0, 0, -0.5), xy_square()),
		translate(math::Vector3D(0, 0, 0.5), xy_square()),
		translate(math::Vector3D(0, -0.5, 0), xz_square()),
		translate(math::Vector3D(0, 0.5, 0), xz_square()),
		translate(math::Vector3D(-0.5, 0, 0), yz_square()),
		translate(math::Vector3D(0.5, 0, 0), yz_square())
	};

	auto allocator =x + sizeof(x) / sizeof(x[0]);
	std::vector<Primitive> v(x, allocator);
	auto cube = primitives::make_union(v);
	return cube;
}