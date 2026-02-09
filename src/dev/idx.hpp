#pragma once

template <typename Tag>
struct IDX {
    static constexpr int INVALID = -1;
    int val;
    constexpr IDX() : val(INVALID) {}
    constexpr explicit IDX(int v) : val(v) {}
    constexpr bool is_valid() const   { return val > INVALID; }
    constexpr bool is_invalid() const { return !is_valid(); }

    // comparisons only within same IDX space
    friend constexpr bool operator==(IDX a, IDX b) { return a.val == b.val; }
    friend constexpr bool operator!=(IDX a, IDX b) { return a.val != b.val; }
    friend constexpr bool operator<(IDX a, IDX b)  { return a.val < b.val; }
    friend constexpr bool operator>(IDX a, IDX b)  { return a.val > b.val; }
    friend constexpr bool operator<=(IDX a, IDX b) { return a.val <= b.val; }
    friend constexpr bool operator>=(IDX a, IDX b) { return a.val >= b.val; }

    IDX& operator++() { ++val; return *this; } // prefix ++
    IDX operator++(int) { IDX old = *this; ++val; return old; } // postfix ++
    constexpr explicit operator int() const { return val; }
};

struct AgentTag {};
struct HumanTag {};
struct PersonalVehicleTag {};

using AgentIDX = IDX<AgentTag>;
using HumanIDX = IDX<HumanTag>;
using PersonalVehicleIDX = IDX<PersonalVehicleTag>;
using PVIDX = PersonalVehicleIDX;
