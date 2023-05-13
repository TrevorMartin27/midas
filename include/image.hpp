#pragma once

#include <vector>
#include <string>

#include <cstdint>

struct Pixel {
	using Type = float;

	Type r, g, b;

	Pixel();
	Pixel(Type r, Type g, Type b);
};

Pixel operator+(const Pixel& pixel, Pixel::Type value);
Pixel operator-(const Pixel& pixel, Pixel::Type value);
Pixel operator*(const Pixel& pixel, Pixel::Type value);
Pixel operator/(const Pixel& pixel, Pixel::Type value);

Pixel operator+(const Pixel& pixel, const Pixel& other);
Pixel operator-(const Pixel& pixel, const Pixel& other);
Pixel operator*(const Pixel& pixel, const Pixel& other);
Pixel operator/(const Pixel& pixel, const Pixel& other);

Pixel operator+=(Pixel& pixel, const Pixel& other);
Pixel operator-=(Pixel& pixel, const Pixel& other);
Pixel operator*=(Pixel& pixel, const Pixel& other);
Pixel operator/=(Pixel& pixel, const Pixel& other);

class Image {
private:
	unsigned int _width, _height;
	std::vector<Pixel> _data;

public:
	Image(unsigned int width, unsigned int height);

	unsigned int width() const;
	unsigned int height() const;

	Pixel& at(unsigned int x, unsigned int y);
	const Pixel& at(unsigned int x, unsigned int y) const;

	void export_png(const std::string& path) const;

	static Image from_file(const std::string& path);

private:
	unsigned int offset(unsigned int x, unsigned int y) const;
};
