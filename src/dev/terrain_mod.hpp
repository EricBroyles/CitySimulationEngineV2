#pragma once
#include <stdexcept>
#include <godot_cpp/classes/image.hpp>
#include "cell.hpp"

using namespace godot;

struct TerrainMod {
private:
    constexpr void validate() const {if (val < NONE || val >= MAX) { throw std::invalid_argument("Unknown TerrainMod"); }}
public:
    static constexpr Image::Format IMAGE_FORMAT = Image::FORMAT_R8;
    enum OPTIONS {NONE, JUNCTION_STOP, JUNCTION1, JUNCTION2, JUNCTION3, LANE_DIVIDER, MAX};
    uint8_t val;
    constexpr TerrainMod(): val(NONE) {}
    constexpr explicit TerrainMod(uint8_t v): val(v) { validate(); } //explicit refers to static_cast<TM>
    constexpr bool operator==(const TerrainMod tm) const { return val == tm.val; }
    constexpr bool operator!=(const TerrainMod tm) const { return val != tm.val; }
};

using TM = TerrainMod;