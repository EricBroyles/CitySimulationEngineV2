#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/image.hpp>
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
    InputPackage(): cols(0), rows(0), sec_per_step(1), feet_per_cell(10), num_steps(0), num_humans(0), pv_ownership_rate(0)  {}

    void set_image_matrices(const Ref<Image> p_tt, const Ref<Image> p_tm, const Ref<Image> p_dir, const Ref<Image> p_mph) {
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


