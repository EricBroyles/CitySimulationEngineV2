#pragma once

using namespace godot;

class Cell {
public:
    int x;
    int y;
    Cell(): x(-1), y(-1) {}
    Cell(int px, int py): x(px), y(py) {}
    Cell(const Cell& cell, const int resolution) {
        //lower resolution
        x(cell.x / resolution); y(cell.y / resolution);
    }
    bool is_valid() const {return (x < 0) || (y < 0)}
    void invalid() {x(-1); y(-1);}
    bool in_bounds(int lbx, int lby, int ubx, int uby) {
        if (x < lbx || x > ubx) {return false;}
        if (y < lby || y > uby) {return false;}
        return true;
    }
    int get_rowwise_idx(int cols) {return y * cols + c;}
    Cell get_adjacent(const Direction& dir) const {
        // must be a solo direction (E good) (E,W no bueno)
        swtich (dir.val) {
            case Direction::NONE : return Cell();
            case Direction::E    : return Cell(x+1,y+0);
            case Direction::NE   : return Cell(x+1,y-1);
            case Direction::N    : return Cell(x+0,y-1); 
            case Direction::NW   : return Cell(x-1,y-1); 
            case Direction::W    : return Cell(x-1,y+0); 
            case Direction::SW   : return Cell(x-1,y+1); 
            case Direction::S    : return Cell(x+0,y+1); 
            case Direction::SE   : return Cell(x+1,y+1); 
            default              : return Cell();
        }
    }
    bool operator==(const Cell& other) const {return x == other.x && y == other.y;}
};
