#include "random_blink_state.hpp"

void RandomBlinkState::randomize(size_t max_index, CHSV new_color) {
    index      = random8(max_index);
    brightness = random8(128);
    step_size  = random8(2, 12);
    rising     = true;
    color      = new_color;
}

void RandomBlinkState::randomize(size_t max_index) {
    randomize(max_index, CHSV(random8(), random8(128, UINT8_MAX), random8()));
}

void RandomBlinkState::advance(CRGB leds[], size_t max_index) {
    if ((uint32_t)brightness + step_size > UINT8_MAX) {
        rising = false;
    }

    if (!rising && brightness < 10) {
        leds[index] = CRGB::Black;
        randomize(max_index, color);
    }
    if (rising) {
        brightness += step_size;
    } else {
        brightness -= step_size;
    }
    this->color.v = brightness;

    leds[index] = color;
}
