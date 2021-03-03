#include "random_blink_state.hpp"

void RandomBlinkState::randomize(size_t max_index) {
  index = random8(max_index);
  brightness = random8(128);
  step_size = random8(2, 12);
  rising = true;
  color = CHSV(random8(), random8(128, 255), random8());
}

void RandomBlinkState::advance(CRGB leds[], size_t max_index) {
  if ((uint32_t)brightness + step_size > 255) {
    rising = false;
  }

  if (!rising && brightness < 30) {
    leds[index] = CRGB::Black;
    randomize(max_index);
  }
  if (rising) {
    brightness += step_size;
  } else {
    brightness -= step_size;
  }
  color.v = brightness;

  leds[index] = color;
}
