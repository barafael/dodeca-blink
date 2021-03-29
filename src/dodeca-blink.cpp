#include <Arduino.h>
#include <FastLED.h>
#include <Preferences.h>

#define ENABLE_BLUETOOTH
#ifdef ENABLE_BLUETOOTH
    #include <BluetoothSerial.h>
    #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
        #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
    #endif
#endif

#include "constants.hpp"
#include "pins.hpp"
#include "dodeca_color_sparkle.hpp"
#include "dodeca_fade_palette.hpp"
#include "dodeca_random_blink.hpp"
#include "dodeca_test_pattern.hpp"
#include "dodecahedron.hpp"
#include "leds.hpp"
#include "command.hpp"

#ifdef ENABLE_BLUETOOTH
BluetoothSerial SerialBT;
#endif

DodecaRandomBlink random_blink;
DodecaFadePalette fading;
DodecaTestPattern test_pattern(LEDS_PER_EDGE);
DodecaColorSparkle sparkling;

Preferences persistent_state;

Command command = Command::NONE;

class LampSettings {
  public:
    LampState lamp_state = LampState::FADE_PALETTE_STATE;
    uint8_t brightness = INITIAL_BRIGHTNESS;
};

LampSettings settings;

uint8_t actual_brightness;

void setup() {
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(1000);

    Serial.begin(115200);

    persistent_state.begin("settings", false);
    settings.lamp_state = (LampState)persistent_state.getUInt("lamp-state", (uint32_t)LampState::FADE_PALETTE_STATE);
    settings.brightness = persistent_state.getUChar("brightness", INITIAL_BRIGHTNESS);
    actual_brightness = settings.brightness;

    char ssid1[15];
    char ssid2[15];

    uint64_t chipid = ESP.getEfuseMac();
    uint16_t chip = (uint16_t)(chipid >> 32);

    // TODO use chip id for id string?
    snprintf(ssid1, 15, "%04X", chip);
    snprintf(ssid2, 15, "%08X", (uint32_t)chipid);

    #ifdef ENABLE_BLUETOOTH
    String id = "Dodeca lamp BlueTooth control";
    SerialBT.begin(id);
    #endif

    random16_add_entropy(random(19885678));

    FastLED.addLeds<WS2811, DATA_PIN_1, GRB>(led_array[0], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_2, GRB>(led_array[1], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_3, GRB>(led_array[2], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_4, GRB>(led_array[3], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_5, GRB>(led_array[4], LEDS_PER_STRIP);
    FastLED.addLeds<WS2811, DATA_PIN_6, GRB>(led_array[5], LEDS_PER_STRIP);

    FastLED.setBrightness(settings.brightness);
}

void loop() {
    #ifdef ENABLE_BLUETOOTH
    if (SerialBT.available()) {
        uint32_t val = SerialBT.read();
        if (is_state(val)) {
            settings.lamp_state = (LampState)val;
            persistent_state.putUInt("lamp-state", val);
            FastLED.clear();
        } else if (is_command(val)) {
            command = (Command)val;
        }
    }
    #endif // ENABLE_BLUETOOTH

    switch (command) {
        case Command::NONE:
        break;
        case Command::INCREASE_BRIGHTNESS: {
            if (settings.brightness + BRIGHTNESS_STEP < 256) {
                settings.brightness += BRIGHTNESS_STEP;
                #ifdef ENABLE_BLUETOOTH
                SerialBT.println(settings.brightness);
                #endif
                persistent_state.putUChar("brightness", settings.brightness);
            } else {
                #ifdef ENABLE_BLUETOOTH
                SerialBT.println("max brightness");
                #endif
            }
        }
        break;
        case Command::DECREASE_BRIGHTNESS: {
            if (settings.brightness > BRIGHTNESS_STEP) {
                settings.brightness -= BRIGHTNESS_STEP;
                #ifdef ENABLE_BLUETOOTH
                SerialBT.println(settings.brightness);
                #endif
                persistent_state.putUChar("brightness", settings.brightness);
            } else {
                #ifdef ENABLE_BLUETOOTH
                SerialBT.println("min brightness");
                #endif
            }
        }
        break;
        case Command::NEXT_STATE: {
            LampState next = next_state(settings.lamp_state);
            settings.lamp_state = next;
            persistent_state.putUInt("lamp-state", (int)next);
            FastLED.clear();
        }
        break;
        case Command::PREVIOUS_STATE: {
            LampState previous = previous_state(settings.lamp_state);
            settings.lamp_state = previous;
            persistent_state.putUInt("lamp-state", (int)previous);
            FastLED.clear();
        }
        break;
        case Command::ACTION_A:
        case Command::ACTION_B:
        case Command::ACTION_C:
        break;
    }
    command = Command::NONE;

    switch (settings.lamp_state) {
        case LampState::FADE_PALETTE_STATE: {
            EVERY_N_MILLISECONDS(20) {
                fading.advance();
            }
        }
        break;
        case LampState::TEST_PATTERN_STATE: {
            EVERY_N_MILLISECONDS(500) {
                test_pattern.advance();
            }
        }
        break;
        case LampState::COLOR_SPARKLE_STATE: {
            sparkling.advance();
        }
        break;
        case LampState::RANDOM_BLINK_STATE: {
            EVERY_N_MILLISECONDS(20) {
                random_blink.advance();
            }
        }
        break;
    }

    EVERY_N_MILLISECONDS(FADE_INTERVAL_MS) {
        if (actual_brightness < settings.brightness) {
            actual_brightness += FADE_STEP;
        } else if (actual_brightness > settings.brightness) {
            actual_brightness -= FADE_STEP;
        }
    }
    FastLED.setBrightness(actual_brightness);
    FastLED.show();
}
