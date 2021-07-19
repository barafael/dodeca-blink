#pragma once

#include <cstddef>

#include "FastLED.h"
#include "constants.hpp"
#include "dodeca_state.hpp"
#include "led_data.hpp"

class ManualMode : public DodecaState {
    public:
    explicit ManualMode(String name) : DodecaState(name) {
    }

    bool do_thing(Command command, uint8_t *data, size_t count) {
        if (data == nullptr) {
            return false;
        }

        uint8_t strip = 0;
        if (data[0] < STRIP_COUNT) {
            strip = data[0];
        }

        uint8_t index = 0;
        if (data[1] < LEDS_PER_STRIP) {
            index = data[1];
        }

        uint8_t r = data[2];
        uint8_t g = data[3];
        uint8_t b = data[4];

        led_array[strip][index] = CRGB(r, g, b);
    }

    void advance() override {
    }
};
