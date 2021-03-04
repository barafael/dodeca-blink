#ifndef DODECA_TEST_PATTERN_HPP
#define DODECA_TEST_PATTERN_HPP

#include "FastLED.h"

#include "constants.hpp"
#include "dodecahedron.hpp"
#include "leds.hpp"

#include <array>

#include <cstddef>

constexpr size_t EDGE_LENGTH = 10;
constexpr size_t EDGE_COUNT  = 30;

class DodecaTestPattern {
  public:
    explicit DodecaTestPattern(CRGB *edges[]) {
        for (size_t i = 0; i < EDGE_COUNT; i++) {
            this->edges[i] = edges[i];
        }
    }

    void advance() {
    }

  private:
    Dodecahedron dod;
    std::array<CRGB*, EDGE_COUNT> edges = {};
};

#endif// DODECA_TEST_PATTERN_HPP
