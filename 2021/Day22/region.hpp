#ifndef REGION_HPP
#define REGION_HPP

#include <bits/stdc++.h>


struct Point
{
    int x=0, y=0, z=0;
    
    Point(int x, int y, int z) : x(x), y(y), z(z) {}
};


struct Region
{
    Point p1, p2;
    Region *sub1, *sub2;
    bool on;
    unsigned long long int volume;

    Region(const Point a, const Point b): p1(p1), p2(p2), on(false)
    {
        p1 = Point(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
        p2 = Point(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
        volume = static_cast<unsigned long long int>(p2.x-p1.x) * 
            static_cast<unsigned long long int>(p2.y-p1.y) * 
            static_cast<unsigned long long int>(p2.z-p1.z);
        sub1 = nullptr; sub2 = nullptr;
    }
    ~Region()
    {
        if (sub1 != nullptr)
        {
            delete sub1;
            sub1 = nullptr;
        }
        if (sub2 != nullptr)
        {
            delete sub2;
            sub2 = nullptr;
        }
    }

    void set(bool f)
    {
        on = f;
        if (sub1 != nullptr) sub1->set(f);
        if (sub2 != nullptr) sub2->set(f);
    }

    unsigned long long int count()
    {
        if (sub1 == nullptr || sub2 == nullptr)
            return (on ? volume : 0);
        return sub1->count() + sub2->count();
    }

    int num_regions()
    {
        if (sub1 == nullptr || sub2 == nullptr)
            return 1;
        return sub1->num_regions() + sub2->num_regions();
    }

    void split_x(int x)
    {
        if (sub1 == nullptr || sub2 == nullptr)
        {
            if (p1.x < x && p2.x > x)
            {
                sub1 = new Region(
                    Point(p1.x, p1.y, p1.z), Point(x, p2.y, p2.z));
                sub2 = new Region(
                    Point(x, p1.y, p1.z), Point(p2.x, p2.y, p2.z));
                sub1->on = on; sub2->on = on;
            }
        }
        else
        {
            sub1->split_x(x);
            sub2->split_x(x);
        }
    }

    void split_y(int y)
    {
        if (sub1 == nullptr || sub2 == nullptr)
        {
            if (p1.y < y && p2.y > y)
            {
                sub1 = new Region(
                    Point(p1.x, p1.y, p1.z), Point(p2.x, y, p2.z));
                sub2 = new Region(
                    Point(p1.x, y, p1.z), Point(p2.x, p2.y, p2.z));
                sub1->on = on; sub2->on = on;
            }
        }
        else
        {
            sub1->split_y(y);
            sub2->split_y(y);
        }
    }

    void split_z(int z)
    {
        if (sub1 == nullptr || sub2 == nullptr)
        {
            if (p1.z < z && p2.z > z)
            {
                sub1 = new Region(
                    Point(p1.x, p1.y, p1.z), Point(p2.x, p2.y, z));
                sub2 = new Region(
                    Point(p1.x, p1.y, z), Point(p2.x, p2.y, p2.z));
                sub1->on = on; sub2->on = on;
            }
        }
        else
        {
            sub1->split_z(z);
            sub2->split_z(z);
        }
    }

    bool contains(const Region& r) const
    {
        return p1.x <= r.p1.x && r.p2.x <= p2.x &&
            p1.y <= r.p1.y && r.p2.y <= p2.y &&
            p1.z <= r.p1.z && r.p2.z <= p2.z;
    }

    void set_if(const Region& r, bool f)
    {
        if (sub1 == nullptr || sub2 == nullptr)
        {
            if (r.contains(*this))
            {
                on = f;
            }
        }
        else
        {
            sub1->set_if(r, f);
            sub2->set_if(r, f);
        }
    }

    bool is_terminal() const
    {
        return sub1 == nullptr || sub2 == nullptr;
    }

    void trim()
    {
        if (is_terminal()) return;
        sub1->trim();
        sub2->trim();
        if (sub1->is_terminal() && sub2->is_terminal())
        {
            if (sub1->on == sub2->on)
            {
                on = sub1->on;
                delete sub1; sub1 = nullptr;
                delete sub2; sub2 = nullptr;
            }
        }
    }
};

struct Instruction
{
    bool on;
    Region region;

    Instruction(const bool f, const Region r) : on(f), region(r) {}
};

#endif // REGION_HPP