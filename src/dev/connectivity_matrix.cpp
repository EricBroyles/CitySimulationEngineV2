#include "connectivity_matrix.hpp"
#include <array>
#include <unordered_set> 
#include "cell.hpp"
#include "direction.hpp"
#include "cmid.hpp"
#include "matrix.hpp"
#include "base_world.hpp"

using namespace godot;

CM::ConnectivityMatrix(const BaseWorld& base): 
    valid(true), walk(base.cols, base.rows), drive(base.cols, base.rows) {
    set_barriers(base);
    set_cmids(base);
    num_walk_groups = count_matrix_groups(walk, walk_has_barrier);
    num_drive_groups = count_matrix_groups(drive, drive_has_barrier);
} 

bool CM::is_walk_barrier(const BaseWorld& base, const Cell cell, const Dir dir) const {
    if (base.can_walk_at(cell) && !dir.is_none()) {return false;}
    return true;     
}

bool CM::is_drive_barrier(const BaseWorld& base, const Cell cell, const Dir dir) const {
    if (base.can_drive_at(cell) && !dir.is_none()) {return false;}
    return true;      
}

void CM::set_barriers(const BaseWorld& base) {
    for (int r = 0; r < base.rows; r++) {
    for (int c = 0; c < base.cols; c++) {
        Cell cell = Cell(c,r);
        Dir dir  = base.get_dir(cell);

        if (is_walk_barrier(base, cell, dir)) {
            walk.at(cell) = CMID(CMID::BARRIER);
            walk_has_barrier = true;
        } 
        else { walk.at(cell) = CMID(cell.to_idx(base.cols)); }
        
        if (is_drive_barrier(base, cell, dir)) {
            drive.at(cell) = CMID(CMID::BARRIER);
            drive_has_barrier = true;
        } 
        else { drive.at(cell) = CMID(cell.to_idx(base.cols)); }
    }}
}

void CM::set_cmids(const BaseWorld& base) {
    set_downstream_cmids(base);
    set_upstream_cmids(base);
}

void CM::set_downstream_cmids(const BaseWorld& base) {
    static constexpr SDirArr4 CELL_SEARCH_DIRS = DOWN_DIRS;
    static constexpr SDirArr4 ADJ_SEARCH_DIRS = UP_DIRS;
    for (int r = 0; r < base.rows; r++) {
    for (int c = 0; c < base.cols; c++) {
        const Cell cell = Cell(c,r);
        resolve_cell(base, walk, cell, CELL_SEARCH_DIRS, ADJ_SEARCH_DIRS);
        resolve_cell(base, drive, cell, CELL_SEARCH_DIRS, ADJ_SEARCH_DIRS);
    }}
}

void CM::set_upstream_cmids(const BaseWorld& base) {
    static constexpr SDirArr4 CELL_SEARCH_DIRS = UP_DIRS;
    static constexpr SDirArr4 ADJ_SEARCH_DIRS = DOWN_DIRS;
    for (int r = base.rows-1; r >= 0; r--) { 
    for (int c = base.cols-1; c >= 0; c--) {
        const Cell cell = Cell(c,r);
        resolve_cell(base, walk, cell, CELL_SEARCH_DIRS, ADJ_SEARCH_DIRS);
        resolve_cell(base, drive, cell, CELL_SEARCH_DIRS, ADJ_SEARCH_DIRS);
    }}
}

void CM::resolve_cell(const BaseWorld& base, Matrix<CMID>& matrix, const Cell cell, const SDirArr4& cell_sdirs, const SDirArr4& adj_sdirs) {
    static constexpr int NUM = std::size(cell_sdirs);
    std::array<bool, NUM> connected = {}; //all false
    CMID& smallest = matrix.at(cell); //reference to avoid extra matrix.at(cell) = smallest
    if (smallest.is_barrier()) { return; }
    for (int i = 0; i < NUM; i++) {
        const Cell adj_cell = cell.get_adjacent_cell(cell_sdirs[i]); //use cell_sdirs to search for the adjacent cell
        if (base.out_of_bounds(adj_cell)) { continue; }
        const CMID adj_cmid = matrix.at(adj_cell); //copy
        if (adj_cmid.is_barrier()) { continue; }
        if (base.get_dir(cell).no_matches(cell_sdirs[i]) && base.get_dir(adj_cell).no_matches(adj_sdirs[i])) { continue; } 
        // the two cells are connected.
        // FUTURE ME: could improve this by giving all connected cells a shared pointer?
        connected[i] = true;
        if (adj_cmid < smallest) { smallest = adj_cmid; }
    }
    for (int i = 0; i < NUM; i++) {
        if (connected[i]) { 
            const Cell adj_cell = cell.get_adjacent_cell(cell_sdirs[i]);
            matrix.at(adj_cell) = smallest;
        }
    }
}

int CM::count_matrix_groups(const Matrix<CMID>& matrix, bool has_barrier) {
    // assumes no CMID::INVALID inside set
    // barrier cmid do not count as a group.
    const std::unordered_set<int>& unique_ints = matrix.to_unique_ints();
    return unique_ints.size() - int(has_barrier);
}


