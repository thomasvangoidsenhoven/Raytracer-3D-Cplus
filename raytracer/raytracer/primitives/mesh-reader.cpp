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
	

	vector<string> strings;
	vector<Primitive> queue;

	ifstream file(path);
	if (file.is_open()) {
		string line;
		while (file.good()) {
			getline(file, line);
			strings.push_back(line);
		}
		LOG(INFO) << strings[0];
		LOG(INFO) << strings.size();

		auto boxes = 0;
		auto triangles = 0;
		vector<Primitive> triangle_queue;
		LOG(INFO) << "Werkt: " << (strings.size() - 5265);
		LOG(INFO) << "Werkt Niet: < " << (strings.size() - 5263);
		for (int i = 0; i < strings.size(); i++)
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

				Point3D a(points[1],points[2],points[3]);
				//LOG(INFO) << "a is " << points[1] << points[2] << points[3];
				Point3D b(points[4], points[5], points[6]);
				//LOG(INFO) << "b is " << points[4]<< points[5]<< points[6];
				Point3D c(points[7], points[8], points[9]);
				//LOG(INFO) << "c is " << points[7]<< points[8]<< points[9];
				
				Primitive p = primitives::triangle(a, b, c);
				//LOG(INFO) << "Primitive MADE";
				//triangle_queue.push_back(p);
			}
			if (test.find("box") != std::string::npos) {
				triangle_queue = vector<Primitive>();
				boxes++;
			}
		}
		//LOG(INFO) << "triangle queue size" <<  triangle_queue.size();
		LOG(INFO) << boxes;
		//LOG(INFO) << triangles;
	}
	else {
		LOG(INFO) << "Mission failed, We'll get em next time!";
	}

	for (int i = 0; i < strings.size(), i++;) 
	{
		string test = strings[i];
		if ( test.at(0) == 't' ){
			string newString;
			
		}
		
	}

	vector<Primitive> triangles2;
	vector<Primitive> boxes2;
	Primitive mesh = primitives::mesh(triangles2, boxes2);
	return mesh;
}