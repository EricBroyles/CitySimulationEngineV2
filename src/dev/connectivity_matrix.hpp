#pragma once
#include <array>
#include "cell.hpp"
#include "matrix.hpp"
#include "direction.hpp"
#include "cmid.hpp"
#include "base_world.hpp"

using namespace godot;

class ConnectivityMatrix {
    static constexpr int NUM_CHECK_DIR = 4;
    static constexpr std::array<SoloDirection, NUM_CHECK_DIR> UP_DIRS = {SoloDirection(Direction::NW), SoloDirection(Direction::N), SoloDirection(Direction::NE), SoloDirection(Direction::W)};
    static constexpr std::array<SoloDirection, NUM_CHECK_DIR> DOWN_DIRS = {SoloDirection(Direction::SE), SoloDirection(Direction::S), SoloDirection(Direction::SW), SoloDirection(Direction::E)};
    Matrix<CMID> walk;
    Matrix<CMID> drive;
    bool valid;
    bool is_walk_barrier(const BaseWorld& base, const Cell cell, const Direction dir) const;
    bool is_drive_barrier(const BaseWorld& base, const Cell cell, const Direction dir) const;
    void set_barriers(const BaseWorld& base);
    void set_cell_cmid(const BaseWorld& base, Matrix<CMID>& matrix, const Cell cell);
    void set_cmids(const BaseWorld& base);
public:
    ConnectivityMatrix(): valid(false), walk(), drive() {}
    ConnectivityMatrix(const BaseWorld& base);
    void display_full() const;
};
