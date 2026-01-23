#pragma once
#include <array>
#include <vector>
#include "world.h"

/*
Connectivity Matrix (CM)
* each cell ig given a cm_group_id which indicated to what cells it is connected to.
* connected only requires 

*/

class CMGroup {
private:
    static constexpr int INVALID_ID = -1;
    int _id;
public:
    explicit CMGroup(): id(INVALID_ID) {}
    explicit CMGroup(int v): id(v) {}
    bool is_valid() const {return id > INVALID_ID;}
    void invalid() {id(INVALID_ID);}
    int id() const {return _id;}
};




// THis does not work as inteded


class ConnectivityMatrix {
private:
    bool valid;
    static constexpr std::array<Direction,4> SEARCH_DIRECTIONS = {Direction(Direction::NE), Direction(Direction::N),Direction(Direction::NW), Direction(Direction::W)};
    const std::vector<CMGroup> walk;
    const std::vector<CMGroup> drive;
    CMgroup get_group(const World& world, const Cell& cell, const Direction& dir) const {
        for (Direction search: SEARCH_DIRECTIONS) {
            if (Direction::no_matches(dir,search)) {continue;}
            Cell adj_cell = cell.get_adjacent(search)
            if (world.out_of_bounds(adj_cell)) {continue;} //handles invalid cells
            int id = adj_cell.get_rowwise_idx(world.cols)
            return CMGroup(id);}
        return CMGroup();
    }
    CMGroup get_walk_group(const World& world, const Cell& cell, const Direction& dir) const {
        if !(world.can_walk_at(cell)) {return CMGroup();}
        return get_group(world, cell, dir);
    }
    CMGroup get_drive_group(const World& world, const Cell& cell, const Direction& dir) const {
        if !(world.can_drive_at(cell)) {return CMGroup();}
        return get_group(world, cell, dir);
    }
public:
    ConnectivityMatrix(): valid(false) {}
    ConnectivityMatrix(const World& world): valid(true) {
        for (int r = 0; r < world.rows; r++) {
        for (int c = 0; c < world.cols; c++) {
            Cell cell = Cell(c,r);
            Direction dir = world.get_dir(cell)
            int idx = cell.get_rowwise_idx(world.cols)
            walk[idx] = get_walk_group(world, cell, dir);
            drive[idx] = get_drive_group(world, cell, dir);
        }}
    }
    bool is_valid() const {return valid;}
    void invalid() {valid(false);}
    // CMGroup get_walk_group(int c, int r); //use cell
    // CMGroup get_drive_group(int c, int r);
    // bool is_walk_connected(int c1, int r1, int c2, int r2);
    // bool is_drive_connected()
    
    
};

