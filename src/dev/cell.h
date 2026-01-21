#pragma once

using namespace godot;

class Cell {
private:
    bool valid;
public:
    int x;
    int y;
    Cell() : valid(false), x(-1), y(-1) {}
    Cell(int px, int py) : valid(true), x(px), y(py) {}
    Cell(const Cell& cell, const int resolution): valid(true) {
        //lower resolution
        x(cell.x / resolution);
        y(cell.y / resolution);
    }
    bool is_valid() const {return valid;}
    void invalid() {valid(false); x(-1); y(-1);}
    bool in_bounds(int lbx, int lby, int ubx, int uby) {
        if (x < lbx || x > ubx) {return false;}
        if (y < lby || y > uby) {return false;}
        return true;
    }
    bool operator==(const Cell& other) const {return x == other.x && y == other.y;}
};
