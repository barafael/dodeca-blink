#pragma once

#include "Arduino.h"
#include "FastLED.h"

#include "constants.hpp"
#include "led_data.hpp"
#include "pins.hpp"

#include "states/dodeca_test_stripes.hpp"

hw_timer_t *timer = NULL;

DodecaTestStripes progress_bar("Progress bar", LEDS_PER_EDGE);

void IRAM_ATTR on_timer() {
    progress_bar.advance();
}

void init_leds() {
    FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDERING>(led_array[0], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDERING>(led_array[1], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_3, COLOR_ORDERING>(led_array[2], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_4, COLOR_ORDERING>(led_array[3], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_5, COLOR_ORDERING>(led_array[4], LEDS_PER_STRIP);
    FastLED.addLeds<LED_TYPE, DATA_PIN_6, COLOR_ORDERING>(led_array[5], LEDS_PER_STRIP);

    FastLED.setBrightness(20);
}

void start_timer() {
    /* Use 1st timer of 4 */
    /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
    timer = timerBegin(0, 80, true);

    /* Attach on_timer function to our timer */
    timerAttachInterrupt(timer, &on_timer, true);

    /* Set alarm to call on_timer function every second
       1 tick is 1us => 1 second is 1000000us
    */
    /* Repeat the alarm (third parameter) */
    timerAlarmWrite(timer, 1000000, true);

    /* Start an alarm */
    timerAlarmEnable(timer);
}

void stop_timer() {
    timerAlarmDisable(timer);
    FastLED.clear();
}
