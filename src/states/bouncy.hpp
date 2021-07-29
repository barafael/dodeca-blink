#pragma once

#include <Arduino.h>

#include <FastLED.h>

#include <cstddef>

#include "command.hpp"
#include "constants.hpp"
#include "dodeca_state.hpp"
#include "led_data.hpp"

#include <array>

constexpr size_t BallCount = 3;

class DodecaBouncy : public DodecaState {
    public:
    DodecaBouncy(String name) : DodecaState(name) {
        for (int i = 0; i < BallCount; i++) {
            ClockTimeSinceLastBounce[i] = millis();
            Height[i]                   = StartHeight;
            Position[i]                 = 0;
            ImpactVelocity[i]           = ImpactVelocityStart;
            TimeSinceLastBounce[i]      = 0;
            Dampening[i]                = 0.90 - float(i) / pow(BallCount, 2);
            Color[i]                    = CRGB(random8(), random8(), random8());
        }
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
        BouncingBalls();

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
    void BouncingBalls() {
        for (int i = 0; i < BallCount; i++) {
            TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];

            Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) +
                        ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

            if (Height[i] < 0) {
                Height[i]                   = 0;
                ImpactVelocity[i]           = Dampening[i] * ImpactVelocity[i];
                ClockTimeSinceLastBounce[i] = millis();

                if (ImpactVelocity[i] < 0.01) {
                    ImpactVelocity[i] = ImpactVelocityStart;
                }

                Strip[i] = random(STRIP_COUNT);
                Color[i] = CRGB(random8(), random8(), random8());
            }
            Position[i] = round(Height[i] * (LEDS_PER_STRIP - 1) / StartHeight);
        }

        for (int i = 0; i < BallCount; i++) { led_array[Strip[i]][Position[i]] = Color[i]; }

        FastLED.show();
        FastLED.clear();
    }

    float Gravity     = -9.81;
    int   StartHeight = 1;

    std::array<size_t, BallCount> Strip = {};

    CRGB  Color[BallCount] = {};
    float Height[BallCount];
    float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);
    float ImpactVelocity[BallCount];
    float TimeSinceLastBounce[BallCount];
    int   Position[BallCount];
    long  ClockTimeSinceLastBounce[BallCount];
    float Dampening[BallCount];

    bool blur = false;

    size_t call_counter = 0;

    const size_t SKIP_COUNTER = 2;
};
