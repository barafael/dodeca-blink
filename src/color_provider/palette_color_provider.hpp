#pragma once

#include "producer.hpp"
#include "states/does_things.hpp"
#include "color_provider.hpp"
#include "command.hpp"

#include <FastLED.h>

class PaletteColorProvider : public ColorProvider {
public:
    PaletteColorProvider(CRGBPalette16 *palettes, size_t num_palettes) : palettes(palettes), num_palettes(num_palettes) { }

    bool do_thing(Command id) override {
        if (id == Command::ACTION_B) {
            current_palette = (current_palette + 1) % num_palettes;
        }
        return false;
    }

    CHSV read() override {
        return rgb2hsv_approximate(ColorFromPalette(palettes[current_palette], random8()));
    }

private:
    CRGBPalette16 *palettes;
    const size_t num_palettes;
    size_t current_palette = 0;
};