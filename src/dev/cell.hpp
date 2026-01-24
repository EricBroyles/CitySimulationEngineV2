/*
@struct Cell

@brief
* allowed to create instances of this as constexpr at compile time

@examples
==============================
-------------------------------
*/
#pragma once

struct Cell {
    int x, y;
    constexpr Cell(): x(INVALID), y(INVALID) {}
    constexpr Cell(int px, int py): x(px), y(py) {}
    constexpr Cell(const Cell& cell, int resolution): x(cell.x/resolution), y(cell.y/resolution) {} 
    bool is_invalid() const { return (x < 0 || y < 0); }
    bool is_valid() const { return !is_invalid(); }
    void invalid() { x = INVALID; y = INVALID; }
    bool in_bounds(int lbx, int lby, int ubx, int uby) {
        if (x < lbx || x > ubx) {return false;}
        if (y < lby || y > uby) {return false;}
        return true;}
    bool operator==(const Cell& other) const { return x == other.x && y == other.y; }
    Cell operator+ (const Cell& other) const { return Cell(x + other.x, y + other.y); }
private:
    static constexpr int INVALID = -1;
};