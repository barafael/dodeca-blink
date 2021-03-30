#ifndef DODECA_RANDOM_BLINK_HPP
#define DODECA_RANDOM_BLINK_HPP

#include <FastLED.h>

#include <cstddef>

#include "constants.hpp"
#include "led_data.hpp"
#include "dodeca_twinkle.hpp"
#include "state.hpp"
#include "command.hpp"
#include "ColorProviders/twinkle_state.hpp"

constexpr size_t NUM_RANDOM_BLINK_STATES = 8;

class DodecaTwinkle: public DodecaState {
  public:
    DodecaTwinkle(Producer<CHSV>& color_producer): color_producer(color_producer) {
        for (size_t i = 0; i < STRIP_COUNT; i++) {
            for (size_t j = 0; j < NUM_RANDOM_BLINK_STATES; j++) {
                states[i][j].randomize(color_producer);
            }
        }
    }

    bool do_thing(uint8_t id) override {
        switch ((Command)id)
        {
            case Command::ACTION_A:
                return false;
                break;
            case Command::ACTION_B:
                return false;
                break;
            case Command::ACTION_C:
                return false;
                break;

            default:
                return false;
        }
    }

    bool do_thing(uint8_t id, uint8_t* args, size_t count) override {
        return false;
    }

    void advance() override {
        for (size_t i = 0; i < STRIP_COUNT; i++) {
            for (size_t j = 0; j < NUM_RANDOM_BLINK_STATES; j++) {
                states[i][j].advance(led_array[i], color_producer);
            }
        }
    }

  private:
    Producer<CHSV> &color_producer;
    TwinkleState<LEDS_PER_STRIP> states[STRIP_COUNT][NUM_RANDOM_BLINK_STATES];
};

#endif// DODECA_RANDOM_BLINK_HPP