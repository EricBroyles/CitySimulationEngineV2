#pragma once
#include <stdexcept>
#include <godot_cpp/classes/image.hpp>
#include "cell.hpp"

struct TerrainType {
private:
    constexpr void validate() const {if (val < NONE || val >= MAX) { throw std::invalid_argument("Unknown TerrainType"); }}
public:
    enum TT {NONE, ROAD, WALKWAY, CROSSWALK, PARKING, BUILDING, BARRIER, MAX};
    uint8_t val;
    constexpr TerrainType(): val(NONE) {}
    constexpr TerrainType(uint8_t v): val(v) { validate(); } 
    TerrainType(const Cell& cell, const Ref<Image>& godot_tt): val((godot_tt->get_pixel(cell.x,cell.y)).r *255) { validate(); }
};