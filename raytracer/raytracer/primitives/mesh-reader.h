#pragma once
#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
		class MeshReader
		{
		public:
			Primitive read_mesh(std::string path);
		};

	}
}