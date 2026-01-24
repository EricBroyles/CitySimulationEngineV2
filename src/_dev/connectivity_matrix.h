// #pragma once
// #include <array>
// #include <vector>
// #include "world.h"
// #include "matrix.h"
// #include <unordered_map>

// /*
// Connectivity Matrix (CM)
// * each cell ig given a cm_group_id which indicated to what cells it is connected to.
// * connected only requires 
// */

// struct CMID {
//     static constexpr int INVALID = -2;
//     static constexpr int BARRIER = -1;
//     int val;
//     CMGroup(): val(INVALID_ID) {}
//     CMGroup(int v): val(v) {}
//     bool is_invalid() const {return val <= INVALID;}
//     bool is_barrier() const {return val == BARRIER;}
//     void invalid() {val(INVALID);}
//     void barrier() {val(BARRIER);}
//     CMID& operator++() {++id; return *this;} //++CMID only. 
//     bool  operator==(const CMID& other) const {return val == other.val;}
// };

// struct Kernel {
//     static constexpr int SIZE = 4
//     static constexpr std::array<Cell,SIZE> SHIFT = {
//         Cell(0,0),
//         Cell(1,0),
//         Cell(0,1),
//         Cell(1,1)};
//     static constexpr std::array<Direction,SIZE> RELEVANT = {
//         Direction(Direction::E & Direction::S & Direction::SE),
//         Direction(Direction::W & Direction::S & Direction::SW),
//         Direction(Direction::E & Direction::N & Direction::NE),
//         Direction(Direction::W & Direction::N & Direction::NW)};
//     Kernel(const World& world, const Cell& cell, Matrix<CMID>& matrix_with_barriers) {
//         std::array<Direction,SIZE> dirs; //defualt initialized to NONE
//         for (int i = 0; i < SIZE; i++) {
//             Cell ci = cell + SHIFT[i];
//             if !(matrix_with_barriers.at(ci).is_barrier()) {
//                 Direction::and(world.get_dir(ci), RELEVANT[i])
//             }
//         }
//         int fill = 0
//         for (int i = 0; i < SIZE-1; i++) {
//         for (int j=i+1; j < SIZE  ; j++) {
//             if (Direction::and(dirs[i]), dirs[j] == 0) {continue;}
//             Cell fill_cell = cell + SHIFT[j];
//             matrix_with_barriers.at(fill_cell) = 
//             fill++;


//         }
//         }
//         // unorderded map, from all possible values to the idx
//         // compare 0 direction to 1,2,3 directions if any are non zero replace it with 0 CMID


        

//     }
// };

// class CMData {
// private:
//     bool is_walk_barrier(const World& world, const Cell& cell, const Direction& dir) const {
//         if (world.can_walk(cell) && !dir.is_none()) {return false;}
//         return true;     
//     }
//     bool is_drive_barrier(const World& world, const Cell& cell, const Direction& dir) const {
//         if (world.can_drive(cell) && !dir.is_none()) {return false;}
//         return true;      
//     }
//     void set_barriers(const World& world) {
//         int i = 0;
//         for (int r = 0; r < world.rows; r++) {
//         for (int c = 0; c < world.cols; c++) {
//             Cell      cell = Cell(c,r);
//             Direction dir  = world.get_dir(cell);
//             walk[i]  = is_walk_barrier(world, cell, dir)  ? CMID(CMID::BARRIER) : CMID(i);
//             drive[i] = is_drive_barrier(world, cell, dir) ? CMID(CMID::BARRIER) : CMID(i);
//             ++i;
//         }}
//     }
//     void set_cmid(const World& world) {
//         for (int r = 0; r < world.rows-1; r++) {
//         for (int c = 0; c < world.cols-1; c++) {


//                 // Kernel 
//                 Cell cell = Cell(c,r);
                

//                 // I need to get the direction for all 4 cells in the kernal ()
//                 // I need to get the CMID for all 4 cells (idx)

//                 Direction dir  = world.get_dir(cell);
//                 // walk[i]  = is_walk_barrier(world, cell, dir)  ? CMID(CMID::BARRIER) : CMID(i);
//                 // drive[i] = is_drive_barrier(world, cell, dir) ? CMID(CMID::BARRIER) : CMID(i);
                
//         }}
//     }
// public:
//     Matrix<CMID> walk;
//     Matrix<CMID> drive;
//     CMData(): walk(), drive() {}
//     CMData(const World& world): walk(world.cols, world.rows), drive(world.cols, world.rows) {set_barriers(world);set_cmid(world);}
// };



// class Kernel {
//     /*
//     Given a topleft cell
//     Sweep this kernel across rows: [0,rows-1) and cols: [0, cols-1) of preset matrix
//     Preset matrix: std::vector<CMID> 
//     * all barriers are labeled
//     * all NONE direction are labeled barrier
//     * all others given unique CMID based on idx
//     */
// public:
//     Kernel(const World& world, const Cell& cell, std::vector<CMID>& preset_matrix){
//         int idx = cell.get_rowwise_idx(world.cols);

//     }


    




//     idx +1
//     idx + num_cols
//     idx + num_cols +1
//     // pass in a target cell (top left corner) -> get the directions for all 3 other cells
//     //set direction to 0 if barrier
//     //given the direction 
// }















// // *******************************************

// struct CMGroup {
//     static constexpr int INVALID_ID = -1;
//     int id;
//     CMGroup(): id(INVALID_ID) {}
//     explicit CMGroup(int v): id(v) {}
//     bool is_valid() const {return id > INVALID_ID;}
//     void invalid() {id(INVALID_ID);}
//     CMGroup& operator++() {++id; return *this;} // Prefix ++ : makes the id 1 larger
//     bool operator==(const CMGroup& other) const {return id == other.id;}
// };

// struct CMData { 
// public:
//     // Needed because walk,drive init together and then are const.
//     std::vector<CMGroup> walk;
//     std::vector<CMGroup> drive;
//     CMData(): walk(), drive() {}
//     CMData(const World& world): valid(true), walk(world.num_cells), drive(world.num_cells) {
//         int idx = 0;
//         for (int r = 0; r < world.rows; r++) {
//         for (int c = 0; c < world.cols; c++) {
//             Cell cell = Cell(c,r);
//             Direction dir = world.get_dir(cell);

            



//             set_walk_group(world, idx, cell, dir);
//             set_drive_group(world, idx, cell, dir);

//             // walk[idx]  = get_walk_group(world, cell, dir, CMGroup(idx));
//             // drive[idx] = get_drive_group(world, cell, dir, CMGroup(idx));
//             idx++;
//         }}

//         // After this I need to look through again and replace all non walk and non drive cells with none

//     }
// private:

//     static void get_walk_group(const World& world, int idx, const Cell& cell, const Direction& dir) {
//         if !(world.can_walk_at(cell)) {return CMGroup();}
//         CMGroup group = walk[idx];
//         if !(group.is_valid()) {group = CMGroup(idx);}
//         if (dir.is_none()) {return group;}

//         for (int i=0; i < Cell::NUM_ADJACENT; i++) {
//             SoloDirection solo_dir = SoloDirection(dir, i);
//             if (solo_dir.is_none()) {continue;}
//             Cell adj_cell = cell.get_adjacent(solo_dir);
//             if (world.out_of_bounds(adj_cell)) {continue;} //handles invalid cells
//             if !(world.can_walk_at(adj_cell)) {continue;}
//             int adj_idx = adj_cell.get_rowwise_idx(world.cols);
//             CMGroup adj_group = walk[adj_idx];

//             // if it is invalid replace with my
//             // if it is smaller replace this with adj
//             // if it is larger replace with my
//             if 
//             // need to check is it walkable

            
//             int id = adj_cell.get_rowwise_idx(world.cols)
//             return CMGroup(id);}
//         }

        
//     }
// };








// //         CMgroup group = 0; 
// //         for (int r = 0; r < world.rows; r++) {
// //         for (int c = 0; c < world.cols; c++) {
// //             // if invalid -> group is group.
// //             // for all 8. 
// //             // can I move in that direction. get adj_cell group. if adj_cell_group is ivalid set to my. if adj_cell_group is smaller, replace mine with the smaller. it should never be larger?.

// //             //get smallest CMgroup (if its not invlaiude, then I know its the smallest it can be)
// //             //push CMgroup downstream and upstream to any unassigned. 

// //             // look at all allowed upstream dir. (NW,N,NE,W). check if adj_cell is in bounds. if so it must have a smaller group so assign my group to its, terminate this search
// //             // look at all allowed downstream dir. (order does not matter E, SW, S, SE). if 


// //             // *if cell group is invalid -> 
// //             // ce
// //             // cell group is group -> cont
// //             // else:
// //             //  



// //             // cell group is group 
// //             // for all 4 up steam directions: chekc can I move in that direction from this cell. then if I get one of their values set it as this cells group and stop
// //             // for all 4 down stream directions: for the ones I can move from this cell give them a group id of my value.
// //             // *else continue
// //             // 



// //             Cell cell = Cell(c,r);
// //             Direction dir = world.get_dir(cell);

// //             //
            

// //             ++group;
// //         }}
// //     } 
// // }

// // 

// // class ConnectivityMatrix {
// // private:
// //     bool valid;
// //     std::vector<CMGroup> walk;
// //     std::vector<CMGroup> drive;
// // public:
// //     ConnectivityMatrix(): valid(false), walk(), drive() {}
// //     ConnectivityMatrix(const World& world): valid(true), walk(world.num_cells), drive(world.num_cells) {

// //         walk(world.num_cells);
// //         for (int r = 0; r < world.rows; r++) {
// //         for (int c = 0; c < world.cols; c++) {

// //         }}
// //     }
// //     bool is_valid() const {return valid;}
// //     void invalid() {valid(false);}
// // };



// // THis does not work as inteded


// class ConnectivityMatrix {
// private:
//     bool valid;
//     static constexpr std::array<Direction,4> SEARCH_DIRECTIONS = {Direction(Direction::NE), Direction(Direction::N),Direction(Direction::NW), Direction(Direction::W)};
//     const std::vector<CMGroup> walk;
//     const std::vector<CMGroup> drive;
//     CMgroup get_group(const World& world, const Cell& cell, const Direction& dir) const {
//         for (Direction search: SEARCH_DIRECTIONS) {
//             if (Direction::no_matches(dir,search)) {continue;}
//             Cell adj_cell = cell.get_adjacent(search)
//             if (world.out_of_bounds(adj_cell)) {continue;} //handles invalid cells
//             int id = adj_cell.get_rowwise_idx(world.cols)
//             return CMGroup(id);}
//         return CMGroup();
//     }
//     CMGroup get_walk_group(const World& world, const Cell& cell, const Direction& dir) const {
//         if !(world.can_walk_at(cell)) {return CMGroup();}
//         return get_group(world, cell, dir);
//     }
//     CMGroup get_drive_group(const World& world, const Cell& cell, const Direction& dir) const {
//         if !(world.can_drive_at(cell)) {return CMGroup();}
//         return get_group(world, cell, dir);
//     }
// public:
//     ConnectivityMatrix(): valid(false) {}
//     ConnectivityMatrix(const World& world): valid(true) {
//         for (int r = 0; r < world.rows; r++) {
//         for (int c = 0; c < world.cols; c++) {
//             Cell cell = Cell(c,r);
//             Direction dir = world.get_dir(cell);
//             int idx = cell.get_rowwise_idx(world.cols);
//             walk[idx] = get_walk_group(world, cell, dir);
//             drive[idx] = get_drive_group(world, cell, dir);
//         }}
//     }
//     bool is_valid() const {return valid;}
//     void invalid() {valid(false);}
//     // CMGroup get_walk_group(int c, int r); //use cell
//     // CMGroup get_drive_group(int c, int r);
//     // bool is_walk_connected(int c1, int r1, int c2, int r2);
//     // bool is_drive_connected()
    
    
// };

