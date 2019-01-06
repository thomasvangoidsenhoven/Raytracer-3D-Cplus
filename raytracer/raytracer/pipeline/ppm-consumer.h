#pragma once

using namespace std;
#include "pipeline/processor.h"
#include "imaging/bitmap.h"

using namespace imaging;
namespace raytracer
{
	namespace pipeline {
		

		shared_ptr<Consumer<shared_ptr<imaging::Bitmap>>> ppm();


	}
}