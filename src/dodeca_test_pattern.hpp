#ifndef DODECA_TEST_PATTERN_HPP
#define DODECA_TEST_PATTERN_HPP

#include "FastLED.h"

#include <cstddef>

#include "dodecahedron.hpp"
#include "constants.hpp"
#include "leds.hpp"

constexpr size_t EDGE_LENGTH = 10;
constexpr size_t EDGE_COUNT = 30;

class DodecaTestPattern {
  public:
    explicit DodecaTestPattern(CRGB* edges[]) {
      for (size_t i = 0; i < EDGE_COUNT; i++) {
        this->edges[i] = edges[i];
      }
    }

    void advance() {

    }

  private:
    Dodecahedron dod;

    CRGB *edges[EDGE_COUNT] = {};
};

#endif // DODECA_TEST_PATTERN_HPP
