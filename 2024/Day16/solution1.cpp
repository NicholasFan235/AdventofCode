#include <bits/stdc++.h>



typedef std::pair<int,int> Point;
typedef std::pair<int,int> Direction;
typedef std::pair<Point,Direction> State;

std::vector<std::string> map;
int N,M;
State initial_state;
Point target;

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

unsigned long long int search()
{
    std::priority_queue<
        std::pair<unsigned long long int, State>,
        std::vector<std::pair<unsigned long long int, State>>,
        std::greater<std::pair<unsigned long long int, State>>> queue;
    std::set<State> explored_states;
    queue.push(std::make_pair(0ull, initial_state));

    while (!queue.empty())
    {
        auto s = queue.top(); queue.pop();
        const auto cost = s.first;
        const auto state = s.second;
        const auto loc = state.first;
        const auto dir = state.second;

        if (at(loc) == 'E') return cost;

        const auto queue_state = [&queue, &explored_states](const unsigned long long int cost, const State s)
        {
            if (explored_states.find(s) != explored_states.end()) return;
            explored_states.insert(s);
            queue.push(std::make_pair(cost, s));
        };

        if (at(loc+dir) != '#')
            queue_state(cost+1, std::make_pair(loc+dir, dir));
        queue_state(cost+1000, std::make_pair(loc, rotate(dir, true)));
        queue_state(cost+1000, std::make_pair(loc, rotate(dir, false)));
    }
    throw std::runtime_error("No valid path.");
}

void solve()
{
    unsigned long long int ans = search();
    std::cout << ans << std::endl;
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

