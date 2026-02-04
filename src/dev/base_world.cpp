#include "base_world.hpp"
#include <godot_cpp/classes/image.hpp>
#include "../input_package.hpp"

using namespace godot;

BaseWorld::BaseWorld(): valid(false), cols(0), rows(0), tt(), tm(), speed(), dir(), sec_per_step(0), feet_per_cell(0) {}

BaseWorld::BaseWorld(const Ref<InputPackage> input):
    valid(true),
    cols(input->get_cols()), rows(input->get_rows()),
    sec_per_step(input->get_sec_per_step()), feet_per_cell(input->get_feet_per_cell()),
    tt(input->get_tt()), tm(input->get_tm()), dir(input->get_dir()), 
    speed(input->get_mph(), input->get_sec_per_step(), input->get_feet_per_cell()) {}



// Ref<Image> BaseWorld::emulate_image_r8(int cols, int rows, uint8_t fill, std::vector<uint8_t> pop) {
//     Ref<Image> image = Image::create(cols, rows, false, Image::FORMAT_R8);
//     image->fill(Color(fill / 255.0, 0, 0, 1));
//     if (pop.empty()) { return image; }
    
//     // Iterate through each pixel and set values from pop (cycling through)
//     int pop_index = 0;
//     for (int y = 0; y < rows; y++) {
//     for (int x = 0; x < cols; x++) {
//         image->set_pixel(x, y, Color(pop[pop_index] / 255.0, 0, 0, 1));
//         pop_index = (pop_index + 1) % pop.size(); // Cycle through pop
//     }}

//     return image;
// }

// Ref<Image> BaseWorld::emulate_image_r8_from_matrix(Matrix<uint8_t> matrix) {
//     Ref<Image> image = Image::create(matrix.cols, matrix.rows, false, Image::FORMAT_R8);
    
//     for (int y = 0; y < matrix.rows; y++) {
//     for (int x = 0; x < matrix.cols; x++) {
//         uint8_t value = matrix.at(Cell(x, y));
//         image->set_pixel(x, y, Color(value / 255.0, 0, 0, 1));
//     }}

//     return image;
// }