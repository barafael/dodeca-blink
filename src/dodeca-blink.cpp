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

#include "states/dodeca_color_sparkle.hpp"
#include "states/dodeca_fade_palette.hpp"
#include "states/dodeca_twinkle.hpp"
#include "states/dodeca_test_pattern.hpp"
#include "states/blink_states.hpp"
#include "states/snake.hpp"

#include "firmware_update/updater.hpp"

#include "constants.hpp"
#include "pins.hpp"
#include "firmware_revision.hpp"
#include "led_data.hpp"
#include "command.hpp"
#include "color_provider/random_color_provider.hpp"
#include "color_provider/solid_color_provider.hpp"
#include "color_provider/palette_color_provider.hpp"
#include "palettes.hpp"
#include "lamp_settings.hpp"
#include "dodeca_path_table.hpp"

#ifdef ENABLE_BLUETOOTH
BluetoothSerial SerialBT;
#endif

RandomColorProvider random_color;
SolidColorProvider blue_color(rgb2hsv_approximate(CRGB::Blue));
SolidColorProvider white_color(rgb2hsv_approximate(CRGB::White));
CRGBPalette16 palettes[] = {
sunset_palette,
es_emerald_dragon_08_gp,
es_ocean_breeze_001_gp,
es_rivendell_01_gp,
};
PaletteColorProvider palette_color(palettes, 4);

DodecaFadePalette fading("Fading");
DodecaTestPattern test_pattern("Test Pattern", LEDS_PER_EDGE);
DodecaColorSparkle sparkling("Sparkling");
DodecaTwinkle random_blink("Random blink", random_color);
DodecaTwinkle palette_blink("Palette blink", palette_color);
DodecaTwinkle blue_blink("Blue blink", blue_color);
DodecaTwinkle white_blink("White blink", white_color);

Preferences persistent_state;

LampSettings settings(persistent_state);

Command command = Command::NONE;

uint8_t actual_brightness;

BlinkStateMachine states(&fading);

DodecaPathTable table;

void setup() {
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(1000);

    Serial.begin(115200);

    UpdateStatus update_status = attempt_update();
    switch (update_status) {
        case UpdateStatus::NO_CARD:
        case UpdateStatus::FILE_ERROR:
            Serial.println("Continuing without update.");
            break;
        case UpdateStatus::INSUFFICIENT_SPACE:
        case UpdateStatus::UPDATE_ERROR:
            Serial.println("Error occurred during update. Continuing, here be dragons.");
            break;
        case UpdateStatus::UPDATE_OK:
            Serial.println("Update OK!");
            ESP.restart();
            break;
    }

    // TODO move those to lamp settings class without breaking persistence
    persistent_state.begin("settings", false);

    settings.set_index(persistent_state.getUInt("state-index", 0));
    settings.set_brightness(persistent_state.getUChar("brightness", INITIAL_BRIGHTNESS));

    actual_brightness = settings.get_brightness();

#ifdef ENABLE_BLUETOOTH
    String id = "Dodeca Lamp BlueTooth control";
    SerialBT.begin(id);
#endif

    random16_add_entropy(static_cast<uint16_t>(random(19885678)));

    states.add_state(&test_pattern);
    states.add_state(&sparkling);
    states.add_state(&random_blink);
    states.add_state(&palette_blink);
    states.add_state(&blue_blink);
    states.add_state(&white_blink);

    states.try_set_index(settings.get_index());

    FastLED.addLeds<LED_TYPE, DATA_PIN_1, GRB>(led_array[0], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_2, GRB>(led_array[1], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_3, GRB>(led_array[2], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_4, GRB>(led_array[3], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_5, GRB>(led_array[4], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_6, GRB>(led_array[5], LEDS_PER_STRIP);

    FastLED.setBrightness(settings.get_brightness());

    FastLED.setMaxPowerInVoltsAndMilliamps(5, TOTAL_MILLIAMPS);
}

void loop() {
    uint8_t val = 0;
#ifdef ENABLE_BLUETOOTH
    if (SerialBT.available()) {
        val = (uint8_t) SerialBT.read();
        if (is_command(val)) {
            command = (Command) val;
        }
    }
#endif // ENABLE_BLUETOOTH

    if (val >= 'A' && val <= 'Z') {
        size_t index = val - 65;
        Serial.println(index);
        if (states.try_set_index(index)) {
            SerialBT.println("Successfully set state.");
        } else {
            SerialBT.println("Failed to set state.");
        }
        FastLED.clear();
    }

    switch (command) {
        case Command::NONE:
            break;
        case Command::INCREASE_BRIGHTNESS: {
            if (settings.get_brightness() < BRIGHTNESS_STEP) {
                settings.set_brightness(settings.get_brightness() + BRIGHTNESS_TINY_STEP);
                settings.serialize();
#ifdef ENABLE_BLUETOOTH
                SerialBT.print("Brightness: ");
                SerialBT.println(settings.get_brightness());
#endif
            } else if (settings.get_brightness() + BRIGHTNESS_STEP < 256) {
                settings.set_brightness(settings.get_brightness() + BRIGHTNESS_STEP);
                settings.serialize();
#ifdef ENABLE_BLUETOOTH
                SerialBT.print("Brightness: ");
                SerialBT.println(settings.get_brightness());
#endif
            } else {
#ifdef ENABLE_BLUETOOTH
                SerialBT.println("max brightness");
#endif
            }
        }
            break;
        case Command::DECREASE_BRIGHTNESS: {
            if (settings.get_brightness() <= BRIGHTNESS_STEP) {
                uint8_t brightness = settings.get_brightness();
                if (BRIGHTNESS_TINY_STEP > brightness) {
                    brightness = 0;
                } else {
                    brightness -= BRIGHTNESS_TINY_STEP;
                }
                settings.set_brightness(brightness);
                settings.serialize();
#ifdef ENABLE_BLUETOOTH
                SerialBT.print("Brightness: ");
                SerialBT.println(settings.get_brightness());
#endif
            } else {
                settings.set_brightness(settings.get_brightness() - BRIGHTNESS_STEP);
                settings.serialize();
#ifdef ENABLE_BLUETOOTH
                SerialBT.print("Brightness: ");
                SerialBT.println(settings.get_brightness());
#endif
            }
        }
            break;
        case Command::NEXT_STATE: {
            states.go_to_next();
            settings.set_index(states.get_active_index());
            settings.serialize();
            FastLED.clear();
#ifdef ENABLE_BLUETOOTH
            SerialBT.print("State: ");
            SerialBT.println(*states.get_active_state()->get_name());
#endif
        }
            break;
        case Command::PREVIOUS_STATE: {
            states.go_to_previous();
            settings.set_index(states.get_active_index());
            settings.serialize();
            FastLED.clear();
#ifdef ENABLE_BLUETOOTH
            SerialBT.print("State: ");
            SerialBT.println(*states.get_active_state()->get_name());
#endif
        }
            break;
        case Command::ACTION_A:
            states.get_active_state()->do_thing(Command::ACTION_A);
            break;
        case Command::ACTION_B:
            states.get_active_state()->do_thing(Command::ACTION_B);
            break;
        case Command::ACTION_C:
            states.get_active_state()->do_thing(Command::ACTION_C);
            break;

        case Command::GET_COMMAND_NAMES:
            SerialBT.print("Commands: ");
            SerialBT.print(states.get_active_state()->get_thing_name(Command::ACTION_A));
            SerialBT.print(";");
            SerialBT.print(states.get_active_state()->get_thing_name(Command::ACTION_B));
            SerialBT.print(";");
            SerialBT.print(states.get_active_state()->get_thing_name(Command::ACTION_C));
            SerialBT.println(";");
            break;
        case Command::GET_STATE_LIST:
            SerialBT.print("States: ");
            for (DodecaState *state: states) {
                SerialBT.print(*state->get_name());
                SerialBT.print("; ");
            }
            SerialBT.println();
            break;
        case Command::GET_FIRMWARE_REVISION:
            SerialBT.print("Revision: ");
            SerialBT.print(REVISION.major);
            SerialBT.print(";");
            SerialBT.print(REVISION.minor);
            SerialBT.print(";");
            SerialBT.println(REVISION.patch);
    }

    // Reset command, which has been applied
    command = Command::NONE;

    EVERY_N_MILLISECONDS(20) {
        states.get_active_state()->advance();
    }

    EVERY_N_MILLISECONDS(FADE_INTERVAL_MS) {
        if (actual_brightness < settings.get_brightness()) {
            actual_brightness += FADE_STEP;
        } else if (actual_brightness > settings.get_brightness()) {
            actual_brightness -= FADE_STEP;
        }
    }

    FastLED.setBrightness(actual_brightness);
    FastLED.show();
}
