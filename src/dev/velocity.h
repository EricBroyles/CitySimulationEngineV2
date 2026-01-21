#pragma once

#include <cstdint>

class Speed {
// (mi / hour) (1 hour / 60 min) (1 min / 60 sec) (sec_per_step) (5280 ft / 1 mi) (1/feet_per_cell)
public:
    float val;
    Speed(): val(0) {}
    Speed(float speed): val(speed) {}
    Speed(int sec_per_step, int feet_per_cell, int mph) { val = mph * (1.0f/3600.0f) * sec_per_step * 5280.0f * 1.0f/feet_per_cell; }
    Speed(World& world, int mph) { val = mph * (1.0f/3600.0f) * world.step_duration * 5280.0f * 1.0f/world.cell_width; }
};

class Direction {
private:
    uint8_t val;

public: 
    static constexpr uint8_t NONE = 0b00000000;
    static constexpr uint8_t E    = 0b00000001;
    static constexpr uint8_t NE   = 0b00000010;
    static constexpr uint8_t N    = 0b00000100;
    static constexpr uint8_t NW   = 0b00001000;
    static constexpr uint8_t W    = 0b00010000;
    static constexpr uint8_t SW   = 0b00100000;
    static constexpr uint8_t S    = 0b01000000;
    static constexpr uint8_t SE   = 0b10000000;
    static constexpr uint8_t ALL  = 0b11111111;
    Direction(): val(NONE) {}
    Direction(uint8_t dir): val(dir) {}
    Direction(bool e, bool ne, bool n, bool nw, bool w, bool sw, bool s, bool se) {
        val = (e ? E : NONE) | (ne ? NE : NONE) | (n ? N : NONE) | (nw ? NW : NONE) |
              (w ? W : NONE) | (sw ? SW : NONE) | (s ? S : NONE) | (se ? SE : NONE);
    }
    bool atleast1_matches(Direction other) { return (val & other.val) != 0; }
};

class Velocity {
public:
    Speed speed;
    Direction direction;
    Velocity(): speed(Speed()), direction(Direction()) {}
    Velocity(Speed spd, Direction dir): speed(spd), direction(dir) {}
};

