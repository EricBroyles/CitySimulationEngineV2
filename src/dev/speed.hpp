/*
@Speed
@brief
* convert mph -> cell/step
* conversion: (mile/hour) (feet/mile) (cell/feet) (hour/sec) (sec/step)
*/
#pragma once

struct Speed {
    static constexpr float FEET_PER_MILE = (5280.0f/1.0f);
    static constexpr float HOUR_PER_SEC  = (1.0f/3600.0f);
    float val; // cell per step
    constexpr Speed(): val(0.0f) {}
    constexpr Speed(float speed): val(speed) {}
    constexpr Speed(int mph, int sec_per_step, int feet_per_cell): val(mph * (FEET_PER_MILE / feet_per_cell) * HOUR_PER_SEC * sec_per_step) {}
    //constexpr Speed(World& world, int mph) { val = mph * (1.0f/3600.0f) * world.step_duration * 5280.0f * 1.0f/world.cell_width; }
};
