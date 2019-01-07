#include "mesh-primitive.h"
#include "primitive.h"
#include "triangle-primitive.h"
#include "easylogging++.h"

using namespace raytracer::primitives;
using namespace raytracer;
using namespace std;
using namespace math;
namespace {
	class MeshImplementation : public primitives::_private_::PrimitiveImplementation {
		public:
			vector<Primitive> triangles;
			vector<Primitive> boxes;

			MeshImplementation(const vector<Primitive>& triangles, const vector<Primitive>& boxes) : triangles(triangles),boxes(boxes) {
				LOG(INFO) << "Starting Construction";

				//test create pyramid
				//ay thats pretty good
				//Point3D p1 = Point3D::spherical(1, Angle::degrees(0),Angle::degrees(90));
				//Point3D p2 = Point3D::spherical(1, Angle::degrees(60), Angle::degrees(-30));
				//Point3D p3 = Point3D::spherical(1, Angle::degrees(180), Angle::degrees(-30));
				//Point3D p4 = Point3D::spherical(1, Angle::degrees(-60), Angle::degrees(-30));
				//Primitive t1 = primitives::triangle(p1, p2, p3);
				//Primitive t2 = primitives::triangle(p1, p3, p4);
				//Primitive t3 = primitives::triangle(p1, p4, p2);
				//Primitive t4 = primitives::triangle(p2, p2, p3);
				//this->triangles.push_back(t1);
				//this->triangles.push_back(t2);
				//this->triangles.push_back(t3);
				//this->triangles.push_back(t4);
			}

			vector<shared_ptr<Hit>> find_all_hits(const Ray& ray) const override {
				vector<shared_ptr<Hit>> hits;
				for each (Primitive p in triangles) {
					//TODO optimized triangle
					Hit hit;
					p->find_first_positive_hit(ray,&hit);

					hits.push_back(make_shared<Hit>(hit));
				}
				return hits;
			}

			Box bounding_box() const override {
				//SHOULD JUST RETURN THE FIRST ELEMENT (biggest box)

				//test
				//get bounding box of first triangle.
				Box smallbox = triangles.at(0)->bounding_box();

				//group all boxes until you end up with on single box
				for each (Primitive p in triangles)
				{
					smallbox = smallbox.merge(p->bounding_box());
				}

				return smallbox;
			}


	};
}

Primitive raytracer::primitives::mesh(const vector<Primitive>& triangles, const vector<Primitive>& boxes)
{
	return Primitive(make_shared<MeshImplementation>(triangles,boxes));
}
