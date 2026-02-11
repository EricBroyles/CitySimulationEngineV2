#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "dev/terrain_type.hpp"
#include "dev/terrain_mod.hpp"
#include "dev/direction.hpp"
#include "dev/speed.hpp"
#include "dev/image_matrix.hpp"

using namespace godot;

class InputPackage: public RefCounted {
private:
    GDCLASS(InputPackage, RefCounted);
    ImageMatrix<TT> tt;
    ImageMatrix<TM> tm;
    ImageMatrix<Dir> dir;
    ImageMatrix<MPH> mph; 
    int cols, rows;
    int sec_per_step;
    int feet_per_cell;
    int num_steps;
    int num_humans;
    int pv_ownership_rate;
    int human_step_every_x_steps = 10;
    int pv_step_every_x_steps = 1;
    MPH avg_walk_mph = DEFAULT_AVG_WALK_MPH;
    MPH avg_drive_mph = DEFAULT_AVG_DRIVE_MPH;

protected:
    static void _bind_methods(); 

public:
    static constexpr MPH DEFAULT_AVG_WALK_MPH = MPH(3);
    static constexpr MPH DEFAULT_AVG_DRIVE_MPH = MPH(38);
    InputPackage(): cols(2), rows(2), sec_per_step(1), feet_per_cell(10), num_steps(0), num_humans(0), pv_ownership_rate(0)  {}

    void set_image_matrices(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_dir, const Ref<Image> p_mph) {
        if (p_tt.is_null() || p_tm.is_null() || p_dir.is_null() || p_mph.is_null()) {
            UtilityFunctions::push_error("One or more images are null.");
        }

        const uint32_t tt_cols  = p_tt->get_width();
        const uint32_t tt_rows  = p_tt->get_height();
        const uint32_t tm_cols  = p_tm->get_width();
        const uint32_t tm_rows  = p_tm->get_height();
        const uint32_t dir_cols = p_dir->get_width();
        const uint32_t dir_rows = p_dir->get_height();
        const uint32_t mph_cols = p_mph->get_width();
        const uint32_t mph_rows = p_mph->get_height();

        // All images must match size
        if (tt_cols != tm_cols || tt_cols != dir_cols || tt_cols != mph_cols ||
            tt_rows != tm_rows || tt_rows != dir_rows || tt_rows != mph_rows) {
            UtilityFunctions::push_error("All images must have identical dimensions.");
        }

        // Must be square
        if (tt_cols != tt_rows) {
            UtilityFunctions::push_error("Image must be square (cols == rows).");
        }

        // Minimum size
        if (tt_cols < 2) {
            UtilityFunctions::push_error("Image size must be >= 2.");
        }

        // Power of 2 check
        bool is_power_of_two = tt_cols && !(tt_cols & (tt_cols - 1));
        if (!is_power_of_two) {
            UtilityFunctions::push_error("Image size must be a power of 2.");
        }

        tt = ImageMatrix<TT>(p_tt, TT::IMAGE_FORMAT);
        tm = ImageMatrix<TM>(p_tm, TM::IMAGE_FORMAT);
        dir = ImageMatrix<Dir>(p_dir, Dir::IMAGE_FORMAT);
        mph = ImageMatrix<MPH>(p_mph, MPH::IMAGE_FORMAT);
        cols = tt.cols;
        rows = tt.rows;
    }

    void set_sec_per_step(int val) { sec_per_step = val; }
    void set_feet_per_cell(int val) { feet_per_cell = val; }
    void set_num_steps(int val) { num_steps = val; }
    void set_num_humans(int val) { num_humans = val; }
    void set_pv_ownership_rate(int val) { pv_ownership_rate = val; }
    void set_human_step_every_x_steps(int val) { human_step_every_x_steps = val; }
    void set_pv_step_every_x_steps(int val) { pv_step_every_x_steps = val; }
    void override_avg_mph(uint8_t walk_mph, uint8_t drive_mph) { avg_walk_mph = MPH(walk_mph); avg_drive_mph = MPH(drive_mph); } //I cannot have 

    const ImageMatrix<TT>&  get_tt()            const { return tt; }
    const ImageMatrix<TM>&  get_tm()            const { return tm; }
    const ImageMatrix<Dir>& get_dir()           const { return dir; }
    const ImageMatrix<MPH>& get_mph()           const { return mph; }
    int get_cols()                              const { return cols; }
    int get_rows()                              const { return rows; }
    int get_sec_per_step()                      const { return sec_per_step; }
    int get_feet_per_cell()                     const { return feet_per_cell; }
    int get_num_steps()                         const { return num_steps; }
    int get_num_humans()                        const { return num_humans; }
    int get_pv_ownership_rate()                 const { return pv_ownership_rate; }
    int get_human_step_every_x_steps()          const {return human_step_every_x_steps; }
    int get_pv_step_every_x_steps()             const {return pv_step_every_x_steps; }
    Speed get_avg_walk_speed()                  const { return Speed(avg_walk_mph, sec_per_step, feet_per_cell); }
    Speed get_avg_drive_speed()                 const { return Speed(avg_drive_mph, sec_per_step, feet_per_cell); }
};


