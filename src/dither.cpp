#include "dither.hpp"

#include <utility>

Image dither(Image& input, const Palette& palette) {
	Image output = Image(input.width(), input.height());

	for(unsigned int y = 0; y < output.height(); y++) {
		for(unsigned int x = 0; x < output.width(); x++) {
			const Pixel old_pixel = input.at(x, y);
			const Pixel new_pixel = palette.closest_color(old_pixel);

			const Pixel error = old_pixel - new_pixel;

			if(x < (input.width() - 1)) {
				input.at(x + 1, y) += error * (7.0/16.0);
			}

			if(x < (input.width() - 1) && y < (input.height() - 1)) {
				input.at(x + 1, y + 1) += error * (1.0/16.0);
			}

			if(y < (input.height() - 1)) {
				input.at(x, y + 1) += error * (5.0/16.0);
			}

			if(x > 0 && y < (input.height() - 1)) {
				input.at(x - 1, y + 1) += error * (3.0/16.0);
			}

			output.at(x, y) = new_pixel;
		}
	}

	return std::move(output);
}
