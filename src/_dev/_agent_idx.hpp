// #pragma once

// struct AgentIdx {
//     static constexpr int INVALID = -1;
//     int val;
//     constexpr AgentID(): val(INVALID) {}
//     constexpr AgentID(int v): val(v) {}
//     bool is_valid() const { return val > INVALID; }
//     bool is_not_valid() const  { return !is_valid(); }
//     constexpr bool operator==(AgentID other) const { return val == other.val; }
//     constexpr bool operator!=(AgentID other) const { return val != other.val; }
//     constexpr bool operator<=(AgentID other) const { return val <= other.val; }
//     constexpr bool operator>=(AgentID other) const { return val >= other.val; }
//     constexpr bool operator<(AgentID other)  const { return val < other.val; }
//     constexpr bool operator>(AgentID other)  const { return val > other.val; }
//     AgentID& operator++() { ++val; return *this; } //++AgentID 
//     AgentID operator++(int) { AgentID old = *this; ++val; return old; } //AgentID++ 
//     constexpr explicit operator int() const { return val; }
// };

// struct HumanIdx : public AgentIdx {
//     using AgentIdx::AgentIdx; 
// };

// struct PersonalVehicleIdx : public AgentIdx {
//     using AgentIdx::AgentIdx;
// };

// using PVIdx = PersonalVehicleIdx;
