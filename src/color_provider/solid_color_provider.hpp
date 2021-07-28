#pragma once

#include "color_provider.hpp"
#include "producer.hpp"

#include <FastLED.h>

class SolidColorProvider : public ColorProvider {
    public:
    explicit SolidColorProvider(CHSV color) : color(color) {
    }

    CHSV read() override {
        return color;
    }

    bool do_thing(Command command, uint8_t *data, size_t count) {
        if (data == nullptr) {
            return false;
        }

        uint8_t r = data[0];
        uint8_t g = data[1];
        uint8_t b = data[2];

        color = rgb2hsv_approximate(CRGB(r, g, b));

        return true;
    }

    private:
    CHSV color;
};