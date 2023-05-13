#include "palette.hpp"

#include <fstream>
#include <limits>
#include <utility>

#include <cstdint>

Palette::Palette() { }

Palette::Palette(std::vector<Pixel> colors) : colors(std::move(colors)) { }

Pixel Palette::closest_color(Pixel pixel) const {
	Pixel closest_color;
	Pixel::Type lowest_error = std::numeric_limits<Pixel::Type>::max();

	for(const auto& color : this->colors) {
		const Pixel::Type error = (
			(pixel.r - color.r) * (pixel.r - color.r) +
			(pixel.g - color.g) * (pixel.g - color.g) +
			(pixel.b - color.b) * (pixel.b - color.b)
		);

		if(error < lowest_error) {
			closest_color = color;
			lowest_error = error;
		}
	}

	return std::move(closest_color);
}

Palette Palette::from_file(const std::string& path) {
	std::ifstream file(path);

	std::vector<Pixel> colors;

	unsigned int r, g, b;
	while(file >> r >> g >> b) {
		colors.push_back(Pixel(
			static_cast<Pixel::Type>(r) / static_cast<Pixel::Type>(0xff),
			static_cast<Pixel::Type>(g) / static_cast<Pixel::Type>(0xff),
			static_cast<Pixel::Type>(b) / static_cast<Pixel::Type>(0xff)
		));
	}

	return Palette(std::move(colors));
}
