/*
must use
Ref<InputPackage> input = memnew(InputPackage);

*/

#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/image.hpp>
#include "dev/image_matrix.hpp"
#include "dev/terrain_type.hpp"
#include "dev/terrain_mod.hpp"
#include "dev/direction.hpp"
#include "dev/speed.hpp"

using namespace godot;

class InputPackage: public RefCounted {
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
    int personal_vehicle_ownership_rate;

protected:
    static void _bind_methods(); 

public:
    InputPackage(): cols(0), rows(0), sec_per_step(1), feet_per_cell(10), num_steps(0), num_humans(0), personal_vehicle_ownership_rate(0)  {}

    void set_image_matrices(Ref<Image> p_tt, Ref<Image> p_tm, Ref<Image> p_dir, Ref<Image> p_mph) {
        tt = ImageMatrix<TT>(p_tt);
        tm = ImageMatrix<TM>(p_tm);
        dir = ImageMatrix<Dir>(p_dir);
        mph = ImageMatrix<MPH>(p_mph);
        cols = tt.cols;
        rows = tt.rows;
    }

    void set_sec_per_step(int val)                    { sec_per_step = val; }
    void set_feet_per_cell(int val)                   { feet_per_cell = val; }
    void set_num_steps(int val)                       { num_steps = val; }
    void set_num_humans(int val)                      { num_humans = val; }
    void set_personal_vehicle_ownership_rate(int val) { personal_vehicle_ownership_rate = val; }

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
    int get_personal_vehicle_ownership_rate()   const { return personal_vehicle_ownership_rate; }
};


