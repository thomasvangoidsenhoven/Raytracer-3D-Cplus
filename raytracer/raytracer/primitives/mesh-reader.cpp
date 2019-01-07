#include "mesh-reader.h"
#include "easylogging++.h"
#include "primitives\primitives.h"
#include "json/json.hpp"
using namespace std;
using nlohmann::json;
//returns mesh primitive
Primitive raytracer::primitives::MeshReader::read_mesh(std::string path)
{
	vector<Primitive> triangles;
	vector<Primitive> boxes;

	ifstream file(path);
	if (file.is_open()) {


		json json;
		file >> json;


		//  crashes 3D studio string input = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		//test create pyramid
				//ay thats pretty good
				Point3D p1 = Point3D::spherical(1, Angle::degrees(0),Angle::degrees(90));
				Point3D p2 = Point3D::spherical(1, Angle::degrees(60), Angle::degrees(-30));
				Point3D p3 = Point3D::spherical(1, Angle::degrees(180), Angle::degrees(-30));
				Point3D p4 = Point3D::spherical(1, Angle::degrees(-60), Angle::degrees(-30));
				Primitive t1 = primitives::triangle(p1, p2, p3);
				Primitive t2 = primitives::triangle(p1, p3, p4);
				Primitive t3 = primitives::triangle(p1, p4, p2);
				Primitive t4 = primitives::triangle(p2, p2, p3);
				triangles.push_back(t1);
				triangles.push_back(t2);
				triangles.push_back(t3);
				triangles.push_back(t4);
	}
	else {
		LOG(INFO) << "Mission failed, We'll get em next time!";
	}


	Primitive mesh = primitives::mesh(triangles,boxes);
	return mesh;
}
