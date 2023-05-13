#include <iostream>
#include <string>
#include <cstdlib>

#include "image.hpp"
#include "palette.hpp"

#include "dither.hpp"

struct Config {
	std::string input_path;
	std::string palette_path;
	std::string output_path;
};

// TODO: Do something more C++ like
Config parse_arguments(int argc, const char* argv[]) {
	std::string input_path;
	std::string palette_path = "./palettes/default.txt";
	std::string output_path = "./output.png";

	for(int i = 1; i < argc; i++) {
		std::string argument = std::string(argv[i]);

		if(argument == "--help") {
			std::cout << "Usage: midas <input_path> [--output <output_path>] [--palette <palette_path>]\n";
			exit(0);
		} else if(argument == "--palette") {
			if(argc == (i + 1)) {
				std::cerr << "[ERROR] Expected Path After --palette Directive\n";
				exit(1);
			}

			palette_path = std::move(std::string(argv[++i]));
		} else if(argument == "--output" || argument == "-o") {
			if(argc == (i + 1)) {
				std::cerr << "[ERROR] Expected Path After --output Directive\n";
				exit(1);
			}

			output_path = std::move(std::string(argv[++i]));
		} else if(input_path == "") {
			input_path = std::move(argument);
		} else {
			std::cerr << "[ERROR] Unexpected Argument '" << argument << "'\n";
			exit(1);
		}
	}

	if(input_path == "") {
		std::cout << "[ERROR] Expected Input Path. Run midas --help for help.\n";
		exit(1);
	}

	std::cout << "Input: " << input_path << "\n";
	std::cout << "Palette: " << palette_path << "\n";
	std::cout << "Output: " << output_path << "\n";

	return Config {
		input_path,
		palette_path,
		output_path
	};
}

int main(int argc, const char* argv[]) {
	Config config = parse_arguments(argc, argv);

	Image input = Image::from_file(config.input_path);

	Palette palette = Palette::from_file(config.palette_path);

	Image output = dither(input, palette);

	output.export_png(config.output_path);

	return 0;
}