#pragma once

#include "image.hpp"
#include "palette.hpp"

// TODO: Make the input a constant reference
Image dither(Image& input, const Palette& palette);
