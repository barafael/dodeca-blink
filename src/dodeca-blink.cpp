#include <Arduino.h>
#include <FastLED.h>
#include <BluetoothSerial.h>

#include "constants.hpp"
#include "dodeca_color_sparkle.hpp"
#include "dodeca_fade_palette.hpp"
#include "dodeca_random_blink.hpp"
#include "dodeca_test_pattern.hpp"
#include "dodecahedron.hpp"
#include "leds.hpp"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

constexpr size_t LEDS_PER_EDGE = 20;

DodecaRandomBlink random_blink;
DodecaFadePalette fading;
DodecaTestPattern test_pattern(LEDS_PER_EDGE);
DodecaColorSparkle sparkling;

void setup() {
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(1000);

    Serial.begin(115200);

    SerialBT.begin("Dodeca lamp BT control");

    random16_add_entropy(random(19885678));

    FastLED.addLeds<WS2811, DATA_PIN_1, GRB>(led_array[0], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_2, GRB>(led_array[1], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_3, GRB>(led_array[2], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_4, GRB>(led_array[3], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_5, GRB>(led_array[4], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_6, GRB>(led_array[5], LEDS_PER_STRIP);

    FastLED.setBrightness(128);
}

enum class Command : uint32_t
{
    NONE = 0,

    INCREASE_BRIGHTNESS = 'i',
    DECREASE_BRIGHTNESS = 'd',

    ACTION_A = 'a',
    ACTION_B = 'b',
    ACTION_C = 'c',
};

bool is_command(int val) {
    return val == 'i' || val == 'd' || val == 'a' || val == 'b' || val == 'c';
}

enum class State : uint32_t
{
    FADE_PALETTE_STATE = 'P',
    TEST_PATTERN_STATE = 'T',
    COLOR_SPARKLE_STATE = 'S',
    RANDOM_BLINK_STATE = 'R',
};

bool is_state(int val) {
    return val == 'P' || val == 'T' || val == 'S' || val == 'R';
}

State state = State::FADE_PALETTE_STATE;
Command command = Command::NONE;

int brightness = INITIAL_BRIGHTNESS;

void loop() {
    if (Serial.available()) {
        SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) {
        int val = SerialBT.read();
        if (is_state(val)) {
            state   = (State)val;
            FastLED.clear();
        } else if (is_command(val)) {
            command = (Command)val;
        }
        Serial.write(val);
    }

    switch (command) {
        case Command::NONE:
        break;
        case Command::INCREASE_BRIGHTNESS: {
            if (brightness + BRIGHTNESS_STEP < 256) {
                brightness += BRIGHTNESS_STEP;
            }
        }
        break;
        case Command::DECREASE_BRIGHTNESS: {
            if (brightness > BRIGHTNESS_STEP) {
                brightness -= BRIGHTNESS_STEP;
            }
        }
        break;
        case Command::ACTION_A:
        case Command::ACTION_B:
        case Command::ACTION_C:
        break;
    }
    command = Command::NONE;

    switch (state) {
        case State::FADE_PALETTE_STATE: {
            EVERY_N_MILLISECONDS(20) {
                fading.advance();
            }
        }
        break;
        case State::TEST_PATTERN_STATE: {
            EVERY_N_MILLISECONDS(500) {
                test_pattern.advance();
            }
        }
        break;
        case State::COLOR_SPARKLE_STATE: {
            sparkling.advance();
        }
        break;
        case State::RANDOM_BLINK_STATE: {
            EVERY_N_MILLISECONDS(20) {
                random_blink.advance();
            }
        }
        break;
    }

    // TODO if bored: animate brightness change :)
    FastLED.setBrightness(brightness);
    FastLED.show();
}
