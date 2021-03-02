#ifndef DODECA_TEST_PATTERN_HPP
#define DODECA_TEST_PATTERN_HPP

#include "FastLED.h"

#include "dodecahedron.hpp"
#include "constants.hpp"
#include "leds.hpp"

#define EDGE_LENGTH 10
#define EDGE_COUNT 30

class DodecaTestPattern {
  public:
    DodecaTestPattern(CRGB* edges[]) {
      for (size_t i = 0; i < EDGE_COUNT; i++) {
        this->edges[i] = edges[i];
      }
    }
    
    void advance() {
      
    }

  private:
    Dodecahedron dod;

    CRGB *edges[EDGE_COUNT];
};

#endif // DODECA_TEST_PATTERN_HPP
