#include "FastLED.h"

#include "random_blink_state.hpp"
#include "constants.hpp"
#include "leds.hpp"

#define NUM_RANDOM_BLINK_STATES 8

class DodecaRandomBlink {
  public:
    DodecaRandomBlink(CRGB leds[][NUM_LEDS]) {
      for (size_t i = 0; i < NUM_RANDOM_BLINK_STATES; i++) {
        states[0][i].randomize(NUM_LEDS - 1);
        states[1][i].randomize(NUM_LEDS - 1);
        states[2][i].randomize(NUM_LEDS - 1);
        states[3][i].randomize(NUM_LEDS - 1);
        states[4][i].randomize(NUM_LEDS - 1);
        states[5][i].randomize(NUM_LEDS - 1);
      }
    }

    void advance() {
      for (size_t i = 0; i < NUM_RANDOM_BLINK_STATES; i++) {
        states[0][i].advance(led_array[0], NUM_LEDS - 1);
        states[1][i].advance(led_array[1], NUM_LEDS - 1);
        states[2][i].advance(led_array[2], NUM_LEDS - 1);
        states[3][i].advance(led_array[3], NUM_LEDS - 1);
        states[4][i].advance(led_array[4], NUM_LEDS - 1);
        states[5][i].advance(led_array[5], NUM_LEDS - 1);
      }
    }

  private:
    RandomBlinkState states[STRIP_COUNT][NUM_RANDOM_BLINK_STATES];
};
