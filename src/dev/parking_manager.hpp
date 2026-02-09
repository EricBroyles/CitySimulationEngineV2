#pragma once
#include "idx.hpp"
#include "cell.hpp"
#include "base_world.hpp"

/*

4096x4096 base world. with Parking TT. get_tt(Cell)

get_random_parking_cell() -> Cell
reserve_reasonable_parking_cell(Cell near_cell) -> Cell, update parking

take the provided cell -> 

4096 = 4^6

4096x4096
1024x1024   4x
256x256     4x4
64x64       4x4x4
16x16       4x4x4x4
4x4         4x4x4x4x4
base


layers:
0: total parking space
1: 4 quadrents, num spaces in each

dont store stuff insdie the 0 quadrent. 
bottom layer is base. 

std::vector<>

Node0:
-> value = total parking spots 4096x4096
-> parent = INVALID
->


levels: each has an array 

[4096 
 1024 1024 1024 1024 
 256 256 ... 
 64 ...
 16 ...
 4  ...]

 must be

 number of layers is num / 4 until output is <= 4

Cell(x,y)
Cell(x,y), layer

number of layers.

access via layer ...
convert a cell into 

*/

/*
Assume: world size is a square wth width of 4, 16, 64, 256, 1024, 4096, ...

std::vector<int> = [count in ]


*/

// struct ParkingIDX

// using 

// struct Node {
//     int value;
//     IDX parent; 
//     std::array<IDX> children; //idx

// }

// class ParkingManager {
//     const BaseWorld& base;

// public:
//     ParkingManager() {}
//     ParkingManager(const BaseWorld& bw): base(bw) {


//     }
// };