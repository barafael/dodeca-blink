#ifndef DODECA_FADE_PALETTE_HPP
#define DODECA_FADE_PALETTE_HPP

#include "FastLED.h"
#include "constants.hpp"
#include "leds.hpp"

#include <cstddef>

DEFINE_GRADIENT_PALETTE (color_palette) {
  50,  50, 255,  0,
  64, 255,   0,   0,   //red
  180, 255, 255,   0,   //bright yellow
  50,  50, 255,  0,
  225, 80, 60, 120,
  255, 0, 0, 0
};

class DodecaFadePalette {
  public:
    DodecaFadePalette() = default;

    void advance() {
        for (size_t strip = 0; strip < STRIP_COUNT; strip++) {
            fill_palette(led_array[strip], NUM_LEDS, paletteIndex, 255 / NUM_LEDS, palette, 255, LINEARBLEND);
        }
        paletteIndex++;
    }
    private:
        uint8_t paletteIndex = 0;
        CRGBPalette16 palette = color_palette;
};

#endif// DODECA_FADE_PALETTE_HPP