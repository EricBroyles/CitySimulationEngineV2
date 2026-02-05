#include "tester.hpp"
#include "tests/my_connectivity_matrix.hpp"

using namespace godot;

void Tester::_bind_methods() {
    ClassDB::bind_method(D_METHOD("construct_cm"), &Tester::construct_cm);
}

void Tester::construct_cm() const {
    print_line("==================================");
    print_line("@TEST: construct_cm"); int passed = 0, total = 0;

    /*
    TT VARIES while Dir is ALL
    */

    {
        CM cm = MyCM::create(4, 4, TT(TT::NONE), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::NONE, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::ROAD), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_FULL_4x4) && MyCM::validate_num_groups(cm, 0, 1);
        print_line(vformat("[Pass: %s] TT::ROAD, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::WALKWAY), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_FULL_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 1, 0);
        print_line(vformat("[Pass: %s] TT::WALKWAY, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::CROSSWALK), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_FULL_4x4, MyCM::CMID_FULL_4x4) && MyCM::validate_num_groups(cm, 1, 1);
        print_line(vformat("[Pass: %s] TT::CROSSWALK, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_FULL_4x4, MyCM::CMID_FULL_4x4) && MyCM::validate_num_groups(cm, 1, 1);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::BUILDING), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_FULL_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 1, 0);
        print_line(vformat("[Pass: %s] TT::BUILDING, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::BARRIER), Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::BARRIER, Dir::ALL", pass)); if (pass) passed++; total++;
    }

    /*
    TT VARIES while Dir is NONE
    */

    {
        CM cm = MyCM::create(4, 4, TT(TT::NONE), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::NONE, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::ROAD), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::ROAD, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::WALKWAY), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::WALKWAY, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::CROSSWALK), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::CROSSWALK, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::BUILDING), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::BUILDING, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::BARRIER), Dir(Dir::NONE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_BARRIER_4x4, MyCM::CMID_BARRIER_4x4) && MyCM::validate_num_groups(cm, 0, 0);
        print_line(vformat("[Pass: %s] TT::BARRIER, Dir::NONE", pass)); if (pass) passed++; total++;
    }

    /*
    TT PARKING while Dir VARIES from E->SE
    */

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::E));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_HORI_4x4, MyCM::CMID_HORI_4x4) && MyCM::validate_num_groups(cm, 4, 4);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::E", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::W));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_HORI_4x4, MyCM::CMID_HORI_4x4) && MyCM::validate_num_groups(cm, 4, 4);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::W", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::N));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_VERT_4x4, MyCM::CMID_VERT_4x4) && MyCM::validate_num_groups(cm, 4, 4);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::N", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::S));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_VERT_4x4, MyCM::CMID_VERT_4x4) && MyCM::validate_num_groups(cm, 4, 4);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::S", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::NE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_POS_DIAG_4x4, MyCM::CMID_POS_DIAG_4x4) && MyCM::validate_num_groups(cm, 7, 7);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::NE", pass)); if (pass) passed++; total++;
    }

        {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::SW));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_POS_DIAG_4x4, MyCM::CMID_POS_DIAG_4x4) && MyCM::validate_num_groups(cm, 7, 7);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::SW", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::NW));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_NEG_DIAG_4x4, MyCM::CMID_NEG_DIAG_4x4) && MyCM::validate_num_groups(cm, 7, 7);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::NW", pass)); if (pass) passed++; total++;
    }

    {
        CM cm = MyCM::create(4, 4, TT(TT::PARKING), Dir(Dir::SE));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::CMID_NEG_DIAG_4x4, MyCM::CMID_NEG_DIAG_4x4) && MyCM::validate_num_groups(cm, 7, 7);
        print_line(vformat("[Pass: %s] TT::PARKING, Dir::SE", pass)); if (pass) passed++; total++;
    }

    /*
    W Connection
    */

    {
        CM cm = MyCM::create_w_connection(Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::W_CONNECTION, MyCM::W_CONNECTION) && MyCM::validate_num_groups(cm, 1, 1);
        print_line(vformat("[Pass: %s] W Connection with Dir::ALL", pass)); if (pass) passed++; total++;
    }

    /*
    Bottom Leak
    */

    {
        CM cm = MyCM::create_bottom_leak(Dir(Dir::ALL));
        // MyCM::display(cm);
        bool pass = MyCM::validate_matrices(cm, MyCM::BOTTOM_LEAK, MyCM::BOTTOM_LEAK) && MyCM::validate_num_groups(cm, 2, 2);
        print_line(vformat("[Pass: %s] Bottom Leak with Dir::ALL", pass)); if (pass) passed++; total++;
    }
 
    print_line(vformat("@Results: %d/%d", passed, total));
    print_line("==================================\n");
}



















// #include "dev\cell.hpp"
// #include "dev\vec.hpp"
// #include "dev\direction.hpp"
// #include "dev\speed.hpp"
// #include "tests/my_input_package.hpp"
// #include "dev\terrain_type.hpp"
// #include "dev\terrain_mod.hpp"
// #include "dev\matrix.hpp"
// #include "dev\image_matrix.hpp"
// #include "dev\base_world.hpp"
// #include "dev\world.hpp"
// #include "dev\cmid.hpp"
// #include "tests/my_connectivity_matrix.hpp"
// #include <godot_cpp/classes/image_texture.hpp>
// #include "tests/my_timing_experiments.hpp"



// void Tester::timing() const {
//     // print_line("hi");
//     // Ref<Image> tt_img = MyInputPackage::create_image_r8(4096, 4096, TT().val);
//     // ImageMatrix<MPH> mat = ImageMatrix<MPH>();
//     // Ref<InputPackage> input = memnew(InputPackage);
//     // InputPackage input = memnew(InputPackage(); //somthing about this is hanging?>
//     // InputPackage input = MyInputPackage::emulate(4096, 4096, TT(), TM(), Dir(), MPH());
//     // print_line(input.get_cols());
//     // print_line(input.get_rows());
//     // BaseWorld base = BaseWorld(input);
//     // print_line(base.cols);
//     // print_line(base.rows);

//     // CM cm = CM();
//     CM cm = MyConnectivityMatrix::create_from_one_tt_one_dir(4096,4096,TT(TT::PARKING), Dir(Dir::ALL));
//     // MyConnectivityMatrix::display(cm);
// }

// void Tester::timing() const {
//     {
//         MyTimingExperiments::exp1_tech1();
//         MyTimingExperiments::exp1_tech2();
//     }
//     {
//         auto start = std::chrono::high_resolution_clock::now();
//         for (int i = 0; i < 4096; i++) {
//         for (int j = 0; j < 4096; j++) {
//             volatile int dummy = i * j;
//         }}
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("4096x4096 loop completed in %.2f ms", duration.count() / 1000.0));
//     }

//     {
//         // Constant pixel value to check against
//         float pixel_value = 0.5f;
//         auto start = std::chrono::high_resolution_clock::now();
//         for (int y = 0; y < 4096; y++) {
//             for (int x = 0; x < 4096; x++) {
//                 // Do 8 checks on the constant pixel value
//                 volatile bool check1 = (pixel_value > 0.5f);
//                 volatile bool check2 = (pixel_value < 0.3f);
//                 volatile bool check3 = (pixel_value == 0.0f);
//                 volatile bool check4 = (pixel_value >= 0.7f);
//                 volatile bool check5 = (pixel_value <= 0.2f);
//                 volatile bool check6 = (pixel_value != 1.0f);
//                 volatile bool check7 = (pixel_value > 0.1f && pixel_value < 0.9f);
//                 volatile bool check8 = (pixel_value == 1.0f || pixel_value == 0.0f);
//             }
//         }
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("4096x4096 iterations with 8 checks per pixel completed in %.2f ms", duration.count() / 1000.0));
//     }

//     {
//         Ref<Image> img = Image::create(4096, 4096, false, Image::FORMAT_R8);
//         auto start = std::chrono::high_resolution_clock::now();
//         for (int y = 0; y < 4096; y++) {
//             for (int x = 0; x < 4096; x++) {
//                 // Do 8 checks on each pixel
//                 Color pixel = img->get_pixel(x, y);
                
//                 volatile bool check1 = (pixel.r > 0.5f);
//                 volatile bool check2 = (pixel.r < 0.3f);
//                 volatile bool check3 = (pixel.r == 0.0f);
//                 volatile bool check4 = (pixel.r >= 0.7f);
//                 volatile bool check5 = (pixel.r <= 0.2f);
//                 volatile bool check6 = (pixel.r != 1.0f);
//                 volatile bool check7 = (pixel.r > 0.1f && pixel.r < 0.9f);
//                 volatile bool check8 = (pixel.r == 1.0f || pixel.r == 0.0f);
//             }
//         }
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("4096x4096 image with 8 checks per pixel completed in %.2f ms", duration.count() / 1000.0));
//     }

//     {
//         const Ref<Image> img = Image::create(4096, 4096, false, Image::FORMAT_R8);
//         auto start = std::chrono::high_resolution_clock::now();
//         for (int y = 0; y < 4096; y++) {
//             for (int x = 0; x < 4096; x++) {
//                 // Do 8 checks on each pixel
//                 const Color pixel = img->get_pixel(x, y);
                
//                 volatile bool check1 = (pixel.r > 0.5f);
//                 volatile bool check2 = (pixel.r < 0.3f);
//                 volatile bool check3 = (pixel.r == 0.0f);
//                 volatile bool check4 = (pixel.r >= 0.7f);
//                 volatile bool check5 = (pixel.r <= 0.2f);
//                 volatile bool check6 = (pixel.r != 1.0f);
//                 volatile bool check7 = (pixel.r > 0.1f && pixel.r < 0.9f);
//                 volatile bool check8 = (pixel.r == 1.0f || pixel.r == 0.0f);
//             }
//         }
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("const 4096x4096 image with 8 checks per pixel completed in %.2f ms", duration.count() / 1000.0));
//     }

//     {
//         Ref<Image> img = Image::create(4096, 4096, false, Image::FORMAT_R8);
//         auto start = std::chrono::high_resolution_clock::now();
//         for (int i = 0; i < 256 * 256; i++) {
//             // Calculate x, y coordinates in the 4096 image
//             int x = i % 4096;
//             int y = i / 4096;
            
//             // Read from the image
//             Color pixel = img->get_pixel(x, y);
//             float value = pixel.r;
            
//             // Do 8 checks
//             volatile bool check1 = (value > 0.5f);
//             volatile bool check2 = (value < 0.3f);
//             volatile bool check3 = (value == 0.0f);
//             volatile bool check4 = (value >= 0.7f);
//             volatile bool check5 = (value <= 0.2f);
//             volatile bool check6 = (value != 1.0f);
//             volatile bool check7 = (value > 0.1f && value < 0.9f);
//             volatile bool check8 = (value == 1.0f || value == 0.0f);
            
//             // Set a value back to the image
//             img->set_pixel(x, y, Color(0.75f, 0.0f, 0.0f));
//         }
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("Simulate agents: 256x256 iterations (read, 8 checks, write to 4096 image) completed in %.2f ms", duration.count() / 1000.0));
//     }

//     {
//         Ref<Image> img = Image::create(4096, 4096, false, Image::FORMAT_R8);
//         auto start = std::chrono::high_resolution_clock::now();
//         std::vector<uint8_t> pixel_data;
//         pixel_data.reserve(4096 * 4096);  // Pre-allocate for efficiency
//         for (int y = 0; y < 4096; y++) {
//             for (int x = 0; x < 4096; x++) {
//                 Color pixel = img->get_pixel(x, y);
//                 uint8_t value = static_cast<uint8_t>(pixel.r * 255.0f);
//                 pixel_data.push_back(value);
//             }
//         }
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("R8 image to vector<uint8_t> conversion completed in %.2f ms", duration.count() / 1000.0));
//         print_line(vformat("Vector size: %d elements", pixel_data.size()));
//     }

//     {
//         // Create a 4096x4096 R8 image
//         Ref<Image> img = Image::create(4096, 4096, false, Image::FORMAT_R8);
        
//         auto start = std::chrono::high_resolution_clock::now();
        
//         // Get the raw data as PackedByteArray
//         PackedByteArray byte_array = img->get_data();
        
//         // Convert to std::vector
//         std::vector<uint8_t> pixel_data(byte_array.ptr(), byte_array.ptr() + byte_array.size());
        
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
//         print_line(vformat("Image to vector (using get_data) completed in %.2f ms", duration.count() / 1000.0));
//         print_line(vformat("Vector size: %d elements", pixel_data.size()));
//     }

//     {
//         std::vector<uint8_t> pixel_data(4096 * 4096, 128);  // Initialize with value 128
//         auto start = std::chrono::high_resolution_clock::now();
//         for (int i = 0; i < 4096 * 4096; i++) {
//             uint8_t value = pixel_data[i];
            
//             // Do 8 checks
//             volatile bool check1 = (value > 127);
//             volatile bool check2 = (value < 76);
//             volatile bool check3 = (value == 0);
//             volatile bool check4 = (value >= 178);
//             volatile bool check5 = (value <= 51);
//             volatile bool check6 = (value != 255);
//             volatile bool check7 = (value > 25 && value < 230);
//             volatile bool check8 = (value == 255 || value == 0);
//         }
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("Reading from vector (4096x4096) with 8 checks completed in %.2f ms", duration.count() / 1000.0));
//     }

//     {
//         const std::vector<uint8_t> pixel_data(4096 * 4096, 128);  // Initialize with value 128
//         auto start = std::chrono::high_resolution_clock::now();
//         for (int i = 0; i < 4096 * 4096; i++) {
//             const uint8_t value = pixel_data[i];
            
//             // Do 8 checks
//             volatile bool check1 = (value > 127);
//             volatile bool check2 = (value < 76);
//             volatile bool check3 = (value == 0);
//             volatile bool check4 = (value >= 178);
//             volatile bool check5 = (value <= 51);
//             volatile bool check6 = (value != 255);
//             volatile bool check7 = (value > 25 && value < 230);
//             volatile bool check8 = (value == 255 || value == 0);
//         }
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         print_line(vformat("Reading from const vector (4096x4096) with 8 checks completed in %.2f ms", duration.count() / 1000.0));
//     }

//     {
//         // Create a vector of 4096x4096 uint8_t values
//         std::vector<uint8_t> pixel_data(4096 * 4096, 128);  // Initialize with value 128
        
//         auto start = std::chrono::high_resolution_clock::now();
        
//         for (int i = 0; i < 256 * 256; i++) {
//             // Read from the vector
//             uint8_t value = pixel_data[i];
            
//             // Do 8 checks
//             volatile bool check1 = (value > 127);
//             volatile bool check2 = (value < 76);
//             volatile bool check3 = (value == 0);
//             volatile bool check4 = (value >= 178);
//             volatile bool check5 = (value <= 51);
//             volatile bool check6 = (value != 255);
//             volatile bool check7 = (value > 25 && value < 230);
//             volatile bool check8 = (value == 255 || value == 0);
            
//             // Write back to the vector
//             pixel_data[i] = 192;
//         }
        
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
//         print_line(vformat("256x256 iterations (read, 8 checks, write to vector) completed in %.2f ms", duration.count() / 1000.0));
//     }

//     {
//         // Create a vector of 4096x4096 uint8_t values
//         std::vector<uint8_t> pixel_data(4096 * 4096, 128);
        
//         auto start = std::chrono::high_resolution_clock::now();
        
//         // Create PackedByteArray from vector
//         PackedByteArray byte_array;
//         byte_array.resize(pixel_data.size());
//         memcpy(byte_array.ptrw(), pixel_data.data(), pixel_data.size());
        
//         // Create Image from raw data
//         Ref<Image> img = Image::create_from_data(4096, 4096, false, Image::FORMAT_R8, byte_array);
        
//         // Create texture from image
//         Ref<ImageTexture> texture = ImageTexture::create_from_image(img);
        
//         auto end = std::chrono::high_resolution_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
//         print_line(vformat("Vector to texture conversion completed in %.2f ms", duration.count() / 1000.0));
   
//     }

// }

// void Tester::cm_tests() const {
//     print_line("==================================");
//     print_line("@Test: Connectivity Matrix in World");


//     print_line("<<<<Test all TT with Direction ALL>>>>\n");
//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::NONE),Direction(Direction::ALL));
//     print_line("[Pass: CHECK] TT = NONE, Direction = ALL -> all CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::ALL));
//     print_line("[Pass: CHECK] TT = ROAD, Direction = ALL -> walk CMID = -1, drive CMID = 0"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::ALL));
//     print_line("[Pass: CHECK] TT = WALKWAY, Direction = ALL -> walk CMID = 0, drive CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::CROSSWALK),Direction(Direction::ALL));
//     print_line("[Pass: CHECK] TT = CROSSWALK, Direction = ALL -> all CMID = 0"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::PARKING),Direction(Direction::ALL));
//     print_line("[Pass: CHECK] TT = PARKING, Direction = ALL -> all CMID = 0"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::BUILDING),Direction(Direction::ALL));
//     print_line("[Pass: CHECK] TT = BUILDING, Direction = ALL -> walk CMID = 0, drive CMID = -1"); print_line("");
    
//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::BARRIER),Direction(Direction::ALL));
//     print_line("[Pass: CHECK] TT = BARRIER, Direction = ALL -> all CMID = -1"); print_line("");


//     print_line("<<<<Test all TT with Direction NONE>>>>\n");
//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::NONE),Direction(Direction::NONE));
//     print_line("[Pass: CHECK] TT = NONE, Direction = NONE -> all CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::NONE));
//     print_line("[Pass: CHECK] TT = ROAD, Direction = NONE -> all CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::NONE));
//     print_line("[Pass: CHECK] TT = WALKWAY, Direction = NONE -> all CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::CROSSWALK),Direction(Direction::NONE));
//     print_line("[Pass: CHECK] TT = CROSSWALK, Direction = NONE -> all CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::PARKING),Direction(Direction::NONE));
//     print_line("[Pass: CHECK] TT = PARKING, Direction = NONE -> all CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::BUILDING),Direction(Direction::NONE));
//     print_line("[Pass: CHECK] TT = BUILDING, Direction = NONE -> all CMID = -1"); print_line("");
    
//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::BARRIER),Direction(Direction::NONE));
//     print_line("[Pass: CHECK] TT = BARRIER, Direction = NONE -> all CMID = -1"); print_line("");


//     print_line("<<<<Test TT WALKWAY with all solo Direction (E,NE,N,NW,W,SW,S,SE)>>>>\n");
//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::E));
//     print_line("[Pass: CHECK] TerrainType::WALKWAY, Direction::E -> walk 10 Direction::E groups CMID = 0,10,..,90, drive CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::NE));
//     print_line("[Pass: CHECK] TerrainType::WALKWAY, Direction::NE -> walk 10 Direction::NE groups CMID = 0,1,..9,19,29,..99, drive CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::N));
//     print_line("[Pass: CHECK] TerrainType::WALKWAY, Direction::N -> walk 10 Direction::N groups CMID = 0:9, drive CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::NW));
//     print_line("[Pass: CHECK] TerrainType::WALKWAY, Direction::NW -> walk 10 Direction::NW groups CMID = 0,1,..,9,10,20,..,90 drive CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::W));
//     print_line("[Pass: CHECK] TerrainType::WALKWAY, Direction::W -> walk 10 Direction::W groups CMID = 0,10,..,90, drive CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::SW));
//     print_line("[Pass: CHECK] TerrainType::WALKWAY, Direction::SW -> walk 10 Direction::SW groups CMID = 0,1,..9,19,29,..99, drive CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::S));
//     print_line("[Pass: CHECK] TerrainType::WALKWAY, Direction::S -> walk 10 Direction::S groups CMID = 0:9, drive CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::WALKWAY),Direction(Direction::SE));
//     print_line("[Pass: CHECK] TerrainType::WALKWAY, Direction::SE -> walk 10 Direction::SE groups CMID = 0,1,..,9,10,20,..,90, drive CMID = -1"); print_line("");


//     print_line("<<<<Test TT ROAD with all solo Direction (E,NE,N,NW,W,SW,S,SE)>>>>\n");
//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::E));
//     print_line("[Pass: CHECK] TerrainType::ROAD, Direction::E -> drive 10 Direction::E groups CMID = 0,10,..,90, walk CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::NE));
//     print_line("[Pass: CHECK] TerrainType::ROAD, Direction::NE -> drive 10 Direction::NE groups CMID = 0,1,..9,19,29,..99, walk CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::N));
//     print_line("[Pass: CHECK] TerrainType::ROAD, Direction::N -> drive 10 Direction::N groups CMID = 0:9, walk CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::NW));
//     print_line("[Pass: CHECK] TerrainType::ROAD, Direction::NW -> drive 10 Direction::NW groups CMID = 0,1,..,9,10,20,..,90 walk CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::W));
//     print_line("[Pass: CHECK] TerrainType::ROAD, Direction::W -> drive 10 Direction::W groups CMID = 0,10,..,90, walk CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::SW));
//     print_line("[Pass: CHECK] TerrainType::ROAD, Direction::SW -> drive 10 Direction::SW groups CMID = 0,1,..9,19,29,..99, walk CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::S));
//     print_line("[Pass: CHECK] TerrainType::ROAD, Direction::S -> drive 10 Direction::S groups CMID = 0:9, walk CMID = -1"); print_line("");

//     MyConnectivityMatrix::one_tt_one_dir(10,10,TerrainType(TerrainType::ROAD),Direction(Direction::SE));
//     print_line("[Pass: CHECK] TerrainType::ROAD, Direction::SE -> drive 10 Direction::SE groups CMID = 0,1,..,9,10,20,..,90, walk CMID = -1"); print_line("");


//     print_line("<<<<Test TT Parking and Barriers with Direction All>>>>\n");
//     MyConnectivityMatrix::list_tt_list_dir(5,5,{TT::PARKING, TT::PARKING, TT::BARRIER},{Direction::ALL});
//     print_line("[Pass: CHECK] {TT::PARKING, TT::PARKING, TT::BARRIER}, Direction::ALL -> Thin Barrier example, so expect only CMID = 0 and diagonal rows of CMID = -1, same for walk and drive"); print_line("");
    
//     MyConnectivityMatrix::list_tt_list_dir(9,9,{TT::PARKING, TT::PARKING, TT::BARRIER},{Direction::ALL});
//     print_line("[Pass: CHECK] {TT::PARKING, TT::PARKING, TT::BARRIER}, Direction::ALL -> 3 solid vertical barriers. 3 groups present."); print_line("");
    

//     print_line("<<<<Custom>>>>\n");
//     MyConnectivityMatrix::w_connection(Dir(Dir::ALL));
//     print_line("[Pass: CHECK] w_connection(Dir(Dir::ALL)) -> all one group in shape of w."); print_line("");
    
//     MyConnectivityMatrix::bottom_leak(Dir(Dir::ALL));
//     print_line("[Pass: CHECK] bottom_leak(Dir(Dir::ALL)) -> all one group. with a barrier at col idx = 2"); print_line("");

//     print_line("<<<<Time trials>>>>\n");
//     MyConnectivityMatrix::one_tt_one_dir(4096,4096,TT(TT::PARKING),Dir(Dir::ALL),false);
//     print_line("[Pass: CHECK] I want the time to be less than 2s"); print_line("");
    
//     print_line("==================================\n");
// }

// void Tester::cmid_tests() const {
//     print_line("==================================");
//     print_line("@Test: CMID");
//     int passed = 0, total = 0; bool pass;

//     total++; pass = true;
//     {
//         CMID default_id;
//         CMID custom_id(5);
//         CMID barrier_id(CMID::BARRIER);
//         pass = (default_id.val == CMID::INVALID &&
//                 custom_id.val == 5 &&
//                 barrier_id.val == CMID::BARRIER &&
//                 CMID::INVALID == -2 &&
//                 CMID::BARRIER == -1);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Construction and constant values", pass));

//     total++; pass = true;
//     {
//         CMID invalid_id;
//         CMID barrier_id(CMID::BARRIER);
//         CMID valid_id(0);
//         CMID valid_id2(10);
//         pass = (invalid_id.is_invalid() && !invalid_id.is_valid() &&
//                 !barrier_id.is_invalid() && barrier_id.is_valid() &&
//                 valid_id.is_valid() && !valid_id.is_invalid() &&
//                 valid_id2.is_valid() && !valid_id2.is_invalid());
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] is_valid() and is_invalid() checks", pass));

//     total++; pass = true;
//     {
//         CMID barrier_id(CMID::BARRIER);
//         CMID not_barrier(0);
//         CMID invalid_id;
//         pass = (barrier_id.is_barrier() &&
//                 !not_barrier.is_barrier() &&
//                 !invalid_id.is_barrier());
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] is_barrier() check", pass));

//     total++; pass = true;
//     {
//         CMID id(5);
//         id.invalidate();
//         bool first_check = (id.val == CMID::INVALID && id.is_invalid());
        
//         id = CMID(10);
//         id.barrier();
//         bool second_check = (id.val == CMID::BARRIER && id.is_barrier());
        
//         pass = (first_check && second_check);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] invalidate() and barrier() methods", pass));

//     total++; pass = true;
//     {
//         CMID id(5);
//         CMID& result = ++id;
//         pass = (id.val == 6 && result.val == 6 && &result == &id);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Prefix increment operator (++id)", pass));

//     total++; pass = true;
//     {
//         CMID id1(5);
//         CMID id2(5);
//         CMID id3(10);
//         CMID barrier1(CMID::BARRIER);
//         CMID barrier2(CMID::BARRIER);
//         pass = (id1 == id2 &&
//                 !(id1 == id3) &&
//                 barrier1 == barrier2 &&
//                 !(id1 == barrier1));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Equality operator (==)", pass));

//     total++; pass = true;
//     {
//         CMID zero_id(0);
//         CMID negative_id(-3);
//         CMID large_id(1000000);
//         pass = (zero_id.is_valid() &&
//                 negative_id.is_invalid() &&
//                 large_id.is_valid());
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Boundary values (0, negative, large positive)", pass));

//     total++; pass = true;
//     {
//         CMID from_barrier(CMID::BARRIER);
//         ++from_barrier;
//         CMID from_zero(0);
//         ++from_zero;
//         CMID from_negative(-5);
//         ++from_negative;
//         pass = (from_barrier.val == 0 &&
//                 from_zero.val == 1 &&
//                 from_negative.val == -4);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Increment from barrier, zero, and negative", pass));

//     print_line(vformat("@Results: %d/%d", passed, total));
//     print_line("==================================\n");
// }

// void Tester::world_tests() const {
//     print_line("==================================");
//     print_line("@Test: World");
//     int passed = 0, total = 0; bool pass;

//     total++; pass = true;
//     {
//         World world;
//         pass = (world.is_invalid() && !world.is_valid());
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Default constructor creates invalid world", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         Ref<Image> img_tm = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         Ref<Image> img_speed = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         Ref<Image> img_dir = Image::create(5, 5, false, Image::FORMAT_RGB8);
        
//         World world(img_tt, img_tm, img_speed, img_dir, 6, 5);
//         pass = (world.is_valid() && !world.is_invalid());
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Parameterized constructor creates valid world (Debug:5)", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         img_tt->set_pixel(1, 1, Color(1.0/255.0, 0.0, 0.0));
//         Ref<Image> img_tm = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_speed = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_dir = Image::create(3, 3, false, Image::FORMAT_RGB8);
        
//         World world(img_tt, img_tm, img_speed, img_dir, 6, 5);
//         TerrainType tt = world.get_tt(Cell(1, 1));
//         pass = (tt == TerrainType(1));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_tt() returns correct TerrainType", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_tm = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         img_tm->set_pixel(2, 2, Color(2.0/255.0, 0.0, 0.0));
//         Ref<Image> img_speed = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_dir = Image::create(3, 3, false, Image::FORMAT_RGB8);
        
//         World world(img_tt, img_tm, img_speed, img_dir, 6, 5);
//         TerrainMod tm = world.get_tm(Cell(2, 2));
//         pass = (tm == TerrainMod(2));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_tm() returns correct TerrainMod", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(4, 4, false, Image::FORMAT_RGB8);
//         Ref<Image> img_tm = Image::create(4, 4, false, Image::FORMAT_RGB8);
//         Ref<Image> img_speed = Image::create(4, 4, false, Image::FORMAT_RGB8);
//         img_speed->set_pixel(1, 1, Color(50.0/255.0, 0.0, 0.0));
//         Ref<Image> img_dir = Image::create(4, 4, false, Image::FORMAT_RGB8);
        
//         World world(img_tt, img_tm, img_speed, img_dir, 10, 8);
//         Speed speed = world.get_speed(Cell(1, 1));
//         pass = (speed == Speed(50, 10, 8));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_speed() returns Speed with world parameters", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_tm = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_speed = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_dir = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         img_dir->set_pixel(2, 1, Color(8.0/255.0, 0.0, 0.0));
        
//         World world(img_tt, img_tm, img_speed, img_dir, 6, 5);
//         Direction dir = world.get_dir(Cell(2, 1));
//         pass = (dir == Direction(8));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_dir() returns correct Direction", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(4, 4, false, Image::FORMAT_RGB8);
//         img_tt->set_pixel(0, 0, Color(1.0/255.0, 0.0, 0.0));
//         img_tt->set_pixel(1, 1, Color(2.0/255.0, 0.0, 0.0));
//         img_tt->set_pixel(2, 2, Color(3.0/255.0, 0.0, 0.0));
//         Ref<Image> img_tm = Image::create(4, 4, false, Image::FORMAT_RGB8);
//         Ref<Image> img_speed = Image::create(4, 4, false, Image::FORMAT_RGB8);
//         Ref<Image> img_dir = Image::create(4, 4, false, Image::FORMAT_RGB8);
        
//         World world(img_tt, img_tm, img_speed, img_dir, 6, 5);
//         pass = (world.get_tt(Cell(0, 0)) == TerrainType(1) &&
//                 world.get_tt(Cell(1, 1)) == TerrainType(2) &&
//                 world.get_tt(Cell(2, 2)) == TerrainType(3));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Multiple cells return different values", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         img_tt->set_pixel(1, 1, Color(5.0/255.0, 0.0, 0.0));
//         Ref<Image> img_tm = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_speed = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         Ref<Image> img_dir = Image::create(3, 3, false, Image::FORMAT_RGB8);
        
//         const World world(img_tt, img_tm, img_speed, img_dir, 6, 5);
//         pass = (world.is_valid() && 
//                 world.get_tt(Cell(1, 1)) == TerrainType(5));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Const World allows const method calls", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         img_tt->set_pixel(0, 0, Color(1.0/255.0, 0.0, 0.0));
//         img_tt->set_pixel(4, 4, Color(2.0/255.0, 0.0, 0.0));
//         Ref<Image> img_tm = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         img_tm->set_pixel(0, 4, Color(3.0/255.0, 0.0, 0.0));
//         Ref<Image> img_speed = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         img_speed->set_pixel(4, 0, Color(4.0/255.0, 0.0, 0.0));
//         Ref<Image> img_dir = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         img_dir->set_pixel(2, 2, Color(5.0/255.0, 0.0, 0.0));
        
//         World world(img_tt, img_tm, img_speed, img_dir, 6, 5);
//         pass = (world.get_tt(Cell(0, 0)) == TerrainType(1) &&
//                 world.get_tt(Cell(4, 4)) == TerrainType(2) &&
//                 world.get_tm(Cell(0, 4)) == TerrainMod(3) &&
//                 world.get_speed(Cell(4, 0)) == Speed(4, 6, 5) &&
//                 world.get_dir(Cell(2, 2)) == Direction(5));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] All matrices accessible at edge cells", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img_tt = Image::create(2, 2, false, Image::FORMAT_RGB8);
//         Ref<Image> img_tm = Image::create(2, 2, false, Image::FORMAT_RGB8);
//         Ref<Image> img_speed = Image::create(2, 2, false, Image::FORMAT_RGB8);
//         img_speed->set_pixel(1, 1, Color(25.0/255.0, 0.0, 0.0));
//         Ref<Image> img_dir = Image::create(2, 2, false, Image::FORMAT_RGB8);
        
//         World world(img_tt, img_tm, img_speed, img_dir, 12, 10);
//         Speed speed = world.get_speed(Cell(1, 1));
//         // Verify the Speed was constructed with the correct parameters
//         pass = (speed == Speed(25, 12, 10));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Speed constructed with world's sec_per_step and feet_per_cell", pass));

//     print_line(vformat("@Results: %d/%d", passed, total));
//     print_line("==================================\n");
// }

// void Tester::image_matrix_tests() const {
//     print_line("==================================");
//     print_line("@Test: ImageMatrix");
//     int passed = 0, total = 0; bool pass;

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(10, 8, false, Image::FORMAT_RGB8);
//         ImageMatrix<TerrainType> matrix(img);
//         pass = (matrix.cols == 10 && matrix.rows == 8);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Image dimensions (cols/rows)", pass));

//     total++; pass = true;
//     {
//         ImageMatrix<TerrainType> matrix;
//         pass = (matrix.cols == 0 && matrix.rows == 0);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Default constructor initializes to 0x0", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         img->set_pixel(2, 3, Color(0.5, 0.0, 0.0)); // r = 0.5
//         ImageMatrix<TerrainType> matrix(img);
//         uint8_t val = matrix.get_r8(Cell(2, 3));
//         pass = (val >= 127 && val <= 128); // 0.5 * 255 ≈ 127-128
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_r8() extracts red channel", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         img->set_pixel(1, 1, Color(3/255.0, 0.0, 0.0));
//         ImageMatrix<TerrainType> matrix(img);
//         TerrainType tt = matrix.get_tt(Cell(1, 1));
//         pass = (tt == TerrainType(3));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_tt() returns TerrainType", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(4, 4, false, Image::FORMAT_RGB8);
//         img->set_pixel(2, 2, Color(2/255.0, 0.0, 0.0));
//         ImageMatrix<TerrainMod> matrix(img);
//         TerrainMod tm = matrix.get_tm(Cell(2, 2));
//         pass = (tm == TerrainMod(2));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_tm() returns TerrainMod", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         img->set_pixel(3, 3, Color(50.0/255.0, 0.0, 0.0));
//         ImageMatrix<Speed> matrix(img);
//         Speed speed = matrix.get_speed(Cell(3, 3), 6, 5);
//         pass = (speed == Speed(50, 6, 5));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_speed() returns Speed with parameters", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(6, 6, false, Image::FORMAT_RGB8);
//         img->set_pixel(4, 4, Color(8.0/255.0, 0.0, 0.0));
//         ImageMatrix<Direction> matrix(img);
//         Direction dir = matrix.get_dir(Cell(4, 4));
//         pass = (dir == Direction(8));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] get_dir() returns Direction", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(7, 7, false, Image::FORMAT_RGB8);
//         img->set_pixel(0, 0, Color(1.0/255.0, 0.0, 0.0));    // Top-left
//         img->set_pixel(6, 0, Color(2.0/255.0, 0.0, 0.0));    // Top-right
//         img->set_pixel(0, 6, Color(3.0/255.0, 0.0, 0.0));    // Bottom-left
//         img->set_pixel(6, 6, Color(4.0/255.0, 0.0, 0.0));    // Bottom-right
//         ImageMatrix<TerrainType> matrix(img);
//         pass = (matrix.get_tt(Cell(0, 0)) == TerrainType(1) &&
//                 matrix.get_tt(Cell(6, 0)) == TerrainType(2) &&
//                 matrix.get_tt(Cell(0, 6)) == TerrainType(3) &&
//                 matrix.get_tt(Cell(6, 6)) == TerrainType(4));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Corner cell access", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(3, 3, false, Image::FORMAT_RGB8);
//         img->set_pixel(1, 1, Color(5/255.0, 0.0, 0.0));
//         const ImageMatrix<TerrainType> matrix(img);
//         pass = (matrix.get_r8(Cell(1, 1)) == 5);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Const ImageMatrix access", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(2, 2, false, Image::FORMAT_RGB8);
//         img->set_pixel(1, 1, Color(1.0/255.0, 0.0, 0.0));
//         ImageMatrix<TerrainType> matrix(img);
//         uint8_t val1 = matrix.get_r8(Cell(1, 1));
//         uint8_t val2 = matrix.get_r8(Cell(1, 1));
//         TerrainType tt = matrix.get_tt(Cell(1, 1));
//         pass = (val1 == 1 && val2 == 1 && tt == TerrainType(1));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Multiple reads return consistent values", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(5, 5, false, Image::FORMAT_RGB8);
//         img->set_pixel(0, 0, Color(1.0/255.0, 0.0, 0.0));
//         img->set_pixel(1, 1, Color(2.0/255.0, 0.0, 0.0));
//         img->set_pixel(2, 2, Color(3.0/255.0, 0.0, 0.0));
//         ImageMatrix<TerrainType> matrix(img);
//         pass = (matrix.get_tt(Cell(0, 0)) == TerrainType(1) &&
//                 matrix.get_tt(Cell(1, 1)) == TerrainType(2) &&
//                 matrix.get_tt(Cell(2, 2)) == TerrainType(3));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Different cells have different values", pass));

//     total++; pass = true;
//     {
//         Ref<Image> img = Image::create(100, 200, false, Image::FORMAT_RGB8);
//         img->set_pixel(99, 199, Color(0.0/255.0, 0.0, 0.0));
//         ImageMatrix<TerrainMod> matrix(img);
//         pass = (matrix.cols == 100 && 
//                 matrix.rows == 200 && 
//                 matrix.get_tm(Cell(99, 199)) == TerrainMod(0));
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Large image (100x200) handling", pass));

//     //This passed if it fails to comile. (PASSED.)
//     // {
//     //     ImageMatrix<Speed> matrix();
//     //     matrix.get_dir();
//     // }

//     print_line(vformat("@Results: %d/%d", passed, total));
//     print_line("==================================\n");
// }

// void Tester::matrix_tests() const {
//     print_line("==================================");
//     print_line("@Test: Matrix");
//     int passed = 0, total = 0; bool pass;

//     total++; pass = true;
//     {
//         Matrix<int> matrix(5, 5);
//         matrix.at(Cell(2, 3)) = 42;
//         pass = (matrix.at(Cell(2, 3)) == 42);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Set and get value at Cell(2,3)", pass));

//     total++; pass = true;
//     {
//         Matrix<int> matrix(3, 3);
//         pass = (matrix.at(Cell(1, 1)) == 0); // int() == 0
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Default initialization to T()", pass));

//     total++; pass = true;
//     {
//         Matrix<int> matrix(4, 4);
//         matrix.at(Cell(2, 2)) = 100;
//         const Matrix<int>& const_ref = matrix;
//         pass = (const_ref.at(Cell(2, 2)) == 100);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Const reference access", pass));

//     total++; pass = true;
//     {
//         Matrix<float> matrix(2, 2);
//         matrix.at(Cell(0, 0)) = 3.14f;
//         matrix.at(Cell(1, 1)) = 2.71f;
//         pass = (matrix.at(Cell(0, 0)) > 3.13f && matrix.at(Cell(0, 0)) < 3.15f &&
//                 matrix.at(Cell(1, 1)) > 2.70f && matrix.at(Cell(1, 1)) < 2.72f);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Matrix<float> type", pass));

//     total++; pass = true;
//     {
//         Matrix<int> matrix(5, 5);
//         matrix.at(Cell(0, 0)) = 1;    // Top-left
//         matrix.at(Cell(4, 0)) = 2;    // Top-right
//         matrix.at(Cell(0, 4)) = 3;    // Bottom-left
//         matrix.at(Cell(4, 4)) = 4;    // Bottom-right
//         pass = (matrix.at(Cell(0, 0)) == 1 &&
//                 matrix.at(Cell(4, 0)) == 2 &&
//                 matrix.at(Cell(0, 4)) == 3 &&
//                 matrix.at(Cell(4, 4)) == 4);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Edge cell access", pass));

//     total++; pass = true;
//     {
//         Matrix<int> matrix(3, 3);
//         matrix.at(Cell(1, 1)) = 10;
//         int& ref = matrix.at(Cell(1, 1));
//         ref = 20;
//         pass = (matrix.at(Cell(1, 1)) == 20);
//     }
//     if (pass) passed++;
//     print_line(vformat("[Pass: %s] Reference modification", pass));

//     print_line(vformat("@Results: %d/%d", passed, total));
//     print_line("==================================\n");
// }

// void Tester::terrain_mod_tests() const {
//     print_line("@Test --- TerrainMod");

//     // Construction - default
//     print_line(vformat("[Pass: %s] TerrainMod() creates NONE", TerrainMod().val == TerrainMod::NONE));

//     // Construction - from uint8_t  values)
//     print_line(vformat("[Pass: %s] TerrainMod(JUNCTION_STOP)", TerrainMod(TerrainMod::JUNCTION_STOP).val == TerrainMod::JUNCTION_STOP));
//     print_line(vformat("[Pass: %s] TerrainMod(JUNCTION1)", TerrainMod(TerrainMod::JUNCTION1).val == TerrainMod::JUNCTION1));
//     print_line(vformat("[Pass: %s] TerrainMod(JUNCTION2)", TerrainMod(TerrainMod::JUNCTION2).val == TerrainMod::JUNCTION2));
//     print_line(vformat("[Pass: %s] TerrainMod(JUNCTION3)", TerrainMod(TerrainMod::JUNCTION3).val == TerrainMod::JUNCTION3));
//     print_line(vformat("[Pass: %s] TerrainMod(LANE_DIVIDER)", TerrainMod(TerrainMod::LANE_DIVIDER).val == TerrainMod::LANE_DIVIDER));

//     // Construction - invalid values (should throw)
//     bool threw_max = false;
//     try {
//         TerrainMod invalid(TerrainMod::MAX);
//     } catch (const std::invalid_argument& e) {
//         threw_max = true;
//     }
//     print_line(vformat("[Pass: %s] TerrainMod(MAX) throws exception", threw_max));

//     bool threw_over = false;
//     try {
//         TerrainMod invalid(100);
//     } catch (const std::invalid_argument& e) {
//         threw_over = true;
//     }
//     print_line(vformat("[Pass: %s] TerrainMod(100) throws exception", threw_over));

//     print_line("Check If I need these tests ...");
//     // Construction - from Image
//     // Ref<Image> test_image = Image::create(10, 10, false, Image::FORMAT_RGB8);
//     // test_image->fill(Color(0, 0, 0));  // NONE = 0
//     // test_image->set_pixel(2, 2, Color(1.0f/255.0f, 0, 0));  // JUNCTION_STOP = 1
//     // test_image->set_pixel(4, 4, Color(5.0f/255.0f, 0, 0));  // LANE_DIVIDER = 5

//     // TerrainMod from_img_none(Cell(0,0), test_image);
//     // print_line(vformat("[Pass: %s] TerrainMod from image (0,0) creates NONE", from_img_none.val == TerrainMod::NONE));

//     // TerrainMod from_img_stop(Cell(2,2), test_image);
//     // print_line(vformat("[Pass: %s] TerrainMod from image (2,2) creates JUNCTION_STOP", from_img_stop.val == TerrainMod::JUNCTION_STOP));

//     // TerrainMod from_img_divider(Cell(4,4), test_image);
//     // print_line(vformat("[Pass: %s] TerrainMod from image (4,4) creates LANE_DIVIDER", from_img_divider.val == TerrainMod::LANE_DIVIDER));
// }

// void Tester::terrain_type_tests() const {
//     print_line("@Test --- TerrainType");

//     // Construction - default
//     print_line(vformat("[Pass: %s] TerrainType() creates NONE", TerrainType().val == TerrainType::NONE));

//     // Construction - from uint8_t (valid values)
//     print_line(vformat("[Pass: %s] TerrainType(ROAD) creates ROAD", TerrainType(TerrainType::ROAD).val == TerrainType::ROAD));
//     print_line(vformat("[Pass: %s] TerrainType(WALKWAY) creates WALKWAY", TerrainType(TerrainType::WALKWAY).val == TerrainType::WALKWAY));
//     print_line(vformat("[Pass: %s] TerrainType(CROSSWALK) creates CROSSWALK", TerrainType(TerrainType::CROSSWALK).val == TerrainType::CROSSWALK));
//     print_line(vformat("[Pass: %s] TerrainType(PARKING) creates PARKING", TerrainType(TerrainType::PARKING).val == TerrainType::PARKING));
//     print_line(vformat("[Pass: %s] TerrainType(BUILDING) creates BUILDING", TerrainType(TerrainType::BUILDING).val == TerrainType::BUILDING));
//     print_line(vformat("[Pass: %s] TerrainType(BARRIER) creates BARRIER", TerrainType(TerrainType::BARRIER).val == TerrainType::BARRIER));

//     // Construction - invalid values (should throw)
//     bool threw_negative = false;
//     try {
//         TerrainType invalid(-1);
//     } catch (const std::invalid_argument& e) {
//         threw_negative = true;
//     }
//     print_line(vformat("[Pass: %s] TerrainType(-1) throws exception", threw_negative));

//     bool threw_max = false;
//     try {
//         TerrainType invalid(TerrainType::MAX);
//     } catch (const std::invalid_argument& e) {
//         threw_max = true;
//     }
//     print_line(vformat("[Pass: %s] TerrainType(MAX) throws exception", threw_max));

//     bool threw_over_max = false;
//     try {
//         TerrainType invalid(100);
//     } catch (const std::invalid_argument& e) {
//         threw_over_max = true;
//     }
//     print_line(vformat("[Pass: %s] TerrainType(100) throws exception", threw_over_max));

//     print_line("Check If I need these tests ...");
//     // Construction - from Image
//     // Ref<Image> test_image = Image::create(10, 10, false, Image::FORMAT_RGB8);
//     // test_image->fill(Color(0, 0, 0));  // Fill with black (NONE = 0)

//     // // Set pixels
//     // test_image->set_pixel(5, 5, Color(1.0f/255.0f, 0, 0));  // Red = 1
//     // test_image->set_pixel(3, 3, Color(2.0f/255.0f, 0, 0));  // Red = 2

//     // // Debug: Check what values we actually get back
//     // Color debug_pixel_road = test_image->get_pixel(5, 5);
//     // Color debug_pixel_walk = test_image->get_pixel(3, 3);
//     // print_line(vformat("Debug: Pixel (5,5) r = %f, r*255 = %d", debug_pixel_road.r, (int)(debug_pixel_road.r * 255)));
//     // print_line(vformat("Debug: Pixel (3,3) r = %f, r*255 = %d", debug_pixel_walk.r, (int)(debug_pixel_walk.r * 255)));

//     // TerrainType from_img_none(Cell(0,0), test_image);
//     // print_line(vformat("[Pass: %s] TerrainType from image pixel (0,0) creates NONE (val=%d)", 
//     //     from_img_none.val == TerrainType::NONE, from_img_none.val));

//     // TerrainType from_img_road(Cell(5,5), test_image);
//     // print_line(vformat("[Pass: %s] TerrainType from image pixel (5,5) creates ROAD (val=%d, expected=1)", 
//     //     from_img_road.val == TerrainType::ROAD, from_img_road.val));

//     // TerrainType from_img_walkway(Cell(3,3), test_image);
//     // print_line(vformat("[Pass: %s] TerrainType from image pixel (3,3) creates WALKWAY (val=%d, expected=2)", 
//     //     from_img_walkway.val == TerrainType::WALKWAY, from_img_walkway.val));
// }

// void Tester::speed_tests() const {
//     print_line("@Test --- Speed");
//     // Construction
//     print_line(vformat("[Pass: %s] Speed() creates zero speed", Speed().val == 0.0f));
//     print_line(vformat("[Pass: %s] Speed(5.0f) creates speed with val=5.0", Speed(5.0f).val == 5.0f));

//     // MPH constructor - 60 mph, 1 sec/step, 10 ft/cell should give 8.8 cells/step
//     Speed test_mph(60, 1, 10);
//     print_line(vformat("[Pass: %s] Speed(60 mph, 1 sec/step, 10 ft/cell) ≈ 8.8 cells/step", 
//         abs(test_mph.val - 8.8f) < 0.01f));

//     // Constexpr
//     constexpr Speed compile_time(5.0f);
//     print_line(vformat("[Pass: %s] constexpr Speed works at compile time", compile_time.val == 5.0f));
// }

// void Tester::direction_tests() const {
//     print_line("@Test --- Direction: Construction");
//     print_line(vformat("[Pass: %s] Direction() creates NONE", Direction().val == Direction::NONE));
//     print_line(vformat("[Pass: %s] Direction(Direction::E) creates E", Direction(Direction::E).val == Direction::E));
//     print_line(vformat("[Pass: %s] Direction(0b00000001) creates E", Direction(0b00000001).val == Direction::E));
//     print_line(vformat("[Pass: %s] Direction(Direction::ALL) has all bits", Direction(Direction::ALL).val == Direction::ALL));

//     print_line("");
//     print_line("@Test --- Direction: is_none() and count()");
//     print_line(vformat("[Pass: %s] Direction() is_none() returns true", Direction().is_none()));
//     print_line(vformat("[Pass: %s] Direction(Direction::E) is_none() returns false", !Direction(Direction::E).is_none()));
//     print_line(vformat("[Pass: %s] Direction(Direction::NONE).count() == 0", Direction(Direction::NONE).count() == 0));
//     print_line(vformat("[Pass: %s] Direction(Direction::E).count() == 1", Direction(Direction::E).count() == 1));
//     print_line(vformat("[Pass: %s] Direction(Direction::NE).count() == 1", Direction(Direction::NE).count() == 1));
//     print_line(vformat("[Pass: %s] Direction(Direction::E | Direction::N).count() == 2", 
//         Direction(Direction::E | Direction::N).count() == 2));
//     print_line(vformat("[Pass: %s] Direction(Direction::ALL).count() == 8", Direction(Direction::ALL).count() == 8));
//     print_line(vformat("[Pass: %s] Direction(0b10110101).count() == 5", Direction(0b10110101).count() == 5));

//     print_line("");
//     print_line("@Test --- Direction: operator[]");
//     Direction test_dir(Direction::E | Direction::N | Direction::W);
//     print_line("Variable: test_dir = Direction(E | N | W) = 0b00010101");
//     print_line(vformat("[Pass: %s] test_dir[0] (E bit) is true", test_dir[0]));
//     print_line(vformat("[Pass: %s] test_dir[1] (NE bit) is false", !test_dir[1]));
//     print_line(vformat("[Pass: %s] test_dir[2] (N bit) is true", test_dir[2]));
//     print_line(vformat("[Pass: %s] test_dir[4] (W bit) is true", test_dir[4]));
//     print_line(vformat("[Pass: %s] test_dir[7] (SE bit) is false", !test_dir[7]));
//     print_line(vformat("[Pass: %s] test_dir[-1] (out of bounds) is false", !test_dir[-1]));
//     print_line(vformat("[Pass: %s] test_dir[8] (out of bounds) is false", !test_dir[8]));

//     print_line("");
//     print_line("@Test --- Direction: Equality operators");
//     print_line(vformat("[Pass: %s] Direction() == Direction()", Direction() == Direction()));
//     print_line(vformat("[Pass: %s] Direction(Direction::E) == Direction(Direction::E)", 
//         Direction(Direction::E) == Direction(Direction::E)));
//     print_line(vformat("[Pass: %s] Direction(Direction::E) != Direction(Direction::N)", 
//         Direction(Direction::E) != Direction(Direction::N)));
//     print_line(vformat("[Pass: %s] Direction(Direction::E | Direction::N) == Direction(0b00000101)", 
//         Direction(Direction::E | Direction::N) == Direction(0b00000101)));

//     print_line("");
//     print_line("@Test --- Direction: Bitwise OR");
//     Direction or_test = Direction(Direction::E);
//     print_line("Variable: or_test = Direction(E)");
//     print_line(vformat("[Pass: %s] or_test |= Direction(N) results in E|N", 
//         (or_test |= Direction(Direction::N)) == Direction(Direction::E | Direction::N)));
//     print_line(vformat("[Pass: %s] or_test now has count() == 2", or_test.count() == 2));
//     print_line(vformat("[Pass: %s] Direction(E) | Direction(N) == Direction(E|N)", 
//         (Direction(Direction::E) | Direction(Direction::N)) == Direction(Direction::E | Direction::N)));
//     print_line(vformat("[Pass: %s] Direction(E|W) | Direction(N|S) == Direction(E|W|N|S)", 
//         (Direction(Direction::E | Direction::W) | Direction(Direction::N | Direction::S)) == 
//         Direction(Direction::E | Direction::W | Direction::N | Direction::S)));

//     print_line("");
//     print_line("@Test --- Direction: Bitwise AND");
//     Direction and_test = Direction(Direction::E | Direction::N | Direction::W);
//     print_line("Variable: and_test = Direction(E|N|W)");
//     print_line(vformat("[Pass: %s] and_test &= Direction(E|N) results in E|N", 
//         (and_test &= Direction(Direction::E | Direction::N)) == Direction(Direction::E | Direction::N)));
//     print_line(vformat("[Pass: %s] Direction(E|N) & Direction(N|W) == Direction(N)", 
//         (Direction(Direction::E | Direction::N) & Direction(Direction::N | Direction::W)) == Direction(Direction::N)));
//     print_line(vformat("[Pass: %s] Direction(E) & Direction(N) == Direction(NONE)", 
//         (Direction(Direction::E) & Direction(Direction::N)) == Direction(Direction::NONE)));
//     print_line(vformat("[Pass: %s] Direction(ALL) & Direction(E) == Direction(E)", 
//         (Direction(Direction::ALL) & Direction(Direction::E)) == Direction(Direction::E)));

//     print_line("");
//     print_line("@Test --- Direction: Addition");
//     Direction add_test = Direction(Direction::E);
//     print_line("Variable: add_test = Direction(E) = 0b00000001");
//     print_line(vformat("[Pass: %s] add_test += Direction(N) results in 0b00000101", 
//         (add_test += Direction(Direction::N)).val == 0b00000101));
//     print_line(vformat("[Pass: %s] Direction(0b00000001) + Direction(0b00000010) == Direction(0b00000011)", 
//         (Direction(0b00000001) + Direction(0b00000010)) == Direction(0b00000011)));

//     print_line("");
//     print_line("@Test --- Direction: Subtraction");
//     Direction sub_test = Direction(0b00000101);
//     print_line("Variable: sub_test = Direction(0b00000101)");
//     print_line(vformat("[Pass: %s] sub_test -= Direction(0b00000001) results in 0b00000100", 
//         (sub_test -= Direction(0b00000001)).val == 0b00000100));
//     print_line(vformat("[Pass: %s] Direction(0b00000101) - Direction(0b00000001) == Direction(0b00000100)", 
//         (Direction(0b00000101) - Direction(0b00000001)) == Direction(0b00000100)));

//     print_line("");
//     print_line("@Test --- Direction: Matching");
//     Direction match_test1(Direction::E | Direction::N);
//     Direction match_test2(Direction::N | Direction::W);
//     print_line("Variable: match_test1 = Direction(E|N)");
//     print_line("Variable: match_test2 = Direction(N|W)");
//     print_line(vformat("[Pass: %s] match_test1.no_matches(Direction(W|S)) is true", 
//         match_test1.no_matches(Direction(Direction::W | Direction::S))));
//     print_line(vformat("[Pass: %s] match_test1.no_matches(match_test2) is false (N matches)", 
//         !match_test1.no_matches(match_test2)));
//     print_line(vformat("[Pass: %s] match_test1.atleast1_matches(match_test2) is true (N matches)", 
//         match_test1.atleast1_matches(match_test2)));
//     print_line(vformat("[Pass: %s] Direction(E).no_matches(Direction(W)) is true", 
//         Direction(Direction::E).no_matches(Direction(Direction::W))));
//     print_line(vformat("[Pass: %s] Direction().no_matches(Direction()) is true (both NONE)", 
//         Direction().no_matches(Direction())));

//     print_line("");
//     print_line("@Test --- SoloDirection: Valid Construction");
//     print_line(vformat("[Pass: %s] SoloDirection() creates NONE", SoloDirection().val == Direction::NONE));
//     print_line(vformat("[Pass: %s] SoloDirection(Direction::E) is valid", SoloDirection(Direction::E).val == Direction::E));
//     print_line(vformat("[Pass: %s] SoloDirection(Direction::N) is valid", SoloDirection(Direction::N).val == Direction::N));
//     print_line(vformat("[Pass: %s] SoloDirection(Direction::NONE) is valid", SoloDirection(Direction::NONE).val == Direction::NONE));

//     Direction solo_source(Direction::W);
//     print_line("Variable: solo_source = Direction(W)");
//     print_line(vformat("[Pass: %s] SoloDirection(solo_source) is valid", 
//         SoloDirection(solo_source).val == Direction::W));

//     print_line("");
//     print_line("@Test --- SoloDirection: Invalid Construction (should throw)");
//     bool threw_multi = false;
//     try {
//         SoloDirection invalid(Direction::E | Direction::N);
//     } catch (const std::invalid_argument& e) {
//         threw_multi = true;
//     }
//     print_line(vformat("[Pass: %s] SoloDirection(E|N) throws exception", threw_multi));

//     bool threw_all = false;
//     try {
//         SoloDirection invalid(Direction::ALL);
//     } catch (const std::invalid_argument& e) {
//         threw_all = true;
//     }
//     print_line(vformat("[Pass: %s] SoloDirection(ALL) throws exception", threw_all));

//     bool threw_from_dir = false;
//     try {
//         Direction multi(Direction::E | Direction::W);
//         SoloDirection invalid(multi);
//     } catch (const std::invalid_argument& e) {
//         threw_from_dir = true;
//     }
//     print_line(vformat("[Pass: %s] SoloDirection(Direction with multiple bits) throws exception", threw_from_dir));

//     print_line("");
//     print_line("@Test --- SoloDirection: to_vec2i()");
//     print_line(vformat("[Pass: %s] SoloDirection(E).to_vec2i() == Vec2i(1,0)", 
//         SoloDirection(Direction::E).to_vec2i() == Vec2i(1,0)));
//     print_line(vformat("[Pass: %s] SoloDirection(NE).to_vec2i() == Vec2i(1,1)", 
//         SoloDirection(Direction::NE).to_vec2i() == Vec2i(1,-1)));
//     print_line(vformat("[Pass: %s] SoloDirection(N).to_vec2i() == Vec2i(0,1)", 
//         SoloDirection(Direction::N).to_vec2i() == Vec2i(0,-1)));
//     print_line(vformat("[Pass: %s] SoloDirection(NW).to_vec2i() == Vec2i(-1,1)", 
//         SoloDirection(Direction::NW).to_vec2i() == Vec2i(-1,-1)));
//     print_line(vformat("[Pass: %s] SoloDirection(W).to_vec2i() == Vec2i(-1,0)", 
//         SoloDirection(Direction::W).to_vec2i() == Vec2i(-1,0)));
//     print_line(vformat("[Pass: %s] SoloDirection(SW).to_vec2i() == Vec2i(-1,-1)", 
//         SoloDirection(Direction::SW).to_vec2i() == Vec2i(-1,1)));
//     print_line(vformat("[Pass: %s] SoloDirection(S).to_vec2i() == Vec2i(0,-1)", 
//         SoloDirection(Direction::S).to_vec2i() == Vec2i(0,1)));
//     print_line(vformat("[Pass: %s] SoloDirection(SE).to_vec2i() == Vec2i(1,-1)", 
//         SoloDirection(Direction::SE).to_vec2i() == Vec2i(1,1)));
//     print_line(vformat("[Pass: %s] SoloDirection(NONE).to_vec2i() == Vec2i(0,0)", 
//         SoloDirection(Direction::NONE).to_vec2i() == Vec2i(0,0)));

//     print_line("");
//     print_line("@Test --- SoloDirection: Inheritance (is-a Direction)");
//     SoloDirection solo_inherit(Direction::E);
//     Direction base_from_solo = solo_inherit;  // Implicit upcast
//     print_line(vformat("[Pass: %s] SoloDirection can be assigned to Direction", 
//         base_from_solo.val == Direction::E));
//     print_line(vformat("[Pass: %s] SoloDirection inherits count() method", 
//         solo_inherit.count() == 1));
//     print_line(vformat("[Pass: %s] SoloDirection inherits is_none() method", 
//         !solo_inherit.is_none()));
//     print_line(vformat("[Pass: %s] SoloDirection(NONE).is_none() is true", 
//         SoloDirection().is_none()));

//     print_line("");
//     print_line("@Test --- Edge Cases");
//     print_line(vformat("[Pass: %s] Direction with all bits set has count == 8", 
//         Direction(0b11111111).count() == 8));
//     print_line(vformat("[Pass: %s] Direction(0).is_none() is true", 
//         Direction(0).is_none()));
//     print_line(vformat("[Pass: %s] Multiple OR operations: (E|N|W|S).count() == 4", 
//         (Direction(Direction::E) | Direction(Direction::N) | Direction(Direction::W) | Direction(Direction::S)).count() == 4));
// }

// void Tester::cell_vec_tests() const {
//     print_line("@Test --- Vec2i (Basic Math Vector)");
//     // Construction
//     print_line(vformat("[Pass: %s] Vec2i() == Vec2i(0,0)", Vec2i() == Vec2i(0,0)));
//     print_line(vformat("[Pass: %s] Vec2i(5,10).x == 5 and .y == 10", Vec2i(5,10).x == 5 && Vec2i(5,10).y == 10));

//     // Equality
//     print_line(vformat("[Pass: %s] Vec2i(1,1) == Vec2i(1,1)", Vec2i(1,1) == Vec2i(1,1)));
//     print_line(vformat("[Pass: %s] Vec2i(1,1) != Vec2i(2,3)", Vec2i(1,1) != Vec2i(2,3)));

//     // Addition
//     Vec2i vec_add = Vec2i(1,1);
//     print_line("Variable: vec_add = Vec2i(1,1)");
//     print_line(vformat("[Pass: %s] vec_add += Vec2i(2,3) == Vec2i(3,4)", (vec_add += Vec2i(2,3)) == Vec2i(3,4)));
//     print_line(vformat("[Pass: %s] vec_add is now Vec2i(3,4)", vec_add == Vec2i(3,4)));
//     print_line(vformat("[Pass: %s] Vec2i(1,1) + Vec2i(2,3) == Vec2i(3,4)", (Vec2i(1,1) + Vec2i(2,3)) == Vec2i(3,4)));

//     // Subtraction
//     Vec2i vec_sub = Vec2i(5,8);
//     print_line("Variable: vec_sub = Vec2i(5,8)");
//     print_line(vformat("[Pass: %s] vec_sub -= Vec2i(2,3) == Vec2i(3,5)", (vec_sub -= Vec2i(2,3)) == Vec2i(3,5)));
//     print_line(vformat("[Pass: %s] Vec2i(5,8) - Vec2i(2,3) == Vec2i(3,5)", (Vec2i(5,8) - Vec2i(2,3)) == Vec2i(3,5)));

//     print_line("");
//     print_line("@Test --- Cell (Grid Coordinates)");
//     // Construction
//     print_line(vformat("[Pass: %s] Cell() creates invalid cell", Cell().is_invalid()));
//     print_line(vformat("[Pass: %s] Cell(1,1) is valid", Cell(1,1).is_valid()));
//     print_line(vformat("[Pass: %s] Cell(2,3) is valid", Cell(2,3).is_valid()));
//     print_line(vformat("[Pass: %s] Cell(-1,-1) is invalid", Cell(-1,-1).is_invalid()));
//     print_line(vformat("[Pass: %s] Cell(Vec2i(5,10)) creates cell at (5,10)", Cell(Vec2i(5,10)).x == 5 && Cell(Vec2i(5,10)).y== 10));
//     print_line(vformat("[Pass: %s] Cell(Vec2i(-4,-5)) is invalid", Cell(Vec2i(-4,-5)).is_invalid()));

//     // Accessors
//     Cell test_cell = Cell(7,9);
//     print_line("Variable: test_cell = Cell(7,9)");
//     print_line(vformat("[Pass: %s] test_cell.x == 7", test_cell.x == 7));
//     print_line(vformat("[Pass: %s] test_cell.y == 9", test_cell.y == 9));

//     // Validation
//     print_line(vformat("[Pass: %s] Cell(0,0) is valid", Cell(0,0).is_valid()));
//     print_line(vformat("[Pass: %s] Cell(-1,5) is invalid", Cell(-1,5).is_invalid()));
//     print_line(vformat("[Pass: %s] Cell(5,-1) is invalid", Cell(5,-1).is_invalid()));
//     Cell invalidate_test = Cell(5,5);
//     invalidate_test.invalidate();
//     print_line(vformat("[Pass: %s] Cell(5,5).invalidate() makes it invalid", invalidate_test.is_invalid()));

//     // Bounds checking
//     print_line(vformat("[Pass: %s] Cell(1,1) is in bounds [0-2, 0-3]", Cell(1,1).in_bounds(0,0,2,3)));
//     print_line(vformat("[Pass: %s] Cell(2,3) is NOT in bounds [0-1, 0-2]", !Cell(2,3).in_bounds(0,0,1,2)));
//     print_line(vformat("[Pass: %s] Cell() is NOT in bounds [0-1, 0-2]", !Cell().in_bounds(0,0,1,2)));
//     print_line(vformat("[Pass: %s] Cell(0,0) is in bounds [0-0, 0-0]", Cell(0,0).in_bounds(0,0,0,0)));
//     print_line(vformat("[Pass: %s] Cell(5,5) is NOT in bounds [0-4, 0-4]", !Cell(5,5).in_bounds(0,0,4,4)));

//     // Equality
//     print_line(vformat("[Pass: %s] Cell() == Cell()", Cell() == Cell()));
//     print_line(vformat("[Pass: %s] Cell(1,1) == Cell(1,1)", Cell(1,1) == Cell(1,1)));
//     print_line(vformat("[Pass: %s] Cell(1,1) != Cell(2,3)", Cell(1,1) != Cell(2,3)));
//     print_line(vformat("[Pass: %s] Cell(0,0) != Cell()", Cell(0,0) != Cell()));

//     // Resolution/scaling constructor
//     print_line(vformat("[Pass: %s] Cell(Cell(1,1), 2) == Cell(0,0)", Cell(Cell(1,1), 2) == Cell(0,0)));
//     print_line(vformat("[Pass: %s] Cell(Cell(2,3), 2) == Cell(1,1)", Cell(Cell(2,3), 2) == Cell(1,1)));
//     print_line(vformat("[Pass: %s] Cell(Cell(2,0), 2) == Cell(1,0)", Cell(Cell(2,0), 2) == Cell(1,0)));
//     print_line(vformat("[Pass: %s] Cell(Cell(5,7), 2) == Cell(2,3)", Cell(Cell(5,7), 2) == Cell(2,3)));

//     // Addition with Cell
//     Cell add_cell = Cell(1,1);
//     print_line("");
//     print_line("Variable: add_cell = Cell(1,1)");
//     print_line(vformat("[Pass: %s] add_cell += Cell(2,3) == Cell(3,4)", (add_cell += Cell(2,3)) == Cell(3,4)));
//     print_line(vformat("[Pass: %s] add_cell is now Cell(3,4)", add_cell == Cell(3,4)));
//     print_line(vformat("[Pass: %s] add_cell += Cell(-1,-1) == Cell(2,3)", (add_cell += Cell(-1,-1)) == Cell(2,3)));

//     // Addition with Vec2i
//     Cell add_vec_cell = Cell(1,1);
//     print_line("");
//     print_line("Variable: add_vec_cell = Cell(1,1)");
//     print_line(vformat("[Pass: %s] add_vec_cell += Vec2i(2,3) == Cell(3,4)", (add_vec_cell += Vec2i(2,3)) == Cell(3,4)));
//     print_line(vformat("[Pass: %s] add_vec_cell += Vec2i(-4,-2) == Cell(-1,2)", (add_vec_cell += Vec2i(-4,-2)) == Cell(-1,2)));

//     // Operator+ combinations
//     print_line("");
//     print_line(vformat("[Pass: %s] Cell(1,1) + Cell(2,3) == Cell(3,4)", (Cell(1,1) + Cell(2,3)) == Cell(3,4)));
//     print_line(vformat("[Pass: %s] Cell(1,1) + Vec2i(2,3) == Cell(3,4)", (Cell(1,1) + Vec2i(2,3)) == Cell(3,4)));
//     print_line(vformat("[Pass: %s] Vec2i(1,1) + Cell(2,3) == Cell(3,4)", (Vec2i(1,1) + Cell(2,3)) == Cell(3,4)));
//     print_line(vformat("[Pass: %s] Cell(-3,-2) + Cell(4,3) == Cell(1,1)", (Cell(-3,-2) + Cell(4,3)) == Cell(1,1)));

//     // Complex expression
//     Cell complex_add = Cell(1,1);
//     print_line("");
//     print_line("Variable: complex_add = Cell(1,1)");
//     print_line(vformat("[Pass: %s] complex_add += Cell(-3,-2) + Cell(4,3) == Cell(2,2)", 
//         (complex_add += Cell(-3,-2) + Cell(4,3)) == Cell(2,2)));

//     print_line("");
//     print_line("@Test --- Cell ↔ Vec2i Conversions");
//     // cast conversion
//     Cell conv_cell = Cell(5,10);
//     print_line("Variable: conv_cell = Cell(5,10)");
//     Vec2i cast_vec = static_cast<Vec2i>(conv_cell);  // Uses operator Vec2i()
//     print_line(vformat("[Pass: %s] Vec2i cast_vec = conv_cell; creates Vec2i(5,10)", 
//         cast_vec == Vec2i(5,10)));

//     // Explicit conversion
//     Vec2i explicit_vec = conv_cell.to_vec2i();
//     print_line(vformat("[Pass: %s] conv_cell.to_vec2i() == Vec2i(5,10)", 
//         explicit_vec == Vec2i(5,10)));

//     // Mixed operations
//     print_line(vformat("[Pass: %s] Vec2i(1,1) + Cell(2,3) results in Cell type", 
//         (Vec2i(1,1) + Cell(2,3)) == Cell(3,4)));

//     print_line("");
//     print_line("@Test --- Edge Cases");
//     print_line(vformat("[Pass: %s] Cell(0,-1) is invalid", Cell(0,-1).is_invalid()));
//     print_line(vformat("[Pass: %s] Cell(-1,0) is invalid", Cell(-1,0).is_invalid()));
//     print_line(vformat("[Pass: %s] Cell(0,0) is valid", Cell(0,0).is_valid()));
//     print_line(vformat("[Pass: %s] Very large coordinates Cell(10000,10000) is valid", 
//         Cell(10000,10000).is_valid()));

//     Cell chain_test = Cell(1,1);
//     print_line("Variable: chain_test = Cell(1,1)");
//     print_line(vformat("[Pass: %s] Chained operations: (chain_test += Vec2i(2,2)) += Cell(3,3) == Cell(6,6)", 
//         ((chain_test += Vec2i(2,2)) += Cell(3,3)) == Cell(6,6)));

//     print_line("@Test --- Cell.to_idx");
//     print_line(vformat("[Pass: %s] Cell(1,2) cols = 3 -> idx == 7", Cell(1,2).to_idx(3) == 7));
// }



