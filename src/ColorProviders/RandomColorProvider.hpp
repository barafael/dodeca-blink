#pragma once

#include "Producer.hpp"

#include <FastLED.h>

class RandomColorProvider: public Producer<CHSV> {
  public:
    CHSV read() override {
        return CHSV(random8(), random8(128, UINT8_MAX), random8());
    }
};