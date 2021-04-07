#pragma once

#include "FastLED.h"
#include "constants.hpp"
#include "led_data.hpp"
#include "dodeca_state.hpp"
#include "does_things.hpp"

#include <cstddef>

DEFINE_GRADIENT_PALETTE(greenblue_gp) {
        0, 0, 194, 255,//light blue
        46, 3, 0, 246,//dark blue
        176, 55, 222, 70, //bright green
        255, 0, 194, 255 //light blue
};

DEFINE_GRADIENT_PALETTE(orangepink_gp) {
        0, 255, 100, 0,  //orange
        90, 255, 0, 255,//magenta
        150, 255, 100, 0,  //orange
        255, 255, 100, 0   //orange
};

DEFINE_GRADIENT_PALETTE(browngreen_gp) {
        0, 6, 255, 0,  //green
        71, 0, 255, 153,//bluegreen
        122, 200, 200, 200,//gray
        181, 110, 61, 6,  //brown
        255, 6, 255, 0   //green
};

DEFINE_GRADIENT_PALETTE(yellowred_gp) {
        224, 180, 1, 88,//yellow
        212, 145, 11, 83,//beige
        235, 121, 0, 92,    //orange
        212, 76, 11, 83,   //brick
        245, 44, 12, 96   //zinnober
};

CRGBPalette16 current_palette(greenblue_gp);
CRGBPalette16 target_palette(orangepink_gp);

class DodecaColorSparkle : public DodecaState {
public:
    explicit DodecaColorSparkle(String name) : DodecaState(name) {
        for (size_t i = 0; i < LEDS_PER_STRIP; i++) {
            color_index[i] = random8();
        }
    }

    bool do_thing(Command id) override {
        if (id == Command::ACTION_A) {
            blur = !blur;
            return true;
        }
        return false;
    }

    void advance() override {
        for (size_t i = 0; i < STRIP_COUNT; i++) {
            for (size_t j = 0; j < LEDS_PER_STRIP; j++) {
                led_array[i][j] = ColorFromPalette(current_palette, color_index[j]);
            }
        }

        nblendPaletteTowardPalette(current_palette, target_palette, 10);

        switch (which_palette) {
            case 0:
                target_palette = orangepink_gp;
                break;
            case 1:
                target_palette = browngreen_gp;
                break;
            case 2:
                target_palette = greenblue_gp;
                break;
            case 3:
                target_palette = yellowred_gp;
                break;
            default:
                target_palette = orangepink_gp;
        }

        EVERY_N_SECONDS(5) {
            which_palette = (which_palette + 1) % 4;
        }

        EVERY_N_MILLISECONDS(10) {
            for (size_t i = 0; i < LEDS_PER_STRIP; i++) {
                color_index[i]++;
            }
        }

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

private:
    uint8_t color_index[LEDS_PER_STRIP] = {};
    size_t which_palette = 0;
    bool blur = false;
};