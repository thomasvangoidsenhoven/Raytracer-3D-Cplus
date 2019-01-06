#include "ppm-format.h"



void imaging::PPM::write_text_ppm(const Bitmap & bitmap, std::ostream & cout)
{
	//stdendl no workerino?
	//using ASCII // https://en.wikipedia.org/wiki/Netpbm_format
	int width = bitmap.width();
	int height = bitmap.height();

	cout << "P3" << "\n";
	cout << std::to_string(width) << " " << std::to_string(height) << "\n";
	cout << std::to_string(255) << "\n";

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Color color = bitmap[Position2D(j, i)].clamped();
			cout << std::round(color.r * 255) << " " << std::round(color.g * 255) << " " << std::round(color.b * 255) << "/t";
		}
		cout << "\n";
	}
}
