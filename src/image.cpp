#include "image.hpp"

#include <algorithm>
#include <utility>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

static Pixel::Type clamp(Pixel::Type value, Pixel::Type min, Pixel::Type max) {
	value = value < min ? min : value;
	return value > max ? max : value;
}

Pixel::Pixel() { }

Pixel::Pixel(Pixel::Type r, Pixel::Type g, Pixel::Type b) {
	this->r = clamp(r, 0.0, 1.0);
	this->g = clamp(g, 0.0, 1.0);
	this->b = clamp(b, 0.0, 1.0);
}

Pixel operator+(const Pixel& pixel, Pixel::Type value) {
	return Pixel(
		pixel.r + value,
		pixel.g + value,
		pixel.b + value
	);
}

Pixel operator-(const Pixel& pixel, Pixel::Type value) {
	return Pixel(
		pixel.r - value,
		pixel.g - value,
		pixel.b - value
	);
}

Pixel operator*(const Pixel& pixel, Pixel::Type value) {
	return Pixel(
		pixel.r * value,
		pixel.g * value,
		pixel.b * value
	);
}

Pixel operator/(const Pixel& pixel, Pixel::Type value) {
	return Pixel(
		pixel.r / value,
		pixel.g / value,
		pixel.b / value
	);
}

Pixel operator+(const Pixel& pixel, const Pixel& other) {
	return Pixel(
		pixel.r + other.r,
		pixel.g + other.g,
		pixel.b + other.b
	);
}

Pixel operator-(const Pixel& pixel, const Pixel& other) {
	return Pixel(
		pixel.r - other.r,
		pixel.g - other.g,
		pixel.b - other.b
	);
}

Pixel operator*(const Pixel& pixel, const Pixel& other) {
	return Pixel(
		pixel.r * other.r,
		pixel.g * other.g,
		pixel.b * other.b
	);
}

Pixel operator/(const Pixel& pixel, const Pixel& other) {
	return Pixel(
		pixel.r / other.r,
		pixel.g / other.g,
		pixel.b / other.b
	);
}

Pixel operator+=(Pixel& pixel, const Pixel& other) {
	return (pixel = pixel + other);
}

Pixel operator-=(Pixel& pixel, const Pixel& other) {
	return (pixel = pixel - other);
}

Pixel operator*=(Pixel& pixel, const Pixel& other) {
	return (pixel = pixel * other);
}

Pixel operator/=(Pixel& pixel, const Pixel& other) {
	return (pixel = pixel / other);
}

Image::Image(unsigned int width, unsigned int height)
	: _width(width), _height(height), _data(width * height)
{
}

unsigned int Image::width() const {
	return this->_width;
}

unsigned int Image::height() const {
	return this->_height;
}

Pixel& Image::at(unsigned int x, unsigned int y) {
	return this->_data[this->offset(x, y)];
}

const Pixel& Image::at(unsigned int x, unsigned int y) const {
	return this->_data[this->offset(x, y)];
}

unsigned int Image::offset(unsigned int x, unsigned int y) const {
	assert(x < this->width());
	assert(y < this->height());

	return (y * this->width()) + x;
}

void Image::export_png(const std::string& path) const {
	std::vector<std::uint8_t> data(this->width() * this->height() * 3);

	unsigned int offset = 0;
	for(unsigned int y = 0; y < this->height(); y++) {
		for(unsigned int x = 0; x < this->width(); x++) {
			const Pixel& pixel = this->at(x, y);

			data[offset++] = static_cast<std::uint8_t>(pixel.r * 255.0);
			data[offset++] = static_cast<std::uint8_t>(pixel.g * 255.0);
			data[offset++] = static_cast<std::uint8_t>(pixel.b * 255.0);
		}
	}

	stbi_flip_vertically_on_write(false);

	int res = stbi_write_png(path.c_str(), this->width(), this->height(), 3, data.data(), 3 * this->width());
}

Image Image::from_file(const std::string& path) {
	int width, height, channels;
	std::uint8_t* data = stbi_load(path.c_str(), &width, &height, &channels, 3);
	if(data == NULL) {
		throw std::bad_alloc();
	}

	Image image = Image(width, height);

	const std::uint8_t* reader = data;
	for(unsigned int y = 0; y < image.height(); y++) {
		for(unsigned int x = 0; x < image.width(); x++) {
			image.at(x, y) = Pixel(
				static_cast<Pixel::Type>(reader[0]) / static_cast<Pixel::Type>(0xff),
				static_cast<Pixel::Type>(reader[1]) / static_cast<Pixel::Type>(0xff),
				static_cast<Pixel::Type>(reader[2]) / static_cast<Pixel::Type>(0xff)
			);

			reader += 3;
		}
	}

	return std::move(image);
}
