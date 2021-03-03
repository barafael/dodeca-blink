#ifndef RANDOM_BLINK_STATE_HPP
#define RANDOM_BLINK_STATE_HPP

#include <cstddef>
#include <cstdint>

#include "FastLED.h"

class RandomBlinkState {
  public:
    size_t index = 0;
    uint8_t brightness = 0;
    uint8_t step_size = 10;
    bool rising = true;
    CHSV color;

    void randomize(size_t max_index);

    void advance(CRGB leds[], size_t max_index);
};

#endif // RANDOM_BLINK_STATE_HPP
