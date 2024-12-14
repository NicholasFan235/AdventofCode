#include <bits/stdc++.h>

typedef std::pair<int, int> Point;
typedef std::pair<int, int> Direction;
typedef std::pair<Point, Direction> State;


std::set<Point> obstacles;
State initial_state;


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

bool forms_loop(State current_state, const std::set<Point>& obstacles)
{
    std::set<State> visited_states;
    std::set<Point> visited_locations;

    auto record_state = [&visited_states,&visited_locations](const State& s)
    {
        visited_states.insert(s);
        visited_locations.insert(s.first);
    };
    record_state(current_state);

    while (true)
    {
        std::pair<int,int> next_position = current_state.first + current_state.second;
        if (!in_bounds(next_position)) return false;

        if (is_collision(next_position)) current_state = std::make_pair(current_state.first, rotate(current_state.second));
        else current_state = std::make_pair(next_position, current_state.second);

        bool r = visited_states.find(current_state) == visited_states.end();
        record_state(current_state);
        if (!r) return true;
    }
}

void solve()
{
    long ans = 0;
    for (int i = 0; i < N; i++)
    {
        std::cout << '\r' << i << "/" << N << std::flush;
        for (int j = 0; j < M; j++)
        {
            Point o = std::make_pair(i,j);
            if (obstacles.find(o) != obstacles.end()) continue;

            obstacles.insert(o);
            ans += forms_loop(initial_state, obstacles);
            obstacles.erase(o);
        }
    }
    std::cout << std::endl << ans << std::endl;
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
                initial_state = std::make_pair(p, std::make_pair(-1,0));
            }
        }
        ++i;
        M = line.size();
    }
    N = i;
    // std::cout << current_state << " " << M << " " << N << std::endl;
    solve();
}



