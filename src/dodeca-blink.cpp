#include <Arduino.h>
#include <FastLED.h>

#include "dodeca_fade_palette.hpp"
#include "dodeca_random_blink.hpp"
#include "dodeca_test_pattern.hpp"
#include "dodeca_color_sparkle.hpp"
#include "dodecahedron.hpp"

#include "constants.hpp"
#include "leds.hpp"

constexpr size_t LEDS_PER_EDGE = 10;

DodecaRandomBlink random_blink;
DodecaFadePalette fading;
DodecaTestPattern test_pattern(LEDS_PER_EDGE);
DodecaColorSparkle sparkling;

void setup() {
    Serial.begin(115200);

    random16_add_entropy(random(19885678));
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(1000);

    FastLED.addLeds<WS2811, DATA_PIN_1, GRB>(led_array[0], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_2, GRB>(led_array[1], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_3, GRB>(led_array[2], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_4, GRB>(led_array[3], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_5, GRB>(led_array[4], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_6, GRB>(led_array[5], LEDS_PER_STRIP);

    FastLED.setBrightness(25);
}

void loop() {
//#define DODECA_FADE_PALETTE
#define DODECA_TEST_PATTERN
//#define DODECA_COLOR_SPARKLE
//#define DODECA_RANDOM_BLINK

#ifdef DODECA_RANDOM_BLINK
    EVERY_N_MILLISECONDS(20) {
        random_blink.advance();
    }
#elif defined(DODECA_TEST_PATTERN)
    EVERY_N_MILLISECONDS(500) {
        test_pattern.advance();
    }
#elif defined(DODECA_FADE_PALETTE)
    EVERY_N_MILLISECONDS(20) {
        fading.advance();
    }
#elif defined(DODECA_COLOR_SPARKLE)
    sparkling.advance();
#endif
    FastLED.show();
}
