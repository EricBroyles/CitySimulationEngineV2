#pragma once
#include <stdexcept>
#include <godot_cpp/classes/image.hpp>

struct TerrainMod {
private:
    constexpr void validate() const {if (val < NONE || val >= MAX) { throw std::invalid_argument("Unknown TerrainMod"); }}
public:
    enum TM {NONE, JUNCTION_STOP, JUNCTION1, JUNCTION2, JUNCTION3, LANE_DIVIDER, MAX};
    uint8_t val;
    constexpr TerrainMod(): val(NONE) {}
    constexpr TerrainMod(uint8_t v): val(v) { validate(); } 
    TerrainMod(size_t c, size_t r, const Ref<Image>& godot_tm): val((godot_tm->get_pixel(c,r)).r *255) { validate(); }
};