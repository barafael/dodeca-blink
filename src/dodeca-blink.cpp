#include "constants.hpp"
#include "dodeca_fade_palette.hpp"
#include "dodeca_random_blink.hpp"
#include "dodeca_test_pattern.hpp"
#include "dodecahedron.hpp"
#include "leds.hpp"

#include <Arduino.h>
#include <FastLED.h>

DodecaRandomBlink random_blink;
DodecaFadePalette fading;
DodecaTestPattern test_pattern;

void setup() {
    Serial.begin(115200);

    random16_add_entropy(random(19885678));
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(1000);

    FastLED.addLeds<WS2811, DATA_PIN_1, GRB>(led_array[0], NUM_LEDS);
    FastLED.addLeds<WS2811, DATA_PIN_2, GRB>(led_array[1], NUM_LEDS);
    FastLED.addLeds<WS2811, DATA_PIN_3, GRB>(led_array[2], NUM_LEDS);
    FastLED.addLeds<WS2811, DATA_PIN_4, GRB>(led_array[3], NUM_LEDS);
    FastLED.addLeds<WS2811, DATA_PIN_5, GRB>(led_array[4], NUM_LEDS);
    FastLED.addLeds<WS2811, DATA_PIN_6, GRB>(led_array[5], NUM_LEDS);

    FastLED.setBrightness(55);
    test_pattern.advance();
}

void loop() {
//#define DODECA_FADE_PALETTE
#define DODECA_TEST_PATTERN

#ifdef RANDOM_BLINK
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
#endif
    FastLED.show();
}
