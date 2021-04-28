#pragma once

#include "consumer.hpp"
#include "color_provider/color_provider.hpp"
#include "position_provider/position_provider.hpp"

#include <FastLED.h>

#include <cstddef>
#include <cstdint>

class Snake: public Consumer<CHSV> {
public:
    Snake() = default;

    void advance(CRGB leds[], ColorProvider &color_producer, PositionProvider &position_provider) {

    }

    void write(CHSV color) override {
        this->color = color;
    }

private:
    size_t index = 0;
    size_t length = 0;
    uint8_t brightness = 0;
    uint8_t step_size = 10;
    CHSV color;
};