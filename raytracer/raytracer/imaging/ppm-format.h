#include "bitmap.h"
namespace imaging {
	class PPM {
	public:
		void write_text_ppm(const Bitmap& bitmap, std::ostream& out);
	};
	
}