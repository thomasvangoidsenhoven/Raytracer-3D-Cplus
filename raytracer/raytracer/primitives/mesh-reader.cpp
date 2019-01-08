#include "mesh-reader.h"
#include "easylogging++.h"
#include "primitives\primitives.h"
#include "json/json.hpp"
#include <iostream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;
using nlohmann::json;
//returns mesh primitive
Primitive raytracer::primitives::MeshReader::read_mesh(std::string path)
{
	LOG(INFO) << "Reading mesh " << path;
	vector<Primitive> primitiveList;


	vector<string> strings;
	vector<Primitive> queue;

	ifstream file(path);
	if (file.is_open()) {
		string line;
		while (file.good()) {
			getline(file, line);
			strings.push_back(line);
		}

		vector<Primitive> triangle_queue;
		// vector<Primitive> queue;
		for (int i = 0; i <= strings.size(); i++)
		{
			string test = strings[i];
			if (test.find("triangle") != std::string::npos) {
				vector<double> points;
				std::regex r("^triangle\\\s\\[\\[([-\\d.]*)\\\s([-\\d.]*)\\\s([-\\d.]*)\\],\\[([-\\d.]*)\\\s([-\\d.]*)\\\s([-\\d.]*)\\],\\[([-\\d.]*)\\\s([-\\d.]*)\\\s([-\\d.]*)\\]\\]"); // entire match will be 2 numbers
				std::smatch m;
				std::regex_search(test, m, r);
				for (auto v : m) {
					double x = 0;
					istringstream s(v);
					s >> x;
					points.push_back(x);
				}

				Point3D a(points[1], points[2], points[3]);
				Point3D b(points[4], points[5], points[6]);
				Point3D c(points[7], points[8], points[9]);

				Primitive p = primitives::triangle(a, b, c);
				triangle_queue.push_back(p);
			}
			if (test.find("box") != std::string::npos) {
				//LOG(INFO) << "QUEUE SIZE BEGIN" << queue.size();
				if (triangle_queue.size() > 0) {
				
					auto x = primitives::make_union(triangle_queue);
					queue.insert(queue.begin(), primitives::bounding_box_accelerator(x));
					
				}
				else if(triangle_queue.size() == 0 && queue.size() >= 2){
					Primitive p;
					vector<Primitive>pv = vector<Primitive>();
					pv.push_back(queue[0]);
					pv.push_back(queue[1]);
					queue.erase(queue.begin());
					queue.erase(queue.begin());
					p = primitives::make_union(pv);
					queue.insert(queue.begin(),primitives::bounding_box_accelerator(p));
				}
				else {
				}
				//LOG(INFO) << "QUEUE SIZE END" << queue.size();

				triangle_queue = vector<Primitive>();
			}
		}

	}
	else {
		LOG(INFO) << "Mission failed, We'll get em next time!";
	}

	LOG(INFO) << "Phase 2 initiated!";
	//test create pyramid
	//ay thats pretty good
	vector<Primitive> triangles = vector<Primitive>();
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
	LOG(INFO) << "Phase 3 initiated!";

	vector<Primitive> testVector = vector<Primitive>();
	testVector.push_back(t1);
	testVector.push_back(t2);

	vector<Primitive> testVector2 = vector<Primitive>();
	testVector2.push_back(t3);
	testVector2.push_back(t4);

	

	vector<Primitive> testVector3 = vector<Primitive>();
	testVector3.push_back(primitives::bounding_box_accelerator(primitives::make_union(testVector)));
	testVector3.push_back(primitives::bounding_box_accelerator(primitives::make_union(testVector2)));

	Primitive pyramid = primitives::bounding_box_accelerator(primitives::make_union(triangles));
	Primitive boxyboy = primitives::bounding_box_accelerator(primitives::make_union(testVector3));
	
	//Primitive triangleTest = primitives::bounding_box_accelerator(primitives::triangle(Point3D(0,0,0),Point3D(0, 1, 0),Point3D(0, 0,1)));
	LOG(INFO) << "Phase 4 initiated! Queue size is " << queue.size();

	Primitive theLastPrimitive = queue[0];
	LOG(INFO) << "Phase 5 initiated!";

	Primitive mesh = primitives::mesh(theLastPrimitive);
	return mesh;
}