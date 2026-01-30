#pragma once

struct CMID {
    static constexpr int INVALID = -2;
    static constexpr int BARRIER = -1;
    int val;
    constexpr CMID(): val(INVALID) {}
    constexpr CMID(int v): val(v) {}
    bool is_valid() const { return val > INVALID; }
    bool is_invalid() const { return !is_valid(); }
    bool is_barrier() const { return val == BARRIER; }
    void invalidate() { val = INVALID; }
    void barrier() { val = BARRIER; }
    CMID& operator++() { ++val; return *this; } //++CMID only. 
    bool  operator==(const CMID& other) const { return val == other.val; } 
    bool  operator!=(const CMID& other) const { return val != other.val; } 
};

