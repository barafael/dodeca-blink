#pragma once

#include "Arduino.h"
#include "FastLED.h"
#include "constants.hpp"
#include "dodeca_state.hpp"
#include "dodecahedron.hpp"
#include "index_pair.hpp"
#include "led_data.hpp"

#include <array>
#include <cstddef>

class DodecaTestPattern : public DodecaState {
    public:
    DodecaTestPattern(String name, const size_t leds_per_edge) : DodecaState(name), LEDS_PER_EDGE(leds_per_edge) {
        coordinates[0]  = { 0, 0 * LEDS_PER_EDGE };
        coordinates[5]  = { 0, 1 * LEDS_PER_EDGE };
        coordinates[19] = { 0, 2 * LEDS_PER_EDGE };
        coordinates[24] = { 0, 3 * LEDS_PER_EDGE };
        coordinates[29] = { 0, 4 * LEDS_PER_EDGE };

        coordinates[1]  = { 1, 0 * LEDS_PER_EDGE };
        coordinates[6]  = { 1, 1 * LEDS_PER_EDGE };
        coordinates[15] = { 1, 2 * LEDS_PER_EDGE };
        coordinates[20] = { 1, 3 * LEDS_PER_EDGE };
        coordinates[25] = { 1, 4 * LEDS_PER_EDGE };

        coordinates[2]  = { 2, 0 * LEDS_PER_EDGE };
        coordinates[7]  = { 2, 1 * LEDS_PER_EDGE };
        coordinates[16] = { 2, 2 * LEDS_PER_EDGE };
        coordinates[21] = { 2, 3 * LEDS_PER_EDGE };
        coordinates[26] = { 2, 4 * LEDS_PER_EDGE };

        coordinates[3]  = { 3, 0 * LEDS_PER_EDGE };
        coordinates[8]  = { 3, 1 * LEDS_PER_EDGE };
        coordinates[17] = { 3, 2 * LEDS_PER_EDGE };
        coordinates[22] = { 3, 3 * LEDS_PER_EDGE };
        coordinates[27] = { 3, 4 * LEDS_PER_EDGE };

        coordinates[4]  = { 4, 0 * LEDS_PER_EDGE };
        coordinates[9]  = { 4, 1 * LEDS_PER_EDGE };
        coordinates[18] = { 4, 2 * LEDS_PER_EDGE };
        coordinates[23] = { 4, 3 * LEDS_PER_EDGE };
        coordinates[28] = { 4, 4 * LEDS_PER_EDGE };

        coordinates[10] = { 5, 0 * LEDS_PER_EDGE };
        coordinates[11] = { 5, 1 * LEDS_PER_EDGE };
        coordinates[12] = { 5, 2 * LEDS_PER_EDGE };
        coordinates[13] = { 5, 3 * LEDS_PER_EDGE };
        coordinates[14] = { 5, 4 * LEDS_PER_EDGE };
    }

    bool do_thing(Command id) override {
        switch (id) {
            case Command::ACTION_A: call_counter = SKIP_COUNTER; return true;
            default: return false;
        }
    }

    char const *const get_thing_name(Command id) override {
        if (id == Command::ACTION_A) {
            return "Advance";
        }
        return "";
    }

    void advance() override {
        if (call_counter < SKIP_COUNTER) {
            call_counter += 1;
            return;
        } else {
            call_counter = 0;
        }

        // Reset old LEDs
        for (size_t i = 0; i < LEDS_PER_EDGE; i++) { led_array[previous.strip()][previous.index() + i] = CRGB::Black; }

        CRGB current_color = color[current.strip()];
        for (size_t i = 0; i < LEDS_PER_EDGE; i++) { led_array[current.strip()][current.index() + i] = current_color; }
        previous = current;

        current_edge_index = (current_edge_index + 1) % NUM_EDGES;
        current            = coordinates[current_edge_index];
    }

    private:
    // Which edge of the dodecahedron? See .graphml file for enumeration
    size_t current_edge_index = 0;

    IndexPair previous = {};
    IndexPair current  = {};

    IndexPair coordinates[NUM_EDGES] = {};

    CRGB color[6] = { CRGB::DarkGreen, CRGB::DarkOrange, CRGB::White, CRGB::Brown, CRGB::Blue, CRGB::Yellow };

    const size_t LEDS_PER_EDGE;

    size_t call_counter = 0;

    const size_t SKIP_COUNTER = 100;
};
