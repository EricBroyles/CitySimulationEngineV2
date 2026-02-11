#pragma once
// #include <stdexcept>
#include <godot_cpp/classes/image.hpp>
#include "vec.hpp"
#include "cell.hpp"

using namespace godot;

struct Direction {
    static constexpr Image::Format IMAGE_FORMAT = Image::FORMAT_R8;
    static constexpr int NUM_DIR = 8;
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
    uint8_t val;
    constexpr Direction(): Direction(NONE) {}
    constexpr explicit Direction(uint8_t v): val(v) {} //explicit refers to static_cast<Direction>
    constexpr bool is_none() const { return val == NONE; }
    constexpr int count() const { 
        int count = 0; uint8_t v = val; while(v){count += v & 1; v >>= 1;} return count;}
    bool operator[](int i) { return (i >= 0 && i < NUM_DIR) ? bool(val & 1 << i) : false; } //i=0 get E (T/F), i=1 get NE (T/F) --- NOTE 1<<i = 2^i    
    constexpr Direction& operator+=(const Direction rhs) { val += rhs.val; return *this; }
    constexpr Direction& operator-=(const Direction rhs) { val -= rhs.val; return *this; }
    constexpr Direction& operator&=(const Direction rhs) { val &= rhs.val; return *this; }
    constexpr Direction& operator|=(const Direction rhs) { val |= rhs.val; return *this; }
    friend constexpr Direction operator+(Direction lhs, const Direction rhs) { return lhs += rhs; }
    friend constexpr Direction operator-(Direction lhs, const Direction rhs) { return lhs -= rhs; }
    friend constexpr Direction operator&(Direction lhs, const Direction rhs) { return lhs &= rhs; }
    friend constexpr Direction operator|(Direction lhs, const Direction rhs) { return lhs |= rhs; }
    bool operator==(const Direction rhs) const { return val == rhs.val; } // if all 1&0 match
    bool operator!=(const Direction rhs) const { return val != rhs.val; } // if any 1&0 do not match
    bool no_matches(const Direction dir) const { return (val & dir.val) == NONE; } // if all 1 do not match or no 1 
    bool atleast1_matches(const Direction dir) const { return !no_matches(dir); }   // if atleast one 1 matches 
    constexpr explicit operator uint8_t() const { return val; } //static_cast<uint8_t>
};

struct SoloDirection: Direction {
private: 
    constexpr void validate() const {
        if (count() > 1) { 
            UtilityFunctions::push_error(vformat("Direction must be None or Solo: %d", count()));
            // throw std::invalid_argument("Direction must be None or Solo"); //crashes godot
        }
    }
public:
    constexpr SoloDirection(): Direction(NONE) {} 
    constexpr SoloDirection(uint8_t v): Direction(v) { validate(); } 
    constexpr SoloDirection(const Direction d): Direction(d.val) { validate(); }
    constexpr Vec2i to_vec2i() const {
        switch(val) {
        case E  : return Vec2i(1,0);
        case NE : return Vec2i(1,-1);
        case N  : return Vec2i(0,-1); 
        case NW : return Vec2i(-1,-1); 
        case W  : return Vec2i(-1,0); 
        case SW : return Vec2i(-1,1); 
        case S  : return Vec2i(0,1); 
        case SE : return Vec2i(1,1); 
        default : return Vec2i();}
    }
};

using Dir = Direction;
using SDir = SoloDirection;
using SDirArr4 = std::array<SDir,4>; // template<std::size_t N> using SDirArr = std::array<SDir,N>;
constexpr SoloDirection EAST = SDir(Dir::E);
constexpr SoloDirection WEST = SDir(Dir::W);
constexpr SoloDirection NORTH = SDir(Dir::N);
constexpr SoloDirection SOUTH = SDir(Dir::S);
constexpr SoloDirection NORTHEAST = SDir(Dir::NE);
constexpr SoloDirection NORTHWEST = SDir(Dir::NW);
constexpr SoloDirection SOUTHEAST = SDir(Dir::SE);
constexpr SoloDirection SOUTHWEST = SDir(Dir::SW);


