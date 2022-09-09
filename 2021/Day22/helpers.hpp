#include <bits/stdc++.h>
#include "region.hpp"


std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x << "," << p.y << "," << p.z << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Region& r)
{
    os << r.p1 << " - " << r.p2;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Instruction &i)
{
    os << (i.on ? "on" : "off") << ": " << i.region;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> v)
{
    for (const auto& i : v) os << i << std::endl;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T> s)
{
    for (const auto& i : s) os << i << std::endl;
    return os;
}
