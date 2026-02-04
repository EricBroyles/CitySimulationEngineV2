/*
@Speed
@brief
* convert mph -> cell/step
* conversion: (mile/hour) (feet/mile) (cell/feet) (hour/sec) (sec/step)
*/
#pragma once
#include <godot_cpp/classes/image.hpp>
#include "cell.hpp"

using namespace godot;

struct MilesPerHour {
    static constexpr Image::Format IMAGE_FORMAT = Image::FORMAT_R8;
    uint8_t val;
    constexpr MilesPerHour(): val(0) {}
    constexpr MilesPerHour(uint8_t mph): val(mph) {}
};

using MPH = MilesPerHour;

struct Speed {
    static constexpr float FEET_PER_MILE = (5280.0f/1.0f);
    static constexpr float HOUR_PER_SEC  = (1.0f/3600.0f);
    float val; // cell per step
    constexpr Speed(): val(0.0f) {}
    constexpr Speed(float speed): val(speed) {}
    constexpr Speed(MPH mph, int sec_per_step, int feet_per_cell): val(mph.val * (FEET_PER_MILE / feet_per_cell) * HOUR_PER_SEC * sec_per_step) {}
    constexpr bool operator==(const Speed speed) const { return val == speed.val; }
    constexpr bool operator!=(const Speed speed) const { return val != speed.val; }
};
