#pragma once

#include "producer.hpp"

#include <FastLED.h>

class PaletteColorProvider: public Producer<CHSV> {
  public:
    explicit PaletteColorProvider(CRGBPalette16 palette): palette(palette) {
    }

    void set_palette(CRGBPalette16 palette) {
        this->palette = palette;
    }

    CHSV read() override {
        return rgb2hsv_approximate(ColorFromPalette(palette, random(0, 255)));
    }

  private:
    CRGBPalette16 palette;
};