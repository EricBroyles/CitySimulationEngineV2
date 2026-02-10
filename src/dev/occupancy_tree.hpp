/*
8x8
00 01 02 03 04 05 06 07
08 09 10 11 12 13 14 15
16 17 18 19 20 21 22 23
24 25 26 27 28 29 30 31
32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47
48 49 50 51 52 53 54 55
56 57 58 59 60 61 62 63

aa aa bb bb cc cc dd dd
aa aa bb bb cc cc dd dd
ee ee ff ff gg gg hh hh 
ee ee ff ff gg gg hh hh 
ii ii jj jj kk kk ll ll 
ii ii jj jj kk kk ll ll 
mm mm nn nn oo oo pp pp 
mm mm nn nn oo oo pp pp

AA AA AA AA BB BB BB BB
AA AA AA AA BB BB BB BB
AA AA AA AA BB BB BB BB
AA AA AA AA BB BB BB BB
CC CC CC CC DD DD DD DD
CC CC CC CC DD DD DD DD
CC CC CC CC DD DD DD DD
CC CC CC CC DD DD DD DD

$$ $$ $$ $$ $$ $$ $$ $$
$$ $$ $$ $$ $$ $$ $$ $$
$$ $$ $$ $$ $$ $$ $$ $$
$$ $$ $$ $$ $$ $$ $$ $$
$$ $$ $$ $$ $$ $$ $$ $$
$$ $$ $$ $$ $$ $$ $$ $$
$$ $$ $$ $$ $$ $$ $$ $$
$$ $$ $$ $$ $$ $$ $$ $$

depth: 2^(depth+1) = width
count: (width*width-1)/3

depth = 2
count = 21
                                                                      | 3 is not part of depth
                                                                      | -> left inside base
depth: 00 01 01 01 01 02 02 02 02 02 02 02 02 02 02 02 02 02 02 02 02 | 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 ...
tree:  $$ AA BB CC DD aa bb cc dd ee ff gg hh ii jj kk ll mm nn oo pp | 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 ...
idx :  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 | ...

count at each depth = 4^depth

given: count, desired depth q, total depth d
find:  all the tree nodes before the q
before_q = floor(count / 4^(d-a+1))

given: Cell c, desired depth q, total depth d
find:  the tree idx
ex:    cell(4,4), 02, 02 -> kk = 15 
ex:    cell(7,7), 01, 02 -> DD = 04
ex:    cell(6,2), 02, 02 -> hh = 12

cell(4,4) / 2^(d-a+1) -> cell(2,2) -> r * cols + c -> cols = width / 2^(d-a+1) -> 2 * 4 + 2 = 10, so 10th spot inside that depth. 
now find the number before depth q. before_q + 10 = 5 + 10 = 15


*/
#pragma once
#include <vector>
#include <bit>
#include "cell.hpp"
#include "terrain_type.hpp"

using namespace godot;

class OccupancyTree {
private:
    static constexpr TT PARKING  = TT(TT::PARKING);
    static constexpr TT BUILDING = TT(TT::BUILDING);
    const BaseWorld& base = *(BaseWorld*)nullptr;
    const uint32_t width = 0;
    const uint32_t depth = 0;
    const uint32_t count = 0;
    std::vector<uint32_t> parking_tree;
    std::vector<uint32_t> building_tree;

    static uint32_t calc_depth(uint32_t width) {
        return std::bit_width(width) - 2;
    }

    static uint32_t calc_count(uint32_t width) {
        return (width * width - 1) / 3;
    }

    static uint32_t calc_start_idx(uint32_t count, uint32_t depth, uint32_t desired_depth) {
        return count / (1 << (2 * (depth - desired_depth + 1)));
    }

    static uint32_t calc_nodes_at_depth(uint32_t desired_depth) {
        return (1 << (2 * desired_depth));
    }

    void set_tree_from_base() {
        // Set the deepest level from base grid
        const uint32_t tree_start_idx = calc_start_idx(count, depth, depth);
        const uint32_t grid_size = width / 2;  // Size of the deepest tree level grid
        
        for (uint32_t r = 0; r < width; r++) {
            for (uint32_t c = 0; c < width; c++) {
                Cell cell = Cell(c, r);
                
                // Map to higher tree cell (each tree cell covers 2x2 base cells)
                uint32_t tree_r = r / 2;
                uint32_t tree_c = c / 2;
                uint32_t tree_idx = tree_start_idx + tree_r * grid_size + tree_c;
                
                if (base.get_tt(cell) == PARKING) { 
                    parking_tree[tree_idx]++; 
                }
                else if (base.get_tt(cell) == BUILDING) { 
                    building_tree[tree_idx]++; 
                }
            }
        }
    }

    void set_tree_after_base() {
        // Build tree bottom-up from depth-1 to 0
        for (int q = depth - 1; q >= 0; q--) {
            const uint32_t new_tree_start_idx = calc_start_idx(count, depth, q);
            const uint32_t old_tree_start_idx = calc_start_idx(count, depth, q + 1);
            const uint32_t old_grid_size = 1 << (q + 1);  // Grid side length at level q+1
            const uint32_t new_grid_size = 1 << q;        // Grid side length at level q
            // Each node at level q combines 4 nodes from level q+1
            for (uint32_t r = 0; r < new_grid_size; r++) {
                for (uint32_t c = 0; c < new_grid_size; c++) {
                    uint32_t new_idx = new_tree_start_idx + r * new_grid_size + c;
                    
                    // The 4 children are at positions (2r, 2c), (2r, 2c+1), (2r+1, 2c), (2r+1, 2c+1)
                    // in the old grid
                    uint32_t child_r = r * 2;
                    uint32_t child_c = c * 2;
                    
                    uint32_t child_tl = old_tree_start_idx + (child_r + 0) * old_grid_size + (child_c + 0);
                    uint32_t child_tr = old_tree_start_idx + (child_r + 0) * old_grid_size + (child_c + 1);
                    uint32_t child_bl = old_tree_start_idx + (child_r + 1) * old_grid_size + (child_c + 0);
                    uint32_t child_br = old_tree_start_idx + (child_r + 1) * old_grid_size + (child_c + 1);
                    
                    parking_tree[new_idx] = 
                        parking_tree[child_tl] + 
                        parking_tree[child_tr] + 
                        parking_tree[child_bl] + 
                        parking_tree[child_br];
                    
                    building_tree[new_idx] = 
                        building_tree[child_tl] + 
                        building_tree[child_tr] + 
                        building_tree[child_bl] + 
                        building_tree[child_br];
                }
            }
        }
    }

public:
    OccupancyTree() {}

    OccupancyTree(const BaseWorld& bw): 
        base(bw), 
        width(bw.cols), 
        depth(calc_depth(width)),
        count(calc_count(width)),
        parking_tree(count, 0),
        building_tree(count, 0) 
    {
        set_tree_from_base();
        set_tree_after_base();
    }

    OccupancyTree(uint32_t width, uint32_t depth, uint32_t count, uint32_t parking_tree, uint32_t building_tree):
        width(width),
        depth(depth),
        count(count),
        parking_tree(parking_tree),
        building_tree(building_tree) 
    {}

    uint32_t get_width() const {
        return width;
    }

    uint32_t get_depth() const {
        return depth;
    }

    uint32_t get_count() const {
        return count;
    }

    const std::vector<uint32_t>& get_parking_tree() const {
        return parking_tree;
    }

    const std::vector<uint32_t>& get_building_tree() const {
        return building_tree;
    }

    bool operator==(const OccupancyTree& other) const {
        return 
            width == other.width && 
            depth == other.depth &&
            count == other.count &&
            parking_tree  == other.parking_tree &&
            building_tree == other.building_tree;
    }
};
