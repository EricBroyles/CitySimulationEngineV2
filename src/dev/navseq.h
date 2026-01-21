#pragma once

/*
Navseq: Navigation Sequence
PREFERENCES: higher scores indicate a greater perference. Multiply the preference * time to get the time to compare when picking navseq
*/

class Navseq {
private:
    Navseq::OPTIONS _opt;
public:
    enum class OPTIONS {NONE, WALK, DRIVE};
    static constexpr float PREFERENCES[3] = {0, 1, .9};
    Navseq(): _opt(Navseq::OPTIONS::NONE) {}
    Navseq(Navseq::OPTIONS opt): _opt(opt) {}
    Navseq(Human& human) {
        if !(human.valid) {_opt(Navseq::OPTIONS::None); return;}

        // FINISH.
    }
    bool is_valid() const {return option != Navseq::OPTIONS::NONE}
    void invalid() {_opt(Navseq::OPTIONS::NONE);}
    Navseq::OPTIONS option() {return _opt;}
};
