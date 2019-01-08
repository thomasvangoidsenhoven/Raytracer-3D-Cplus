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
			Primitive triangles;

			MeshImplementation(const Primitive& triangles) : triangles(triangles) {
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
				Hit hit;
				triangles->find_first_positive_hit(ray, &hit);
				hits.push_back(make_shared<Hit>(hit));
				return hits;
			}

			Box bounding_box() const override {
				

				return triangles->bounding_box();
			}


	};
}

Primitive raytracer::primitives::mesh(const Primitive& triangles)
{
	return Primitive(make_shared<MeshImplementation>(triangles));
}
