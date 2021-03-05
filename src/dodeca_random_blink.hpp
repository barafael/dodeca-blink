#ifndef DODECA_RANDOM_BLINK
#define DODECA_RANDOM_BLINK

#include "FastLED.h"
#include "constants.hpp"
#include "leds.hpp"
#include "random_blink_state.hpp"

#include <cstddef>

constexpr size_t NUM_RANDOM_BLINK_STATES = 8;

class DodecaRandomBlink {
  public:
    DodecaRandomBlink() {
        for (size_t i = 0; i < STRIP_COUNT; i++) {
            for (size_t j = 0; j < NUM_RANDOM_BLINK_STATES; j++) {
                states[i][j].randomize(LEDS_PER_STRIP - 1);
            }
        }
    }

    void advance() {
        for (size_t i = 0; i < STRIP_COUNT; i++) {
            for (size_t j = 0; j < NUM_RANDOM_BLINK_STATES; j++) {
                states[i][j].advance(led_array[i], LEDS_PER_STRIP - 1);
            }
        }
    }

  private:
    RandomBlinkState states[STRIP_COUNT][NUM_RANDOM_BLINK_STATES] = {};
};

#endif// DODECA_RANDOM_BLINK