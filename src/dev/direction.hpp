#pragma once
#include <stdexcept>
#include "vec.hpp"

struct Direction {
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
    constexpr Direction(): val(NONE) {}
    constexpr Direction(uint8_t v): val(v) {}
    constexpr bool is_none() const { return val == NONE; }
    constexpr int count() const { 
        int count = 0; uint8_t v = val; while(v){count += v & 1; v <<= 1;}return count;}
    bool operator[](int i) { return (i >= 0 && i < NUM_DIR) ? bool(val & 1 << i) : false; } //i=0 get E (T/F), i=1 get NE (T/F) --- NOTE 1<<i = 2^i    
    constexpr Direction& operator+=(const Direction& rhs) { val += rhs.val; return *this; }
    constexpr Direction& operator-=(const Direction& rhs) { val -= rhs.val; return *this; }
    constexpr Direction& operator&=(const Direction& rhs) { val &= rhs.val; return *this; }
    constexpr Direction& operator|=(const Direction& rhs) { val |= rhs.val; return *this; }
    friend constexpr Direction operator+(Direction copy_lhs, const Direction& rhs) { return copy_lhs += rhs; }
    friend constexpr Direction operator-(Direction copy_lhs, const Direction& rhs) { return copy_lhs -= rhs; }
    friend constexpr Direction operator&(Direction copy_lhs, const Direction& rhs) { return copy_lhs & rhs; }
    friend constexpr Direction operator|(Direction copy_lhs, const Direction& rhs) { return copy_lhs | rhs; }
    bool operator==(const Direction& rhs) const { return val == rhs.val; } // if all 1&0 match
    bool operator!=(const Direction& rhs) const { return val != rhs.val; } // if any 1&0 do not match
    bool no_matches(const Direction& dir) const { return (val & dir.val) == NONE; } // if all 1 do not match or no 1 
    bool atleast1_matches(const Direction& dir) const { return !no_matches(dir); }   // if atleast one 1 matches 
};

struct SoloDirection {
    Direction dir; //NONE or SOLO
    constexpr SoloDirection(): dir(Direction::NONE) {} 
    constexpr SoloDirection(const Direction& d): dir(d) { 
        if (dir.count() > 1) { throw std::invalid_argument("Direction must be None or Solo"); }}
    constexpr Vec2i to_vec2i() const {
        switch(dir.val) {
        case Direction::E  : return Vec2i(1,0);
        case Direction::NE : return Vec2i(1,1);
        case Direction::N  : return Vec2i(0,1); 
        case Direction::NW : return Vec2i(-1,1); 
        case Direction::W  : return Vec2i(-1,0); 
        case Direction::SW : return Vec2i(-1,-1); 
        case Direction::S  : return Vec2i(0,-1); 
        case Direction::SE : return Vec2i(1,-1); 
        default            : return Vec2i();}
    }
};

