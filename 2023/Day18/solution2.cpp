#include <bits/stdc++.h>

struct Instruction
{
    char direction;
    long long count;
    std::string colour;
};

std::ostream& operator<<(std::ostream& os, const Instruction& instruction)
{
    os << instruction.direction << " " << instruction.count;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for (const T& t: v) os << t << std::endl;
    return os; 
}

struct Polygon
{
    std::vector<std::pair<long long, long long>> vertices;

    std::pair<long long, long long> operator[](size_t i)
    {
        return vertices.at((i+vertices.size()) % vertices.size());
    }

    Polygon() : vertices() {}

    void add_vertex(long long x, long long y)
    {
        vertices.push_back(std::make_pair(x,y));
    }
};

std::vector<Instruction> instructions;
Polygon polygon;
long long x, y;
long long n;

long long area(Polygon& polygon)
{
    long long area = 0;
    for (int i = 0; i < polygon.vertices.size(); i++)
    {
        area += polygon[i].first * (polygon[i+1].second - polygon[i-1].second);
    }
    area /= 2;
    return area;
}

void process_instruction(const Instruction& instruction)
{
    for (int i = 0; i < instruction.count; i++)
    {
        switch(instruction.direction)
        {
            case 'U': y--; break;
            case 'D': y++; break;
            case 'L': x--; break;
            case 'R': x++; break;
            default: std::cout << "Invalid direction " << instruction.direction << std::endl;
        }
    }
    n += instruction.count;
    polygon.add_vertex(x,y);
}

void solve()
{
    std::cout << instructions << std::endl;
    polygon = Polygon();
    x = 0; y = 0; n = 0;
    polygon.add_vertex(x,y);
    for (const Instruction& instruction : instructions) process_instruction(instruction);

    std::cout << area(polygon) + 1 + n/2 << std::endl;
}

int main()
{
    char dir, c; int n; std::string colour;
    while (std::cin >> dir >> n >> c >> c >> colour)
    {
        colour.pop_back();
        switch (colour.back())
        {
            case '0': dir = 'R'; break;
            case '1': dir = 'D'; break;
            case '2': dir = 'L'; break;
            case '3': dir = 'U'; break;
            default: std::cout << "Cannot convert '" << colour.back() << "' to direction." << std::endl;
        }
        colour.pop_back();
        n = std::stol(colour.c_str(), nullptr, 16);
        instructions.push_back({dir, n, colour});
    }
    solve();
}
