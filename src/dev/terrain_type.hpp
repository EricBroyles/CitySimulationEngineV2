#pragma once
#include <stdexcept>
// #include <godot_cpp/classes/image.hpp>
#include <array>
#include "cell.hpp"

struct TerrainType {
private:
    static constexpr std::array<bool, 7> CAN_WALK = {false, false, true, true, true, true, false};
    static constexpr std::array<bool, 7> CAN_DRIVE = {false, true, false, true, true, false, false};
    constexpr void validate() const {if (val < NONE || val >= MAX) { throw std::invalid_argument("Unknown TerrainType"); }}
public:
    enum TT {NONE, ROAD, WALKWAY, CROSSWALK, PARKING, BUILDING, BARRIER, MAX};
    uint8_t val;
    constexpr TerrainType(): val(NONE) {}
    constexpr TerrainType(uint8_t v): val(v) { validate(); } 
    constexpr bool can_walk() const { return CAN_WALK[val]; }
    constexpr bool can_drive() const { return CAN_DRIVE[val]; }

    constexpr bool operator==(const TerrainType& tt) const { return val == tt.val; }
    constexpr bool operator!=(const TerrainType& tt) const { return val != tt.val; }



    // TerrainType(const Cell& cell, const Ref<Image>& img): val((img->get_pixel(cell.x,cell.y)).r * 255) { validate(); }
};