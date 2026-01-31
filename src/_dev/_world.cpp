// #include "world.hpp"
// #include "cell.hpp"
// #include "direction.hpp"
// #include "matrix.hpp"
// #include "cmid.hpp"

// World::World(): valid(false), cols(0), rows(0), sec_per_step(0), feet_per_cell(0), cm_walk(), cm_drive() {}

// World::World(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_mph, const Ref<Image> p_dir, int p_sec_per_step, int p_feet_per_cell): 
//     valid(true), cols(p_tt->get_width()), rows(p_tt->get_height()),
//     sec_per_step(p_sec_per_step), feet_per_cell(p_feet_per_cell),
//     tt(p_tt), tm(p_tm), speed(p_mph), dir(p_dir), 
//     cm_walk(p_tt->get_width(), p_tt->get_height()), cm_drive(p_tt->get_width(), p_tt->get_height()) {
//     set_cm_barriers(); 
//     set_cmids();
// }

// bool World::is_cm_walk_barrier(const Cell& cell, const Direction& dir) const {
//     if (can_walk_at(cell) && !dir.is_none()) {return false;}
//     return true;     
// }

// bool World::is_cm_drive_barrier(const Cell& cell, const Direction& dir) const {
//     if (can_drive_at(cell) && !dir.is_none()) {return false;}
//     return true;      
// }

// void World::set_cm_barriers() {
//     for (int r = 0; r < rows; r++) {
//     for (int c = 0; c < cols; c++) {
//         Cell      cell = Cell(c,r);
//         Direction dir  = get_dir(cell);
//         cm_walk.at(cell) = is_cm_walk_barrier(cell, dir)  ? CMID(CMID::BARRIER) : CMID(cell.to_idx(cols));
//         cm_drive.at(cell) = is_cm_drive_barrier(cell, dir) ? CMID(CMID::BARRIER) : CMID(cell.to_idx(cols));
//     }}
// }

// void World::set_cell_cmid(Matrix<CMID>& matrix, const Cell& cell) {
//     CMID& cmid = matrix.at(cell);
//     if (cmid.is_barrier()) { return; }
//     for (int i = 0; i < CM_CHECK_DIRS ; i++) {
//         const Cell adj_cell = cell.get_adjacent_cell(CM_UP_DIRS[i]);
//         if (out_of_bounds(adj_cell)) { continue; }
//         const CMID& adj_cmid = matrix.at(adj_cell); // the "const" here is potentially problamatic
//         if (adj_cmid.is_barrier()) { continue; }
//         if (get_dir(cell).no_matches(CM_UP_DIRS[i]) && get_dir(adj_cell).no_matches(CM_DOWN_DIRS[i])) { continue; } // check do I point up, or does it point down.
//         cmid = adj_cmid; // this cell is connected to a adjacent cell with a smaller cmid. set it to the smaller cmid.
//         return;
//     }
// }

// void World::set_cmids() {
//     for (int r = 0; r < rows; r++) {
//     for (int c = 0; c < cols; c++) {
//         Cell cell = Cell(c,r);
//         set_cell_cmid(cm_walk, cell);
//         set_cell_cmid(cm_drive, cell);
//     }}
// }