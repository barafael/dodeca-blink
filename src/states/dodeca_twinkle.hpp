#pragma once

#include <FastLED.h>

#include <cstddef>

#include "constants.hpp"
#include "led_data.hpp"
#include "dodeca_twinkle.hpp"
#include "dodeca_state.hpp"
#include "command.hpp"
#include "color_provider/color_provider.hpp"

#include "states/twinkle_state.hpp"

constexpr size_t NUM_RANDOM_BLINK_STATES = 8;

class DodecaTwinkle: public DodecaState {
  public:
    DodecaTwinkle(String name, ColorProvider& color_producer): DodecaState(name), color_producer(color_producer) {
        for (size_t i = 0; i < STRIP_COUNT; i++) {
            for (size_t j = 0; j < NUM_RANDOM_BLINK_STATES; j++) {
                states[i][j].randomize(color_producer);
            }
        }
    }

    bool do_thing(Command id) override {
        switch (id)
        {
            case Command::ACTION_A:
                blur = !blur;
                return true;
            case Command::ACTION_B:
                FastLED.clear();
                return color_producer.do_thing(Command::ACTION_B);
            case Command::ACTION_C:
                return false;

            default:
                return false;
        }
    }

    char const *const get_thing_name(Command id) override {
        switch (id)
        {
            case Command::ACTION_A:
                return "Toggle blur";
            case Command::ACTION_B:
                return color_producer.get_thing_name(Command::ACTION_B);
            default:
                return "";
        }
    }

    void advance() override {
        for (size_t i = 0; i < STRIP_COUNT; i++) {
            for (size_t j = 0; j < NUM_RANDOM_BLINK_STATES; j++) {
                states[i][j].advance(led_array[i], color_producer);
            }
        }

        if (blur) {
            uint8_t blurAmount = dim8_raw(beatsin8(3, 15, LEDS_PER_STRIP));

            blur1d( led_array[0], LEDS_PER_STRIP, blurAmount);
            blur1d( led_array[1], LEDS_PER_STRIP, blurAmount);
            blur1d( led_array[2], LEDS_PER_STRIP, blurAmount);
            blur1d( led_array[3], LEDS_PER_STRIP, blurAmount);
            blur1d( led_array[4], LEDS_PER_STRIP, blurAmount);
            blur1d( led_array[5], LEDS_PER_STRIP, blurAmount);
        }
    }

  private:
    ColorProvider &color_producer;
    TwinkleState<LEDS_PER_STRIP> states[STRIP_COUNT][NUM_RANDOM_BLINK_STATES];
    bool blur = false;
};
