#include <bits/stdc++.h>



typedef std::pair<int,int> Point;
typedef std::pair<int,int> Direction;
typedef std::pair<Point,Direction> State;

std::vector<std::string> map;
int N,M;
State initial_state;
Point target;
std::vector<std::vector<int>> route_counts;

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p) { os << "(" << p.first << "," << p.second << ")"; return os; }
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) { for (int i = 0; i < v.size(); i++) os << (i==0?"":" ") << v.at(i); return os;}
template <>
std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v) { for (const auto& s : v) os << s << std::endl; return os;}

template <typename T, typename U>
std::pair<T,U> operator+(const std::pair<T,U>& p,const std::pair<T,U>& q) { return std::make_pair(p.first+q.first, p.second+q.second); }


Direction rotate(const Direction& d, bool inv=false) { return std::make_pair((inv?1:-1) * d.second, (inv?-1:1) * d.first); }


char& at(const Point& p) { return map.at(p.first).at(p.second); }


void record_route(const std::vector<State>& route)
{
    std::set<Point> locs;
    for (const auto& s : route) locs.insert(s.first);
    for (const auto& p : locs) route_counts.at(p.first).at(p.second)++;
}

void search()
{
    std::priority_queue<
        std::pair<unsigned long long int, std::pair<State, std::vector<State>>>,
        std::vector<std::pair<unsigned long long int, std::pair<State, std::vector<State>>>>,
        std::greater<std::pair<unsigned long long int, std::pair<State, std::vector<State>>>>> queue;
    std::map<State, unsigned long long int> explored_states;

    const auto queue_state = [&queue, &explored_states](const unsigned long long int cost, const State s, std::vector<State> route)
    {
        if (explored_states.find(s) != explored_states.end()) if (explored_states.at(s) < cost) return;
        explored_states[s] = cost;
        route.push_back(s);
        queue.push(std::make_pair(cost, std::make_pair(s, route)));
    };

    queue_state(0, initial_state, std::vector<State>());

    unsigned long long int best_route = ULLONG_MAX;
    while (!queue.empty())
    {
        auto s = queue.top(); queue.pop();
        const auto cost = s.first;
        const auto state = s.second.first;
        const auto loc = state.first;
        const auto dir = state.second;
        const auto route = s.second.second;

        if (cost > best_route) return;
        if (at(loc) == 'E')
        {
            best_route = cost;
            record_route(route);
        }

        if (at(loc+dir) != '#')
            queue_state(cost+1, std::make_pair(loc+dir, dir), route);
        queue_state(cost+1000, std::make_pair(loc, rotate(dir, true)), route);
        queue_state(cost+1000, std::make_pair(loc, rotate(dir, false)), route);
    }
}

void solve()
{
    search();
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < M; j++)
    //     {
    //         std::cout << route_counts[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    int c = 0;
    for (const auto& r : route_counts) for (const auto i : r) c += i>0;
    std::cout << c << std::endl;
}


void preprocess()
{
    N = map.size(); M = map.front().size();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            switch (map.at(i).at(j))
            {
            case 'E':
                target = std::make_pair(i,j);
                break;
            case 'S':
                initial_state = std::make_pair(std::make_pair(i,j), std::make_pair(0,1));
                break;
            default:
                continue;
            }
        }
    }
    route_counts = std::vector<std::vector<int>>(N, std::vector<int>(M,0));
}

int main()
{
    std::string l;
    while (std::getline(std::cin, l))
    {
        if (l.empty()) break;
        map.push_back(l);
    }

    preprocess();
    solve();
}

