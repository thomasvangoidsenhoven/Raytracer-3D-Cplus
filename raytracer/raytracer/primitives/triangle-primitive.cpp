#include "primitives/triangle-primitive.h"

using namespace raytracer;
using namespace std;
using namespace math;
namespace raytracer {
	namespace primitives {
		class TriangleImplementation : public _private_::PrimitiveImplementation {
		public:
			Point3D a;
			Point3D b;
			Point3D c;
			Vector3D normalVector;
			TriangleImplementation(const Point3D a, const Point3D b, const Point3D c) : a(a), b(b), c(c) {
				// Compute the normal vector on the plane.
				//Since this remains constant, you might want to do this only once, in the constructor.
				normalVector = (b - a).cross(c - a).normalized();
			}

			vector<shared_ptr<Hit>> find_all_hits(const Ray& ray) const override {
				vector<shared_ptr<Hit>> hits;
				auto t_hit = (a - ray.origin).dot(normalVector) / ray.direction.dot(normalVector);
				auto hit_position = ray.origin + ray.direction * t_hit;;

				//check if hitposition is to the right of ab
				if ((b - a).cross(hit_position - a).dot(normalVector) < 0) return hits;
				//check if hitposition is to the right of bc
				if ((c - b).cross(hit_position - b).dot(normalVector) < 0) return hits;
				//check if hitposition is to the right of ca
				if ((a - c).cross(hit_position - c).dot(normalVector) < 0) return hits;
				auto hit = make_shared<Hit>();
				hit->t = t_hit;
				hit->position = ray.at(t_hit);
				hit->local_position.xyz = hit->position;
				hit->local_position.uv = Point2D(0, 0);
				hit->normal = normalVector;
				hits.push_back(hit);

				return hits;
			}

			Box bounding_box() const override {
				auto minX = min(min(a.x(), b.x()), c.x());
				auto minY = min(min(a.y(), b.y()), c.y());
				auto minZ = min(min(a.z(), b.z()), c.z());
				auto maxX = max(max(a.x(), b.x()), c.x());
				auto maxY = max(max(a.y(), b.y()), c.y());
				auto maxZ = max(max(a.z(), b.z()), c.z());

				return Box(interval(minX, maxX), interval(minY, maxY), interval(minZ, maxZ));
			}


		};
	}
}

Primitive raytracer::primitives::triangle(const Point3D a, const Point3D b, const Point3D c)
{
	return Primitive(std::make_shared<TriangleImplementation>(a, b, c));
}