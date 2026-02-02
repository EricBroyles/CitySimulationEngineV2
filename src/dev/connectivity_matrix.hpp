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
#include "matrix.hpp"
#include "direction.hpp"
#include "cmid.hpp"
#include "base_world.hpp"

using namespace godot;

class ConnectivityMatrix {
    static constexpr SDirArr4 UP_DIRS = {SDir(Dir::NW), SDir(Dir::N), SDir(Dir::NE), SDir(Dir::W)};
    static constexpr SDirArr4 DOWN_DIRS = {SDir(Dir::SE), SDir(Dir::S), SDir(Dir::SW), SDir(Dir::E)};
    Matrix<CMID> walk;
    Matrix<CMID> drive;
    bool valid;
    bool is_walk_barrier(const BaseWorld& base, const Cell cell, const Dir dir) const;
    bool is_drive_barrier(const BaseWorld& base, const Cell cell, const Dir dir) const;
    void set_barriers(const BaseWorld& base);
    void set_cmids(const BaseWorld& base);
    void set_downstream_cmids(const BaseWorld& base);
    void set_upstream_cmids(const BaseWorld& base);
    void resolve_cell(const BaseWorld& base, Matrix<CMID>& matrix, const Cell cell, const SDirArr4& cell_sdirs, const SDirArr4& adj_sdirs);
public:
    ConnectivityMatrix(): valid(false), walk(), drive() {}
    ConnectivityMatrix(const BaseWorld& base);
    void display_full() const;
};

using CM = ConnectivityMatrix;


