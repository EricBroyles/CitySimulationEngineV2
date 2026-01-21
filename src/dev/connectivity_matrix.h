#pragma once
#include <vector>

class CMGroup {
private:
    static const int INVALID_ID = -1;
    int _id;
public:
    explicit CMGroup(): id(INVALID_ID) {}
    explicit CMGroup(int v): id(v) {}
    bool is_valid() const {return id > INVALID_ID;}
    void invalid() {id(INVALID_ID);}
    int id() const {return _id;}
};

class ConnectivityMatrix {
private:
    bool valid;
    const std::vector<CMGroup> walk;
    const std::vector<CMGroup> drive;
    
public:

    bool is_valid() const {return valid;}
    void invalid() {valid(false);}
    
};

//invalid cmid, walk, drive cm, 