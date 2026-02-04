// /*
// Experiment 1: 
// * Given: read-only user defined Speed data in the form ImageR8(4096x4096).
// * Find:  technique with the fastest LOAD and data READ times.
// * LOAD Time: time to complete any neccisary operations before starting to READ the data.
// * READ Time: time to get a Speed object from the matrix and compare the Speed to Speed(0) and iterate a counter.
// E1 Tech1: 
// * LOAD: store references to the given image.
// * READ: each px -> uint8_t -> Speed(uint8_t, val, val) -> Speed == Speed(0) -> iterate
// - LOAD Time = 0 ms
// - READ1 Time = 260.61 ms (one liner const)
// - READ2 Time = 260.71 ms (multiple const variables)
// - READ3 Time = 252.63 ms (multiple variables)
// E1 Tech2: (BEST)
// * LOAD: convert the given image into a Matrix<Speed> by copying it
// * READ: each idx in data -> Speed == Speed(0) -> iterate
// - LOAD Time = 78.01 ms
// - READ1 Time = 18.01 ms (no cell just x,y)
// - READ2 Time = 18.65 ms (used cell to access)
// E1 Tech3: use a pointer to the raw image data, then access by getting byte -> cast to Speed. Skip.

// Experiment2: best way to write the data from matrix -> Imagetexture
// * use get_data and replace the data inside an image to the data in my Matrix (Matrix -> bitstring -> put bit stirng into image -> update texture from image)


// */

#pragma once
#include <chrono>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

struct MyTimingExperiments {
    using TimePoint = std::chrono::high_resolution_clock::time_point;

    static TimePoint now() {
        return std::chrono::high_resolution_clock::now();
    }

    static long long duration_ms(TimePoint start, TimePoint end) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    static void display_duration(const String& msg, TimePoint start) {
        print_line(vformat("%s %.2f", msg, duration_ms(start, now())));
    }

};



// #include <chrono>
// #include <vector>
// #include <godot_cpp/classes/image.hpp>
// #include <godot_cpp/classes/image_texture.hpp>
// #include "speed.hpp"
// #include "matrix.hpp"
// #include "cell.hpp"

// using namespace godot;

// class MyTimingExperiments {
// public:
//     static void exp1_tech1() {
//         const int a = 1;
//         const int b = 1;
//         const int fill_mph = 100;
//         Ref<Image> mph = Image::create(4096, 4096, false, Image::FORMAT_R8);
//         mph->fill(Color(fill_mph/255.0f,0,0));
//         const Speed fill_speed = Speed(fill_mph, a, b);

//         // LOAD
//         auto start = std::chrono::high_resolution_clock::now();
//         const Ref<Image> loaded_mph = mph;
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("Load exp1_tech1 in %.2f ms ", duration.count() / 1000.0));

//         // READ
//         start = std::chrono::high_resolution_clock::now();
//         int counter = 0;
//         for (int y = 0; y < 4096; y++) {
//         for (int x = 0; x < 4096; x++) {
//             const Speed speed = Speed(static_cast<uint8_t>(loaded_mph->get_pixel(x, y).r * 255), a, b);
//             if (speed == fill_speed) {counter++;}
//         }}
//         end = std::chrono::high_resolution_clock::now();
//         duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("READ1 exp1_tech1 in %.2f ms with %d/%d", duration.count() / 1000.0, counter, 4096*4096));

//         // READ2
//         start = std::chrono::high_resolution_clock::now();
//         counter = 0;
//         for (int y = 0; y < 4096; y++) {
//         for (int x = 0; x < 4096; x++) {
//             const Color color = loaded_mph->get_pixel(x, y);
//             const uint8_t val = static_cast<uint8_t>(color.r * 255);
//             const Speed speed = Speed(val, a, b);
//             if (speed == fill_speed) {counter++;}
//         }}
//         end = std::chrono::high_resolution_clock::now();
//         duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("READ2 exp1_tech1 in %.2f ms with %d/%d", duration.count() / 1000.0, counter, 4096*4096));

//         // READ3
//         start = std::chrono::high_resolution_clock::now();
//         counter = 0;
//         for (int y = 0; y < 4096; y++) {
//         for (int x = 0; x < 4096; x++) {
//             Color color = loaded_mph->get_pixel(x, y);
//             uint8_t val = static_cast<uint8_t>(color.r * 255);
//             Speed speed = Speed(val, a, b);
//             if (speed == fill_speed) {counter++;}
//         }}
//         end = std::chrono::high_resolution_clock::now();
//         duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("READ3 exp1_tech1 in %.2f ms with %d/%d", duration.count() / 1000.0, counter, 4096*4096));
//     }

//     static void exp1_tech2() {
//         const int a = 1;
//         const int b = 1;
//         const int fill_mph = 100;
//         Ref<Image> mph = Image::create(4096, 4096, false, Image::FORMAT_R8);
//         mph->fill(Color(fill_mph/255.0f,0,0));
//         const Speed fill_speed = Speed(fill_mph, a, b);

//         // LOAD
//         auto start = std::chrono::high_resolution_clock::now();
//         const Matrix<Speed> loaded_speed = Matrix<Speed>::create_speed_matrix(mph, a, a);
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("Load exp1_tech2 in %.2f ms ", duration.count() / 1000.0));

//         // READ
//         start = std::chrono::high_resolution_clock::now();
//         int counter = 0;
//         for (int y = 0; y < 4096; y++) {
//         for (int x = 0; x < 4096; x++) {
//             Speed speed = loaded_speed.at(x,y);
//             if (speed == fill_speed) {counter++;}
//         }}
//         end = std::chrono::high_resolution_clock::now();
//         duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("READ1 exp1_tech2 in %.2f ms with %d/%d", duration.count() / 1000.0, counter, 4096*4096));

//         // READ2
//         start = std::chrono::high_resolution_clock::now();
//         counter = 0;
//         for (int y = 0; y < 4096; y++) {
//         for (int x = 0; x < 4096; x++) {
//             Cell cell = Cell(x,y);
//             Speed speed = loaded_speed.at(cell);
//             if (speed == fill_speed) {counter++;}
//         }}
//         end = std::chrono::high_resolution_clock::now();
//         duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("READ2 exp1_tech2 in %.2f ms with %d/%d", duration.count() / 1000.0, counter, 4096*4096));

//     }
// };

// //************************************************* */
// // class MyTimingExperiments {
    
// // public:
//     // static void run_all_tests() {
//     //     test_image_to_speed_check();
//     //     test_vector_speed_check();
//     //     test_image_to_vector_speeds();
//     //     test_vector_speeds_to_texture();
//     // }

//     // // How long does it take to read each value inside a const 4096 Image and convert it to Speed and check does the speed == 0 iterate a counter.
//     // static void test_image_to_speed_check() {
//     //     const Ref<Image> img = Image::create(4096, 4096, false, Image::FORMAT_R8);
        
//     //     auto start = std::chrono::high_resolution_clock::now();
        
//     //     int counter = 0;
//     //     for (int y = 0; y < 4096; y++) {
//     //         for (int x = 0; x < 4096; x++) {
//     //             Color pixel = img->get_pixel(x, y);
//     //             uint8_t value = static_cast<uint8_t>(pixel.r * 255.0f);
//     //             Speed speed(value);
                
//     //             if (speed == Speed(0)) {
//     //                 counter++;
//     //             }
//     //         }
//     //     }
        
//     //     auto end = std::chrono::high_resolution_clock::now();
//     //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
//     //     print_line(vformat("Image to Speed with == 0 check completed in %.2f ms (counter: %d)", duration.count() / 1000.0, counter));
//     // }

//     // // How long does it take to read each value inside a const 4096x4096 vector of speeds and check does the speed == 0 iterate a counter
//     // static void test_vector_speed_check() {
//     //     const Matrix<Speed> matrix(4096, 4096);
        
//     //     auto start = std::chrono::high_resolution_clock::now();
        
//     //     int counter = 0;
//     //     for (int i = 0; i < 4096 * 4096; i++) {
//     //         Speed speed = matrix.data[i];
            
//     //         if (speed == Speed(0)) {
//     //             counter++;
//     //         }
//     //     }
        
//     //     auto end = std::chrono::high_resolution_clock::now();
//     //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
//     //     print_line(vformat("Matrix<Speed> with speed == 0 check completed in %.2f ms (counter: %d)", duration.count() / 1000.0, counter));
//     // }

//     // // How long does it take to convert a const 4096 Image to a const 4096x4096 matrix of speeds.
//     // static void test_image_to_vector_speeds() {
//     //     const Ref<Image> img = Image::create(4096, 4096, false, Image::FORMAT_R8);
        
//     //     auto start = std::chrono::high_resolution_clock::now();
        
//     //     PackedByteArray byte_array = img->get_data();
//     //     Matrix<Speed> speeds = Matrix<Speed>(4096,4096);
        
//     //     for (int i = 0; i < byte_array.size(); i++) {
//     //         speeds.push_back(Speed(byte_array[i]));
//     //     }
        
//     //     auto end = std::chrono::high_resolution_clock::now();
//     //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
//     //     print_line(vformat("Image to Matrix<Speed> conversion completed in %.2f ms", duration.count() / 1000.0));
//     // }

//     // // how long does it take to convert a non const 4096x4096 vector of speeds to an ImageTexture
//     // static void test_vector_speeds_to_texture() {
//     //     Matrix<Speed> matrix(4096, 4096);
        
//     //     auto start = std::chrono::high_resolution_clock::now();
        
//     //     PackedByteArray byte_array;
//     //     byte_array.resize(4096 * 4096);
        
//     //     for (int i = 0; i < 4096 * 4096; i++) {
//     //         byte_array[i] = matrix.data[i].val;
//     //     }
        
//     //     Ref<Image> img = Image::create_from_data(4096, 4096, false, Image::FORMAT_R8, byte_array);
//     //     Ref<ImageTexture> texture = ImageTexture::create_from_image(img);
        
//     //     auto end = std::chrono::high_resolution_clock::now();
//     //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
//     //     print_line(vformat("Matrix<Speed> to Image->ImageTexture conversion completed in %.2f ms", duration.count() / 1000.0));
//     // }

//     //************************************************* */