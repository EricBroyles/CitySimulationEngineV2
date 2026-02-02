#pragma once
#include <array>
#include "cell.hpp"
#include "matrix.hpp"
#include "direction.hpp"
#include "cmid.hpp"
#include "base_world.hpp"

//Down stream.
//array of 5 bool all false
// smallest CMID
// is the root cell connected to E cell. 0 slot is true and 1 slot is true. update smallest CMID.
// is the root cell connected to Se cell. o slot is true and 2 slot is true. update smallest CMID.
// S
// SW
//for all true bool replace its CMID with smallest CMID val.


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


// using namespace godot;

// class ConnectivityMatrix {
//     static constexpr int NUM_CHECK_DIR = 4;
//     static constexpr std::array<SoloDirection, NUM_CHECK_DIR> UP_DIRS = {SoloDirection(Direction::NW), SoloDirection(Direction::N), SoloDirection(Direction::NE), SoloDirection(Direction::W)};
//     static constexpr std::array<SoloDirection, NUM_CHECK_DIR> DOWN_DIRS = {SoloDirection(Direction::SE), SoloDirection(Direction::S), SoloDirection(Direction::SW), SoloDirection(Direction::E)};
//     Matrix<CMID> walk;
//     Matrix<CMID> drive;
//     bool valid;
//     bool is_walk_barrier(const BaseWorld& base, const Cell cell, const Direction dir) const;
//     bool is_drive_barrier(const BaseWorld& base, const Cell cell, const Direction dir) const;
//     void set_barriers(const BaseWorld& base);
//     void set_cell_cmid(const BaseWorld& base, Matrix<CMID>& matrix, const Cell cell);
//     void set_cmids(const BaseWorld& base);
// public:
//     ConnectivityMatrix(): valid(false), walk(), drive() {}
//     ConnectivityMatrix(const BaseWorld& base);
//     void display_full() const;
// };
