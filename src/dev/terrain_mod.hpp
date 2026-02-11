#pragma once
// #include <stdexcept>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "cell.hpp"

using namespace godot;

struct TerrainMod {
private:
    constexpr void validate() const {
        if (val < NONE || val >= MAX) { 
            UtilityFunctions::push_error(vformat("Unknown TerrainMod %d", val));
            // throw std::invalid_argument("Unknown TerrainMod"); // crashes godot
        }
    }
public:
    static constexpr Image::Format IMAGE_FORMAT = Image::FORMAT_R8;
    enum OPTIONS {NONE, JUNCTION_STOP, JUNCTION1, JUNCTION2, JUNCTION3, LANE_DIVIDER, MAX};
    uint8_t val;
    constexpr TerrainMod(): val(NONE) {}
    constexpr explicit TerrainMod(uint8_t v): val(v) { validate(); } //explicit refers to static_cast<TM>
    constexpr bool operator==(const TerrainMod tm) const { return val == tm.val; }
    constexpr bool operator!=(const TerrainMod tm) const { return val != tm.val; }
    constexpr explicit operator uint8_t() const { return val; } //static_cast<uint8_t>
};

using TM = TerrainMod;