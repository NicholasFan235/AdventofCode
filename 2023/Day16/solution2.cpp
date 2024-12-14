#include <bits/stdc++.h>


enum Direction {
    None = 0,
    North = 0b0001,
    East = 0b0010,
    South = 0b0100,
    West = 0b1000
};

struct Beam{
    int x, y;
    Direction direction;
    int ctr = 0;

    void update()
    {
        ++ctr;
        switch (direction)
        {
            case Direction::North:
                --y;
                break;
            case Direction::East:
                ++x;
                break;
            case Direction::South:
                ++y;
                break;
            case Direction::West:
                --x;
        }
    }
};

std::vector<std::string> grid;
std::vector<std::vector<bool>> energized;
std::queue<Beam> beams;
std::vector<std::vector<Direction>> beam_paths;


bool update_beam(Beam& beam)
{
    if (beam.x < 0 || beam.y < 0 || beam.x >= grid[0].size() || beam.y >= grid.size()) return false;
    if (beam.ctr > grid.size() * grid[0].size()) return false;
    if (beam_paths[beam.y][beam.x] & beam.direction) return false;
    beam_paths[beam.y][beam.x] = static_cast<Direction>(beam_paths[beam.y][beam.x] | beam.direction);
    energized[beam.y][beam.x] = true;

    char c = grid[beam.y][beam.x];
    switch (c)
    {
        case '.':
            break;
        case '/':
            if (beam.direction == North) beam.direction = East;
            else if (beam.direction == East) beam.direction = North;
            else if (beam.direction == South) beam.direction = West;
            else if (beam.direction == West) beam.direction = South;
            break;
        case '\\':
            if (beam.direction == North) beam.direction = West;
            else if (beam.direction == South) beam.direction = East;
            else if (beam.direction == East) beam.direction = South;
            else if (beam.direction == West) beam.direction = North;
            break;
        case '|':
            if (beam.direction & (East | West))
            {
                beam.direction = North;
                beams.push(Beam{beam.x, beam.y+1, South});
            }
            break;
        case '-':
            if (beam.direction & (North | South))
            {
                beam.direction = East;
                beams.push(Beam{beam.x-1, beam.y, West});
            }
            break;
    }
    beam.update();
    return true;
}


void reset()
{
    while (!beams.empty()) beams.pop();
    energized = std::vector<std::vector<bool>>(grid.size(), std::vector<bool>(grid[0].size(), false));
    beam_paths = std::vector<std::vector<Direction>>(grid.size(), std::vector<Direction>(grid[0].size(), Direction::None));
}

unsigned long long solve_setup(int x, int y, Direction dir)
{
    reset();
    beams.push(Beam{x, y, dir});

    while (!beams.empty())
    {
        while (update_beam(beams.front()));
        beams.pop();
    }

    unsigned long long ans = 0;
    for (const auto& v : energized)
        for (const auto& b : v)
            ans += b;
    return ans;
}

void solve()
{
    unsigned long long max = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        max = std::max(max, solve_setup(0, i, East));
        max = std::max(max, solve_setup(grid[0].size()-1, i, West));
    }
    for (int i = 0; i < grid[0].size(); i++)
    {
        max = std::max(max, solve_setup(i,0,South));
        max = std::max(max, solve_setup(i,grid.size()-1,North));
    }
    std::cout << max << std::endl;
}

int main()
{
    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) continue;
        grid.push_back(s);
    }
    reset();
    solve();
}
