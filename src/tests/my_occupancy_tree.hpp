#pragma once
#include <vector>
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

All Parking vs all Building
vs half parking and half building


*/

struct Result {
    OccupancyTree tree;
    bool pass;
};

struct MyOccupancyTree {
    static constexpr uint32_t W2 = 2;
    static constexpr uint32_t DEPTH_W2 = 1-1;
    static constexpr int COUNT_W2 = 1*1;

    static constexpr uint32_t W4 = 4;
    static constexpr uint32_t DEPTH_W4 = 2-1;
    static constexpr int COUNT_W4 = 1*1+2*2;

    static constexpr uint32_t W8 = 8;
    static constexpr uint32_t DEPTH_W8 = 3-1;
    static constexpr int COUNT_W8 = 1*1+2*2+4*4;

    inline static const std::vector<uint32_t> NONE_TREE_W2 = {0};
    inline static const std::vector<uint32_t> NONE_TREE_W4 = {0, 0, 0, 0, 0};
    inline static const std::vector<uint32_t> NONE_TREE_W8 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    inline static const std::vector<uint32_t> FULL_TREE_W2 = {4};
    inline static const std::vector<uint32_t> FULL_TREE_W4 = {16, 16/4, 16/4, 16/4, 16/4};
    inline static const std::vector<uint32_t> FULL_TREE_W8 = {64, 64/4, 64/4, 64/4, 64/4, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16, 64/16};
    inline static const std::vector<uint32_t> HALF_TREE_W2 = {2};
    inline static const std::vector<uint32_t> HALF_TREE_W4 = {8, 8/4, 8/4, 8/4, 8/4};
    inline static const std::vector<uint32_t> HALF_TREE_W8 = {32, 32/4, 32/4, 32/4, 32/4, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16, 32/16};

    inline static OccupancyTree TREE_W2_NONE = OccupancyTree(W2, DEPTH_W2, COUNT_W2, NONE_TREE_W2, NONE_TREE_W2);
    inline static OccupancyTree TREE_W4_NONE = OccupancyTree(W4, DEPTH_W4, COUNT_W4, NONE_TREE_W4, NONE_TREE_W4);
    inline static OccupancyTree TREE_W8_NONE = OccupancyTree(W8, DEPTH_W8, COUNT_W8, NONE_TREE_W8, NONE_TREE_W8);
    inline static OccupancyTree TREE_W2_FULL_PARKING = OccupancyTree(W2, DEPTH_W2, COUNT_W2, FULL_TREE_W2, NONE_TREE_W2);
    inline static OccupancyTree TREE_W4_FULL_PARKING = OccupancyTree(W4, DEPTH_W4, COUNT_W4, FULL_TREE_W4, NONE_TREE_W4);
    inline static OccupancyTree TREE_W8_FULL_PARKING = OccupancyTree(W8, DEPTH_W8, COUNT_W8, FULL_TREE_W8, NONE_TREE_W8);
    inline static OccupancyTree TREE_W2_FULL_BUILDING = OccupancyTree(W2, DEPTH_W2, COUNT_W2, NONE_TREE_W2, FULL_TREE_W2);
    inline static OccupancyTree TREE_W4_FULL_BUILDING = OccupancyTree(W4, DEPTH_W4, COUNT_W4, NONE_TREE_W4, FULL_TREE_W4);
    inline static OccupancyTree TREE_W8_FULL_BUILDING = OccupancyTree(W8, DEPTH_W8, COUNT_W8, NONE_TREE_W8, FULL_TREE_W8);
    inline static OccupancyTree TREE_W2_HALF_P_B = OccupancyTree(W2, DEPTH_W2, COUNT_W2, HALF_TREE_W2, HALF_TREE_W2);
    inline static OccupancyTree TREE_W4_HALF_P_B = OccupancyTree(W4, DEPTH_W4, COUNT_W4, HALF_TREE_W4, HALF_TREE_W4);
    inline static OccupancyTree TREE_W8_HALF_P_B = OccupancyTree(W8, DEPTH_W8, COUNT_W8, HALF_TREE_W8, HALF_TREE_W8);

    static OccupancyTree create(int cols, int rows, TT fill_tt) {
        Ref<InputPackage> input = MyInputPackage::create(cols, rows, fill_tt, TM(), Dir(), MPH());
        BaseWorld base = BaseWorld(input);
        return OccupancyTree(base);
    }

    static OccupancyTree create(int cols, int rows, const std::vector<TT>& list_tt) {
        Ref<InputPackage> input = MyInputPackage::create(cols, rows, list_tt, {}, {}, {});
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