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

		LOG(INFO) << "JSON SIZE" << json.size();
		int count = 0;
		// range-based for triangles
		for (auto& element : json) {
			if (!element["triangles"].is_null()) {
				for (auto& triangle : element["triangles"]) {
					count++;

					auto puntA = triangle[0];
					string aXs = puntA[0];
					double aX;
					stringstream(aXs) >> aX;
					string aYs = puntA[1];
					double aY;
					stringstream(aYs) >> aY;
					string aZs = puntA[2];
					double aZ;
					stringstream(aYs) << aZ;
					Point3D a(aX,aY,aZ);
					

					auto puntB = triangle[0];
					string bXs = puntB[0];
					double bX;
					stringstream(bXs) >> bX;
					string bYs = puntB[1];
					double bY;
					stringstream(bYs) >> bY;
					string bZs = puntB[2];
					double bZ;
					stringstream(bYs) << bZ;
					Point3D b(bX, bY, bZ);


					auto puntC = triangle[0];
					string cXs = puntC[0];
					double cX;
					stringstream(cXs) >> cX;
					string cYs = puntC[1];
					double cY;
					stringstream(cYs) >> cY;
					string cZs = puntC[2];
					double cZ;
					stringstream(cZs) << cZ;
					Point3D c(cX, cY, cZ);
				
					triangles.push_back(primitives::triangle(a, b, c));
				}
			}
			
		}

		LOG(INFO) << "Amount of triangles: " << count;



		//  crashes 3D studio string input = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		//test create pyramid
				//ay thats pretty good
				/*Point3D p1 = Point3D::spherical(1, Angle::degrees(0),Angle::degrees(90));
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
				triangles.push_back(t4);*/
	}
	else {
		LOG(INFO) << "Mission failed, We'll get em next time!";
	}


	Primitive mesh = primitives::mesh(triangles,boxes);
	return mesh;
}
