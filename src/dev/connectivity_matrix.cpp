#include "connectivity_matrix.hpp"
#include "cell.hpp"
#include "matrix.hpp"
#include "direction.hpp"
#include "cmid.hpp"
#include "base_world.hpp"

using namespace godot;

ConnectivityMatrix::ConnectivityMatrix(const BaseWorld& base): 
    valid(true), walk(base.cols, base.rows), drive(base.cols, base.rows) {
    set_barriers(base);
    set_cmids(base);
} 

bool ConnectivityMatrix::is_walk_barrier(const BaseWorld& base, const Cell cell, const Direction dir) const {
    if (base.can_walk_at(cell) && !dir.is_none()) {return false;}
    return true;     
}

bool ConnectivityMatrix::is_drive_barrier(const BaseWorld& base, const Cell cell, const Direction dir) const {
    if (base.can_drive_at(cell) && !dir.is_none()) {return false;}
    return true;      
}

void ConnectivityMatrix::set_barriers(const BaseWorld& base) {
    for (int r = 0; r < base.rows; r++) {
    for (int c = 0; c < base.cols; c++) {
        Cell      cell = Cell(c,r);
        Direction dir  = base.get_dir(cell);
        walk.at(cell) = is_walk_barrier(base, cell, dir)  ? CMID(CMID::BARRIER) : CMID(cell.to_idx(base.cols));
        drive.at(cell) = is_drive_barrier(base, cell, dir) ? CMID(CMID::BARRIER) : CMID(cell.to_idx(base.cols));
    }}
}

void ConnectivityMatrix::set_cell_cmid(const BaseWorld& base, Matrix<CMID>& matrix, const Cell cell) {
    CMID& cmid = matrix.at(cell);
    if (cmid.is_barrier()) { return; }
    for (int i = 0; i < NUM_CHECK_DIR; i++) {
        const Cell adj_cell = cell.get_adjacent_cell(UP_DIRS[i]);
        if (base.out_of_bounds(adj_cell)) { continue; }
        const CMID& adj_cmid = matrix.at(adj_cell); // the "const" here is potentially problamatic
        if (adj_cmid.is_barrier()) { continue; }
        if (base.get_dir(cell).no_matches(UP_DIRS[i]) && base.get_dir(adj_cell).no_matches(DOWN_DIRS[i])) { continue; } // check do I point up, or does it point down.
        cmid = adj_cmid; // this cell is connected to a adjacent cell with a smaller cmid. set it to the smaller cmid.
        return;
    }
}

void ConnectivityMatrix::set_cmids(const BaseWorld& base) {
    for (int r = 0; r < base.rows; r++) {
    for (int c = 0; c < base.cols; c++) {
        Cell cell = Cell(c,r);
        set_cell_cmid(base, walk, cell);
        set_cell_cmid(base, drive, cell);
    }}
}

void ConnectivityMatrix::display_full() const {
    print_line("----------------------------------");
    print_line("Display Full CM");
    if (!valid) {print_line("CM is invalid. Nothing to display."); return;};
    print_line("Walk: ");
    walk.display_full_as_int();
    print_line("Drive: ");
    drive.display_full_as_int();
}

