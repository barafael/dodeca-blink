#pragma once

#include <Arduino.h>

#include <FastLED.h>

#include <cstddef>

#include "command.hpp"
#include "constants.hpp"
#include "dodeca_state.hpp"
#include "led_data.hpp"

class DodecaFire : public DodecaState {
    public:
    DodecaFire(String name, uint8_t cooling, uint8_t sparking)
        : DodecaState(name), cooling(cooling), sparking(sparking) {
    }

    bool do_thing(Command id) override {
        switch (id) {
            case Command::ACTION_A: blur = !blur; return true;
            case Command::ACTION_B: return false;
            case Command::ACTION_C: return false;

            default: return false;
        }
    }

    char const *const get_thing_name(Command id) override {
        switch (id) {
            case Command::ACTION_A: return "Toggle blur";
            default: return "";
        }
    }

    void advance() override {
        if (call_counter < SKIP_COUNTER) {
            call_counter += 1;
            return;
        } else {
            call_counter = 0;
        }

        fire(cooling, sparking);

        if (blur) {
            uint8_t blurAmount = dim8_raw(beatsin8(3, 15, LEDS_PER_STRIP));

            blur1d(led_array[0], LEDS_PER_STRIP, blurAmount);
            blur1d(led_array[1], LEDS_PER_STRIP, blurAmount);
            blur1d(led_array[2], LEDS_PER_STRIP, blurAmount);
            blur1d(led_array[3], LEDS_PER_STRIP, blurAmount);
            blur1d(led_array[4], LEDS_PER_STRIP, blurAmount);
            blur1d(led_array[5], LEDS_PER_STRIP, blurAmount);
        }
    }

    void fire(int cooling, int sparking) {
        static byte heat[LEDS_PER_STRIP];

        int cooldown;

        // Step 1.  Cool down every cell a little
        for (int i = 0; i < LEDS_PER_STRIP; i++) {
            cooldown = random(0, ((cooling * 10) / LEDS_PER_STRIP) + 2);

            if (cooldown > heat[i]) {
                heat[i] = 0;
            } else {
                heat[i] = heat[i] - cooldown;
            }
        }

        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for (int k = LEDS_PER_STRIP - 1; k >= 2; k--) { heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3; }

        // Step 3.  Randomly ignite new 'sparks' near the bottom
        if (random(255) < sparking) {
            int y   = random(7);
            heat[y] = heat[y] + random(160, 255);
            //heat[y] = random(160,255);
        }

        // Step 4.  Convert heat to LED colors
        for (int j = 0; j < LEDS_PER_STRIP; j++) { set_pixel_heat_color(j, heat[j]); }

        FastLED.show();
    }

    private:
    void set_pixel_heat_color(int pixel, byte temperature) {
        // Scale 'heat' down from 0-255 to 0-191
        byte t192 = round((temperature / 255.0) * 191);

        // calculate ramp up from
        byte heatramp = t192 & 0x3F; // 0..63
        heatramp <<= 2; // scale up to 0..252

        // figure out which third of the spectrum we're in:
        if (t192 > 0x80) { // hottest
            led_array[0][pixel] = CRGB(255, 255, heatramp);
            led_array[1][pixel] = CRGB(255, 255, heatramp);
            led_array[2][pixel] = CRGB(255, 255, heatramp);
            led_array[3][pixel] = CRGB(255, 255, heatramp);
            led_array[4][pixel] = CRGB(255, 255, heatramp);
        } else if (t192 > 0x40) { // middle
            led_array[0][pixel] = CRGB(255, heatramp, 0);
            led_array[1][pixel] = CRGB(255, heatramp, 0);
            led_array[2][pixel] = CRGB(255, heatramp, 0);
            led_array[3][pixel] = CRGB(255, heatramp, 0);
            led_array[4][pixel] = CRGB(255, heatramp, 0);
        } else { // coolest
            led_array[0][pixel] = CRGB(heatramp, 0, 0);
            led_array[1][pixel] = CRGB(heatramp, 0, 0);
            led_array[2][pixel] = CRGB(heatramp, 0, 0);
            led_array[3][pixel] = CRGB(heatramp, 0, 0);
            led_array[4][pixel] = CRGB(heatramp, 0, 0);
        }
    }

    uint8_t cooling;
    uint8_t sparking;

    bool blur = false;

    size_t call_counter = 0;

    const size_t SKIP_COUNTER = 2;
};
