#include "ppm-consumer.h"
#include "imaging/ppm-format.h"

#include "imaging/bitmap.h"
using namespace raytracer::pipeline;
using namespace imaging;

class Ppm : public Consumer<shared_ptr<imaging::Bitmap>>
{
public:
	void consume(std::shared_ptr<imaging::Bitmap> bitmap) override{
		ppm.write_text_ppm(*bitmap, std::cout);
	}


private:
	PPM ppm;


};



namespace raytracer {
	namespace pipeline {
		std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> ppm()
		{
			return make_shared<Ppm>();
		}
	}
}

