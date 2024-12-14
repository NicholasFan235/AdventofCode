#include <bits/stdc++.h>

typedef std::pair<int, int> Point;
typedef std::pair<int, int> Direction;
typedef std::pair<Point, Direction> State;



std::set<State> visited_states;
std::set<Point> visited_locations;
std::set<Point> obstacles;

State current_state;


int N,M;

std::pair<int,int> operator+(const std::pair<int,int>& p, const std::pair<int,int>& q)
{
    return std::make_pair(p.first+q.first, p.second+q.second);
}

inline bool in_bounds(const Point p)
{
    return p.first >= 0 && p.second >= 0 && p.first < N && p.second < M;
}

inline bool is_collision(const Point p)
{
    return obstacles.find(p) != obstacles.end();
}

inline std::pair<int,int> rotate(const Direction d)
{
    return std::make_pair(d.second, -d.first);
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

bool move()
{
    std::pair<int,int> next_position = current_state.first + current_state.second;
    if (!in_bounds(next_position)) return false;

    if (is_collision(next_position)) current_state = std::make_pair(current_state.first, rotate(current_state.second));
    else current_state = std::make_pair(next_position, current_state.second);

    bool r = visited_states.find(current_state) == visited_states.end();
    visited_states.insert(current_state);
    visited_locations.insert(current_state.first);
    return r;
}

void solve()
{
    while (move()) {}
    std::cout << visited_locations.size() << std::endl;
}


int main()
{
    int i = 0;
    std::string line;
    while (std::cin >> line)
    {
        if (line.size() <= 0) break;

        for (int j = 0; j < line.size(); j++)
        {
            if (line[j] == '.') continue;
            Point p = std::make_pair(i,j);

            if (line[j] == '#')
            {
                obstacles.insert(p);
            }
            else if (line[j] == '^')
            {
                current_state = std::make_pair(p, std::make_pair(-1,0));
            }
        }
        ++i;
        M = line.size();
    }
    N = i;
    visited_locations.insert(current_state.first);
    visited_states.insert(current_state);
    // std::cout << current_state << " " << M << " " << N << std::endl;
    solve();
}



