#pragma once
#include <array>
#include <vector>
#include "world.h"

/*

// dir matrix, get_dir -> Direction
        // TT connected to set for walk and drive

        //walk: 
        // for each cell in tt, 
        // check is tt != WALKWAY, CROSSWALK, PARKING, BUILDING -> Cm group is invalid
        // else: check tl, t, tr, l cells that I can move to via dir. 
        // as soon as one is not invalid or out of bounds, get its cm group and set it to this cell.
        // continue

        // same idea for drive but tt != ROAD, PARKING, CROSSWALK

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

class ConnectivityMatrix {
private:
    bool valid;
    static constexpr std::array<Direction,4> SEARCH_DIRECTIONS = {Direction(Direction::NE), Direction(Direction::N),Direction(Direction::NW), Direction(Direction::W)};
    const std::vector<CMGroup> walk;
    const std::vector<CMGroup> drive;
    // THIS IS NOT GOOD. 
    CMGroup get_walk_group(const World& world, const Cell& cell, const Direction& dir, const CMGroup& initial_group) const {
        if !(world.can_walk_at(cell);) {return CMGroup();}
        for (Direction search: SEARCH_DIRECTIONS) {
            if !(Direction::atleast1_matches(dir,search)) {continue;}
            Cell adj_cell = cell.get_adjacent(search)
            if !(world.in_bounds(adj_cell)) {continue;} //this check also deals with invalid cells
            int idx = adj_cell.get_rowwise_idx(world.cols)
            return CMGroup(idx);
        }
        return CMGroup();
    }
    CMGroup get_drive_group(const World& world, const Cell& cell, const Direction& dir, const CMGroup& initial_group) const {
        if !(world.can_drive_at(cell);) {return CMGroup();}
        for (Direction search: SEARCH_DIRECTIONS) {
            if !(Direction::atleast1_matches(dir,search)) {continue;}
            Cell adj_cell = cell.get_adjacent(search)
            if !(world.in_bounds(adj_cell)) {continue;} //this check also deals with invalid cells
            int idx = adj_cell.get_rowwise_idx(world.cols)
            return CMGroup(idx);
        }
        return CMGroup();
    }
public:
    ConnectivityMatrix(): valid(false) {}
    ConnectivityMatrix(const World& world): valid(true) {
        for (int r = 0; r < world.rows; r++) {
        for (int c = 0; c < world.cols; c++) {
            Cell cell = Cell(c,r);
            Direction dir = world.get_dir(cell)
            int idx = cell.get_rowwise_idx(world.cols)
            CMGroup initial_group = CMGroup(idx);
            walk[idx] = get_walk_group(world, cell, dir, initial_group);
            drive[idx] = get_drive_group(world, cell, dir, initial_group);
        }}
    }
    bool is_valid() const {return valid;}
    void invalid() {valid(false);}
    // CMGroup get_walk_group(int c, int r); //use cell
    // CMGroup get_drive_group(int c, int r);
    // bool is_walk_connected(int c1, int r1, int c2, int r2);
    // bool is_drive_connected()
    
    
};

