#ifndef DODECA_TEST_PATTERN_HPP
#define DODECA_TEST_PATTERN_HPP

#include "Arduino.h"
#include "FastLED.h"
#include "constants.hpp"
#include "dodecahedron.hpp"
#include "leds.hpp"

#include <array>
#include <cstddef>

constexpr size_t EDGE_COUNT    = 30;
constexpr size_t LEDS_PER_EDGE = 10;

class IndexPair {
  public:
    IndexPair() = default;
    IndexPair(size_t strip, size_t index): strip(strip), index(index) {
    }

    size_t strip = 0;
    size_t index = 0;
};

class DodecaTestPattern {
  public:
    DodecaTestPattern() {
        coordinates[0]  = {0, 0 * LEDS_PER_EDGE};
        coordinates[5]  = {0, 1 * LEDS_PER_EDGE};
        coordinates[19] = {0, 2 * LEDS_PER_EDGE};
        coordinates[24] = {0, 3 * LEDS_PER_EDGE};
        coordinates[29] = {0, 4 * LEDS_PER_EDGE};

        coordinates[1]  = {1, 0 * LEDS_PER_EDGE};
        coordinates[6]  = {1, 1 * LEDS_PER_EDGE};
        coordinates[15] = {1, 2 * LEDS_PER_EDGE};
        coordinates[20] = {1, 3 * LEDS_PER_EDGE};
        coordinates[25] = {1, 4 * LEDS_PER_EDGE};

        coordinates[2]  = {2, 0 * LEDS_PER_EDGE};
        coordinates[7]  = {2, 1 * LEDS_PER_EDGE};
        coordinates[16] = {2, 2 * LEDS_PER_EDGE};
        coordinates[21] = {2, 3 * LEDS_PER_EDGE};
        coordinates[26] = {2, 4 * LEDS_PER_EDGE};

        coordinates[3]  = {3, 0 * LEDS_PER_EDGE};
        coordinates[8]  = {3, 1 * LEDS_PER_EDGE};
        coordinates[17] = {3, 2 * LEDS_PER_EDGE};
        coordinates[22] = {3, 3 * LEDS_PER_EDGE};
        coordinates[27] = {3, 4 * LEDS_PER_EDGE};

        coordinates[4]  = {4, 0 * LEDS_PER_EDGE};
        coordinates[9]  = {4, 1 * LEDS_PER_EDGE};
        coordinates[18] = {4, 2 * LEDS_PER_EDGE};
        coordinates[23] = {4, 3 * LEDS_PER_EDGE};
        coordinates[28] = {4, 4 * LEDS_PER_EDGE};

        coordinates[10] = {5, 0 * LEDS_PER_EDGE};
        coordinates[11] = {5, 1 * LEDS_PER_EDGE};
        coordinates[12] = {5, 2 * LEDS_PER_EDGE};
        coordinates[13] = {5, 3 * LEDS_PER_EDGE};
        coordinates[14] = {5, 4 * LEDS_PER_EDGE};
    }

    void advance() {
        // Reset old LEDs
        for (size_t i = 0; i < LEDS_PER_EDGE; i++) {
            led_array[previous.strip][previous.index + i] = CRGB::Black;
        }
        for (size_t i = 0; i < LEDS_PER_EDGE; i++) {
            led_array[current.strip][current.index + i] = CRGB::Blue;
        }
        previous = current;

        current_edge_index = (current_edge_index + 1) % EDGE_COUNT;
        current            = coordinates[current_edge_index];
    }

  private:
    // Which edge of the dodecahedron? See .graphml file for enumeration
    size_t current_edge_index = 0;

    IndexPair previous = {};
    IndexPair current  = {};

    IndexPair coordinates[EDGE_COUNT] = {};

    Dodecahedron dod;
};

#endif// DODECA_TEST_PATTERN_HPP
