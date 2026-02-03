#pragma once
#include <stdexcept>
#include <array>

struct NavSeq {
private:
    constexpr void validate() const {if (val < NONE || val >= MAX) { throw std::invalid_argument("Unknown NavSeq"); }}
public:
    enum OPTIONS {NONE, WALK, DRIVE, MAX};
    static constexpr std::array<float> PREFERENCES = {0.0f, 1.0f, 0.9f}; // 0 = avoid at all cost, 1 = standard, 2 = prefer double
    uint8_t val;
    NavSeq(): val(NONE) {}
    NavSeq(uint8_t v): val(v) {}
    bool operator==(const NavSeq other) const {return val == other.val; }
    bool operator!=(const NavSeq other) const {return val != other.val; }
    // given a time static, output the preference score.
};



