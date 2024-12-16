#include <bits/stdc++.h>

typedef std::pair<int,int> Vector;
template <typename T, typename U>
std::pair<T,U> operator+(const std::pair<T,U>& p, const std::pair<T,U>& q) { return std::make_pair(p.first+q.first, p.second+q.second); }
template <typename T, typename U, typename V, typename W>
std::pair<T,U> operator%(const std::pair<T,U>& p, const std::pair<V,W>& q) { return std::make_pair((q.first+p.first%q.first)%q.first, (q.second+p.second%q.second)%q.second); }
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << "("<<p.first<<","<<p.second<<")";
    return os;
}

Vector bounds;
struct Robot
{
    Vector position, velocity;

    void tick()
    {
        position = (position + velocity)%bounds;
    }
};
std::vector<Robot> robots;

std::ostream& operator<<(std::ostream& os, const Robot& r)
{
    os << "Robot("<<r.position<<","<<r.velocity<<")";
    return os;
}

void draw(int i)
{
    std::vector<std::string> m = std::vector<std::string>(bounds.second, std::string(bounds.first, ' '));
    for (const auto& r : robots)
    {
        m[r.position.second][r.position.first] = '#';
    }
    std::stringstream ss;
    ss << i << '\n';
    for (const auto& l : m)
    {
        ss << l << '\n';
    }
    std::cout << ss.str() << std::endl;
}


int quadrat(const Robot& r)
{
    int a = r.position.first - bounds.first/2;
    int b = r.position.second - bounds.second/2;
    if (std::abs(a)<5 || std::abs(b)<5) return -1;
    return (a<0)*2 + (b<0);
}

void tick()
{
    for (auto& r : robots) r.tick();
}

void solve()
{
    long long n_axis = 0;
    for (int i = 0; i < 10000; i++)
    {
        n_axis = 0;
        tick();

        for (const auto& r : robots)
        {
            int q = quadrat(r);
            if (q<0) ++n_axis;
        }

        if (n_axis > 200)
        {
            std::cout << n_axis << "\t";
            draw(i+1);
        }
    }
}

int main()
{
    robots = std::vector<Robot>();

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty()) break;

        const std::regex regex("p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)");
        std::smatch m;
        if (std::regex_match(line, m, regex))
        {
            auto get = [&m](int i){ return atoi(m[i].str().c_str()); };
            robots.push_back(Robot{std::make_pair(get(1), get(2)), std::make_pair(get(3),get(4))});
        }
    }

    if (robots.size() < 100) bounds = std::make_pair(11, 7);
    else bounds = std::make_pair(101, 103);

    solve();
}

