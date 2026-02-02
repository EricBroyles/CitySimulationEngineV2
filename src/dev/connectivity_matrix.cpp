#include "connectivity_matrix.hpp"
#include <array>
#include "cell.hpp"
#include "matrix.hpp"
#include "direction.hpp"
#include "cmid.hpp"
#include "base_world.hpp"

using namespace godot;

CM::ConnectivityMatrix(const BaseWorld& base): 
    valid(true), walk(base.cols, base.rows), drive(base.cols, base.rows) {
    set_barriers(base);
    set_cmids(base);
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
        walk.at(cell) = is_walk_barrier(base, cell, dir)  ? CMID(CMID::BARRIER) : CMID(cell.to_idx(base.cols));
        drive.at(cell) = is_drive_barrier(base, cell, dir) ? CMID(CMID::BARRIER) : CMID(cell.to_idx(base.cols));
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
    std::array<bool, cell_sdirs.size()> connected = {}; //all false
    CMID& smallest = matrix.at(cell); //reference to avoid extra matrix.at(cell) = smallest
    if (smallest.is_barrier()) { return; }
    for (int i = 0; i < cell_sdirs.size(); i++) {
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
    for (int i = 0; i < cell_sdirs.size(); i++) {
        if (connected[i]) { 
            const Cell adj_cell = cell.get_adjacent_cell(cell_sdirs[i]);
            matrix.at(adj_cell) = smallest;
        }
    }
}


//Down stream.
//array of 5 bool all false
// smallest CMID
// is the root cell connected to E cell. 0 slot is true and 1 slot is true. update smallest CMID.
// is the root cell connected to Se cell. o slot is true and 2 slot is true. update smallest CMID.
// S
// SW
//for all true bool replace its CMID with smallest CMID val.



//



// void ConnectivityMatrix::downstream_resolve_cell(const BaseWorld& base, Matrix<CMID>& matrix, const Cell root) {
//     // std::array<bool,NUM_CHECK_DIR> connected = {}; // all false
//     // CMID& smallest = matrix.at(root); //refrence to the cmid (to avoid needing to set it again with matrix.at(root) = smallest)
//     // if (smallest.is_barrier()) { return; }
//     // for (int i = 0; i < NUM_CHECK_DIR; i++) {
//     //     const Cell adj_cell = root.get_adjacent_cell(DOWN_DIRS[i]);
//     //     if (base.out_of_bounds(adj_cell)) { continue; }
//     //     const CMID adj_cmid = matrix.at(adj_cell); //copies the cmid and makes it unmodifiabel
//     //     if (adj_cmid.is_barrier()) { continue; }
//     //     if (base.get_dir(root).no_matches(DOWN_DIRS[i]) && base.get_dir(adj_cell).no_matches(UP_DIRS[i])) { continue; } 
//     //     // the two cells are connected.
//     //     connected[i] = true;
//     //     if (adj_cmid < smallest) { smallest = adj_cmid; }
//     // }
//     // // matrix.at(root) = smallest;
//     // for (int i = 0; i < NUM_CHECK_DIR; i++) {
//     //     if (connected[i]) { 
//     //         const Cell adj_cell = root.get_adjacent_cell(DOWN_DIRS[i]);
//     //         matrix.at(adj_cell) = smallest;
//     //     }
//     // } 

// }


// void ConnectivityMatrix::set_cell_cmid(const BaseWorld& base, Matrix<CMID>& matrix, const Cell cell) {
//     CMID& cmid = matrix.at(cell);
//     if (cmid.is_barrier()) { return; }
//     for (int i = 0; i < NUM_CHECK_DIR; i++) {
//         const Cell adj_cell = cell.get_adjacent_cell(UP_DIRS[i]);
//         if (base.out_of_bounds(adj_cell)) { continue; }
//         CMID& adj_cmid = matrix.at(adj_cell); // the "const" here is potentially problamatic
//         if (adj_cmid.is_barrier()) { continue; }
//         if (base.get_dir(cell).no_matches(UP_DIRS[i]) && base.get_dir(adj_cell).no_matches(DOWN_DIRS[i])) { continue; } // check do I point up, or does it point down.
//         cmid = adj_cmid; // this cell is connected to a adjacent cell with a smaller cmid. set it to the smaller cmid.
//         return;
//     }
// }

// void ConnectivityMatrix::set_cmids(const BaseWorld& base) {
//     for (int r = 0; r < base.rows; r++) {
//     for (int c = 0; c < base.cols; c++) {
//         Cell cell = Cell(c,r);
//         set_cell_cmid(base, walk, cell);
//         set_cell_cmid(base, drive, cell);
//     }}
// }

void CM::display_full() const {
    print_line("----------------------------------");
    print_line("Display Full CM");
    if (!valid) {print_line("CM is invalid. Nothing to display."); return;};
    print_line("Walk: ");
    walk.display_full_as_int();
    print_line("Drive: ");
    drive.display_full_as_int();
}

