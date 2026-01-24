// #pragma once

// /*
// Navseq: Navigation Sequence
// PREFERENCES: higher scores indicate a greater perference. Multiply the preference * time to get the time to compare when picking navseq
// */

// class Navseq {
// public:
//     enum class OPTIONS {NONE, WALK, DRIVE};
//     static constexpr float PREFERENCES[3] = {0.0f, 1.0f, 0.9f};
// private:
//     OPTIONS _opt;
// public:
//     Navseq(): _opt(OPTIONS::NONE) {}
//     Navseq(OPTIONS opt): _opt(opt) {}
//     Navseq(Human& human) {
//         if !(human.valid) {_opt(OPTIONS::None); return;}

//         // FINISH.
//     }
//     bool is_valid() const {return option != OPTIONS::NONE}
//     void invalid() {_opt(OPTIONS::NONE);}
//     OPTIONS option() {return _opt;}
// };
