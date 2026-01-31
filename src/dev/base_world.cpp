#include "base_world.hpp"
#include <godot_cpp/classes/image.hpp>

using namespace godot;

BaseWorld::BaseWorld(): valid(false), cols(0), rows(0), tt(), tm(), speed(), dir(), sec_per_step(0), feet_per_cell(0) {}

BaseWorld::BaseWorld(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_mph, const Ref<Image> p_dir, int p_sec_per_step, int p_feet_per_cell): 
    valid(true), 
    cols(p_tt->get_width()), rows(p_tt->get_height()),
    sec_per_step(p_sec_per_step), feet_per_cell(p_feet_per_cell),
    tt(p_tt), tm(p_tm), speed(p_mph), dir(p_dir) {}

Ref<Image> BaseWorld::emulate_image_r8(int cols, int rows, uint8_t fill, std::vector<uint8_t> pop) {
    Ref<Image> image = Image::create(cols, rows, false, Image::FORMAT_R8);
    image->fill(Color(fill / 255.0, 0, 0, 1));
    if (pop.empty()) { return image; }
    
    // Iterate through each pixel and set values from pop (cycling through)
    int pop_index = 0;
    for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
        image->set_pixel(x, y, Color(pop[pop_index] / 255.0, 0, 0, 1));
        pop_index = (pop_index + 1) % pop.size(); // Cycle through pop
    }}

    return image;
}