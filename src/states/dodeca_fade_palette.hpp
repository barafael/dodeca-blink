#pragma once

#include "FastLED.h"
#include "constants.hpp"
#include "dodeca_state.hpp"
#include "led_data.hpp"

#include <cstddef>

DEFINE_GRADIENT_PALETTE(color_palette) { 50,  50,  255, 0, 64,  255, 0,  0, //red
                                         180, 255, 255, 0, //bright yellow
                                         50,  50,  255, 0, 225, 80,  60, 120, 255, 0, 0, 0 };

class DodecaFadePalette : public DodecaState {
    public:
    explicit DodecaFadePalette(String name) : DodecaState(name) {
    }

    void advance() override {
        for (size_t strip = 0; strip < STRIP_COUNT; strip++) {
            fill_palette(led_array[strip], LEDS_PER_STRIP, paletteIndex, 255 / LEDS_PER_STRIP, palette, 255, LINEARBLEND);
        }
        paletteIndex++;
    }

    private:
    uint8_t       paletteIndex = 0;
    CRGBPalette16 palette      = color_palette;
};
