// barriers matrix (cannot walk and none dir)
// @each cell: search for a smaller CMID
// am I a barrier, then continue
// for all 4 cells that might have a smaller CMID
//      is it a barrier, continue
//      Do DIrections point to each other. -> ( I look up and to the top left

//process each cell
// I need an emtpy CM

#pragma once
#include "cell.hpp"
#include "matrix.hpp"
#include "direction.hpp"
#include "world.hpp"
#include "cmid.hpp"

class ConnectivityMatrix {
    bool valid;
    Matrix<CMID> walk;
    Matrix<CMID> drive;

};

