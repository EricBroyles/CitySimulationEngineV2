/*
@algorithm
Loop forward through all cells.
Push smallest CMID downstream: at each cell find the smallest connected CMID. replace all connected cmid with smallest
Loop backward through all cells.
Push smallest CMID upstream: same idea just look the other direction.

The double loop is needed to deal with barriers creating pockets of not properly classified cmid.
-> Situation: solid barrier that splits a matrix down the middle. but last row has no barrier. 
              with one pass you get two groups. with two passes it is the correct one group.
*/
#pragma once
#include <array>
#include "cell.hpp"
#include "direction.hpp"
#include "cmid.hpp"
#include "matrix.hpp"
#include "base_world.hpp"

using namespace godot;

class ConnectivityMatrix {
    static constexpr SDirArr4 UP_DIRS = {SDir(Dir::NW), SDir(Dir::N), SDir(Dir::NE), SDir(Dir::W)};
    static constexpr SDirArr4 DOWN_DIRS = {SDir(Dir::SE), SDir(Dir::S), SDir(Dir::SW), SDir(Dir::E)};
    Matrix<CMID> walk;
    Matrix<CMID> drive;
    bool walk_has_barrier = false; //needed to count num groups
    bool drive_has_barrier = false; 
    bool valid = false;
    bool is_walk_barrier(const BaseWorld& base, const Cell cell, const Dir dir) const;
    bool is_drive_barrier(const BaseWorld& base, const Cell cell, const Dir dir) const;
    void set_barriers(const BaseWorld& base);
    void set_cmids(const BaseWorld& base);
    void set_downstream_cmids(const BaseWorld& base);
    void set_upstream_cmids(const BaseWorld& base);
    void resolve_cell(const BaseWorld& base, Matrix<CMID>& matrix, const Cell cell, const SDirArr4& cell_sdirs, const SDirArr4& adj_sdirs);
    int count_matrix_groups(const Matrix<CMID>& matrix, bool has_barrier);
public:
    int num_walk_groups = 0;
    int num_drive_groups = 0;
    ConnectivityMatrix(): walk(), drive() {}
    ConnectivityMatrix(const BaseWorld& base);
    const Matrix<CMID>& get_walk() const { return walk; }
    const Matrix<CMID>& get_drive() const { return drive; }
    const bool can_walk_between(const Cell cell1, const Cell cell2) const { return walk.at(cell1).is_cmid() && (walk.at(cell1) == walk.at(cell2)); }
    const bool can_drive_between(const Cell cell1, const Cell cell2) const { return drive.at(cell1).is_cmid() && (drive.at(cell1) == drive.at(cell2)); }
};

using CM = ConnectivityMatrix;


