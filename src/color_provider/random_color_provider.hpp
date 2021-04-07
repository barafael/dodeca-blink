#pragma once

#include "producer.hpp"
#include "color_provider.hpp"

#include <FastLED.h>

class RandomColorProvider : public ColorProvider {
public:
    CHSV read() override {
        return CHSV(random8(), random8(128, UINT8_MAX), random8());
    }
};