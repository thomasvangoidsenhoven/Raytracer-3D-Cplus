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
				//LOG(INFO) << "PUNTEN" << points[1];
				Primitive p = primitives::triangle(a, b, c);
				triangle_queue.push_back(p);
			}
			if (test.find("box") != std::string::npos) {
				LOG(INFO) << "QUEUE SIZE BEGIN" << queue.size();
				if (triangle_queue.size() > 0) {
					//LOG(INFO) << "Triangle Queue Size: " << triangle_queue.size();
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
				LOG(INFO) << "QUEUE SIZE END" << queue.size();

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

	LOG(INFO) << "Phase 3 initiated!";

	

	
	//Primitive triangleTest = primitives::bounding_box_accelerator(primitives::triangle(Point3D(0,0,0),Point3D(0, 1, 0),Point3D(0, 0,1)));
	LOG(INFO) << "Phase 4 initiated! Queue size is " << queue.size();

	Primitive theLastPrimitive = queue[0];
	
	LOG(INFO) << "Phase 5 initiated!";

	Primitive mesh = primitives::mesh(theLastPrimitive);
	return mesh;
}