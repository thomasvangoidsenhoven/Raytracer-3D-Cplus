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


	Primitive mesh = primitives::mesh(triangles,boxes);
	return mesh;
}
