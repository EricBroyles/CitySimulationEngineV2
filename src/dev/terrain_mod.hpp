#pragma once
#include <stdexcept>
#include "cell.hpp"

struct TerrainMod {
private:
    constexpr void validate() const {if (val < NONE || val >= MAX) { throw std::invalid_argument("Unknown TerrainMod"); }}
public:
    enum OPTIONS {NONE, JUNCTION_STOP, JUNCTION1, JUNCTION2, JUNCTION3, LANE_DIVIDER, MAX};
    uint8_t val;
    constexpr TerrainMod(): val(NONE) {}
    constexpr TerrainMod(uint8_t v): val(v) { validate(); } 
    constexpr bool operator==(const TerrainMod tm) const { return val == tm.val; }
    constexpr bool operator!=(const TerrainMod tm) const { return val != tm.val; }
};

using TM = TerrainMod;