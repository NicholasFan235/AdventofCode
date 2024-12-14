#include <bits/stdc++.h>

struct Instruction
{
    char direction;
    int count;
    std::string colour;
};

struct Polygon
{
    std::vector<std::pair<int, int>> vertices;

    std::pair<int, int> operator[](int i)
    {
        return vertices.at((i+vertices.size()) % vertices.size());
    }

    Polygon() : vertices() {}

    void add_vertex(int x, int y)
    {
        vertices.push_back(std::make_pair(x,y));
    }
};

std::vector<Instruction> instructions;
Polygon polygon;
int x, y;
int n;

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
    polygon = Polygon();
    x = 0; y = 0; n = 0;
    polygon.add_vertex(x,y);
    for (const Instruction& instruction : instructions) process_instruction(instruction);

    std::cout << area(polygon) + 1 + n/2 << std::endl;
}

int main()
{
    char dir; int n; std::string colour;
    while (std::cin >> dir >> n >> colour)
    {
        instructions.push_back({dir, n, colour});
    }
    solve();
}
