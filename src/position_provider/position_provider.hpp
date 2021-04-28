#pragma once

#include <cstddef>

#include "producer.hpp"
#include "states/does_things.hpp"
#include "dodeca_position.hpp"

#include <FastLED.h>

class PositionProvider: public Producer<DodecaPosition>, public ThingDoer {

};