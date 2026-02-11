#pragma once
#include <array>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "cell.hpp"

using namespace godot;

struct TerrainType {
private:
    static constexpr std::array<bool, 7> CAN_WALK = {false, false, true, true, true, true, false};
    static constexpr std::array<bool, 7> CAN_DRIVE = {false, true, false, true, true, false, false};
    constexpr void validate() const {
        if (val < NONE || val >= MAX) { 
            UtilityFunctions::push_error(vformat("Unknown TerrainType %d", val));
        }
    }
public:
    static constexpr Image::Format IMAGE_FORMAT = Image::FORMAT_R8;
    enum OPTIONS {NONE, ROAD, WALKWAY, CROSSWALK, PARKING, BUILDING, BARRIER, MAX};
    uint8_t val;
    constexpr TerrainType(): val(NONE) {}
    constexpr explicit TerrainType(uint8_t v): val(v) { validate(); } //explicit refers to static_cast<TT>
    constexpr bool can_walk() const { return CAN_WALK[val]; }
    constexpr bool can_drive() const { return CAN_DRIVE[val]; }
    constexpr bool operator==(const TerrainType tt) const { return val == tt.val; }
    constexpr bool operator!=(const TerrainType tt) const { return val != tt.val; }
    constexpr explicit operator uint8_t() const { return val; } //static_cast<uint8_t>
};

using TT = TerrainType;