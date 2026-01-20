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
    ~Cell() {}
    bool is_valid() const { return valid; }
    void invalid() { valid = false; }
    bool operator==(const Cell& other) const {return x == other.x && y == other.y;}
};
