#pragma once
#include "../dev/occupancy_tree.hpp"
#include "my_input_package.hpp"

// create a base world with TT of building and parking mixed in width = 1,2,4,8,16,...
// I need a printer
using namespace godot;

/*

{} is parking
[] is building
XX is none

example:
8x8
[] []

ex
4x4

2x2


*/

struct Result {
    OccupancyTree tree;
    bool pass;
};

struct MyOccupancyTree {

    static OccupancyTree create(int cols, int rows, TT fill_tt) {
        Ref<InputPackage> input = MyInputPackage::create(cols, rows, fill_tt, TM(), Dir(), MPH());
        BaseWorld base = BaseWorld(input);
        return OccupancyTree(base);
    }



    static void print(const OccupancyTree& tree) {
        const uint32_t width = tree.get_width();
        const uint32_t depth = tree.get_depth();
        const uint32_t count = tree.get_count();
        const std::vector<uint32_t>& parking_tree = tree.get_parking_tree();
        const std::vector<uint32_t>& building_tree = tree.get_building_tree();
        
        print_line("Tree: width=" + String::num_int64(width) + 
                "  depth=" + String::num_int64(depth) + 
                "  count=" + String::num_int64(count));
        
        String indexes = "idx:      ";
        String parking = "parking:  ";
        String building = "building: ";
        
        for (uint32_t i = 0; i < count; i++) {
            // Format index with padding (00, 01, 02, ...)
            if (i < 10) {
                indexes += "0" + String::num_int64(i) + " ";
            } else {
                indexes += String::num_int64(i) + " ";
            }
            
            // Format parking value with padding
            if (parking_tree[i] < 10) {
                parking += "0" + String::num_int64(parking_tree[i]) + " ";
            } else {
                parking += String::num_int64(parking_tree[i]) + " ";
            }
            
            // Format building value with padding
            if (building_tree[i] < 10) {
                building += "0" + String::num_int64(building_tree[i]) + " ";
            } else {
                building += String::num_int64(building_tree[i]) + " ";
            }
        }
        
        print_line(indexes);
        print_line(parking);
        print_line(building);
    }
};