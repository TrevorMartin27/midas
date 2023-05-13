#pragma once

#include <vector>
#include <string>

#include "image.hpp"

class Palette {
private:
	std::vector<Pixel> colors;

public:
	Palette();
	Palette(std::vector<Pixel> colors);

	Pixel closest_color(Pixel pixel) const;

	static Palette from_file(const std::string& path);
};
