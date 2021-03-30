#pragma once

#include "consumer.hpp"

#include <FastLED.h>

#include <cstddef>
#include <cstdint>

template<size_t MAX, size_t MIN = 0>
class TwinkleState: public Consumer<CHSV> {
  public:
    TwinkleState() = default;

    void randomize(Producer<CHSV>& color_producer) {
      index      = random8(MIN, MAX);
      brightness = random8(128);
      step_size  = random8(2, 12);
      rising     = true;
      color      = color_producer.read();
    }

    void advance(CRGB leds[], Producer<CHSV>& color_producer) {
      if ((uint32_t)brightness + step_size > UINT8_MAX) {
          rising = false;
      }

      if (!rising && brightness < 10) {
          leds[index] = CRGB::Black;
          randomize(color_producer);
      }

      if (rising) {
          brightness += step_size;
      } else {
          brightness -= step_size;
      }

      this->color.v = brightness;

      leds[index] = color;
    }

    void write(CHSV color) override {
      this->color = color;
    }

  private:
    size_t index       = 0;
    uint8_t brightness = 0;
    uint8_t step_size  = 10;
    bool rising        = true;
    CHSV color;
};