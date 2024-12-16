#include <bits/stdc++.h>

int N,M;
std::vector<std::string> map;
std::vector<std::vector<bool>> visited_map;

std::vector<std::pair<int,int>> neighbours = {{1,0},{0,1},{-1,0},{0,-1}};

inline char at(const std::pair<int,int> p) { return map.at(p.first).at(p.second); }
inline bool visited(const std::pair<int,int> p) { return visited_map.at(p.first).at(p.second); }
inline void visit(const std::pair<int,int> p) { visited_map.at(p.first).at(p.second) = true; }
inline bool in_bounds(const std::pair<int,int> p) { return p.first>=0 && p.second>=0 && p.first<N && p.second<M; }
inline std::pair<int,int> operator+(const std::pair<int,int> p, const std::pair<int,int> q) { return std::make_pair(p.first+q.first, p.second+q.second); }
inline std::pair<int,int> transpose(const std::pair<int,int> p) { return std::make_pair(p.second, p.first); }

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
{
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        os << (it==s.begin()?"" : " ") << *it;
    }
    return os;
}

unsigned long long int calculate_cost(const std::pair<int,int> start)
{
    unsigned long long int area = 0;
    std::array<std::set<std::pair<int,int>>, 4> perimeter_locations;
    unsigned long long int perimeter = 0;

    const char source = at(start);

    std::queue<std::pair<int,int>> check_queue;
    check_queue.push(start);

    while (!check_queue.empty())
    {
        const std::pair<int,int> p = check_queue.front();
        check_queue.pop();
        
        if (!visited(p))
        {
            visit(p);
            ++area;
            for (int i = 0; i < 4; i++)
            {
                const auto& n = neighbours[i];
                
                const std::pair<int,int> q = p+n;
                if (!in_bounds(q) || (at(q)!=source)) perimeter_locations[i].insert(i%2==0?p:transpose(p));
            
                if (in_bounds(q) && (at(q)==source) && !visited(q))
                    check_queue.push(q);
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        // std::cout << perimeter_locations[i] << std::endl;
        int c = -2;
        int prev = -1;
        for (const auto& x : perimeter_locations[i])
        {
            if (prev != x.first) { prev = x.first; c = -2; }
            if (x.second != c+1) ++perimeter;
            c = x.second;
        }
    }
    // std::cout << area << "*" << perimeter << "=" << area*perimeter << std::endl;

    return area*perimeter;
}


void solve()
{
    unsigned long long int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (!visited_map[i][j]) ans += calculate_cost(std::make_pair(i,j));
        }
    }
    std::cout << ans << std::endl;
}


int main()
{
    std::string line;
    while (std::cin >> line) map.push_back(line);
    N = map.size(); M = map.front().size();
    visited_map = std::vector<std::vector<bool>>(N, std::vector<bool>(M, false));
    solve();
}

