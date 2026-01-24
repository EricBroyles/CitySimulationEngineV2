// #pragma once

// #include <cstdint>
// #include <array>

// struct Speed {
// // (mi / hour) (1 hour / 60 min) (1 min / 60 sec) (sec_per_step) (5280 ft / 1 mi) (1/feet_per_cell)
//     float val;
//     constexpr Speed(): val(0) {}
//     constexpr Speed(float speed): val(speed) {}
//     constexpr Speed(int sec_per_step, int feet_per_cell, int mph) { val = mph * (1.0f/3600.0f) * sec_per_step * 5280.0f * 1.0f/feet_per_cell; }
//     constexpr Speed(World& world, int mph) { val = mph * (1.0f/3600.0f) * world.step_duration * 5280.0f * 1.0f/world.cell_width; }
// };

// struct Direction {
//     static constexpr uint8_t NONE = 0b00000000;
//     static constexpr uint8_t E    = 0b00000001;
//     static constexpr uint8_t NE   = 0b00000010;
//     static constexpr uint8_t N    = 0b00000100;
//     static constexpr uint8_t NW   = 0b00001000;
//     static constexpr uint8_t W    = 0b00010000;
//     static constexpr uint8_t SW   = 0b00100000;
//     static constexpr uint8_t S    = 0b01000000;
//     static constexpr uint8_t SE   = 0b10000000;
//     static constexpr uint8_t ALL  = 0b11111111;
//     uint8_t val;
//     constexpr Direction(): val(NONE) {}
//     constexpr Direction(uint8_t dir): val(dir) {}
//     constexpr Direction(bool e, bool ne, bool n, bool nw, bool w, bool sw, bool s, bool se) {
//         val = (e ? E : NONE) | (ne ? NE : NONE) | (n ? N : NONE) | (nw ? NW : NONE) |
//               (w ? W : NONE) | (sw ? SW : NONE) | (s ? S : NONE) | (se ? SE : NONE);
//     }
//     static bool atleast1_matches(const Direction& d1, const Direction& d2) const {return (d1.val & d2.val) != 0;}
//     static bool no_matches(const Direction& d1, const Direction& d2) const {return (d1.val & d2.val) == 0;} // None & None -> no matching direction so true
//     static Direction and(const Direction& d1, const Direction& d2) {return Direction(d1.val & d2.val);}
//     bool operator[](int i) const {
//         // given an integer corrsponding to a direction determine if that direction is in this direction
//         // dir_mask: 0 -> E = 00000001, 1 -> NE = 00000010
//         if (i < 0 || i > 7) {return false;}
//         uint8_t dir_mask = 1 << i; //2^i
//         return val & dir_mask; //false if 0
//     }
//     bool is_none() const {return val == NONE;}
// };

// struct SoloDirection {
//     // should do inheritance.
//     uint8_t val;
//     constexpr SoloDirection(const Direction& dir, int dir_idx): val(0) {
//         if (i > 0 && i < 8) {
//             uint8_t dir_mask = 1 << dir_idx;
//             val(dir.val & dir_mask);
//         }
//     }
//     bool is_none() const {return val == Direction::NONE;}
//     Vec2i get_vector() const {
//         switch (val) {
//             case Direction::E  : return Vec2i(1,0);
//             case Direction::NE : return Vec2i(1,1);
//             case Direction::N  : return Vec2i(0,1); 
//             case Direction::NW : return Vec2i(1,1); 
//             case Direction::W  : return Vec2i(1,0); 
//             case Direction::SW : return Vec2i(1,1); 
//             case Direction::S  : return Vec2i(0,1); 
//             case Direction::SE : return Vec2i(1,1); 
//             default            : return Vec2i();}
//     }
// };

// struct Velocity {
//     Speed speed;
//     Direction direction;
//     constexpr Velocity(): speed(Speed()), direction(Direction()) {}
//     constexpr Velocity(Speed spd, Direction dir): speed(spd), direction(dir) {}

// };

