#include <bits/stdc++.h>

int N,M;
std::vector<std::string> map;
std::vector<std::vector<bool>> visited_map;

std::vector<std::pair<int,int>> neighbours = {{1,0},{-1,0},{0,1},{0,-1}};

inline char at(const std::pair<int,int> p) { return map.at(p.first).at(p.second); }
inline bool visited(const std::pair<int,int> p) { return visited_map.at(p.first).at(p.second); }
inline void visit(const std::pair<int,int> p) { visited_map.at(p.first).at(p.second) = true; }
inline bool in_bounds(const std::pair<int,int> p) { return p.first>=0 && p.second>=0 && p.first<N && p.second<M; }
inline std::pair<int,int> operator+(const std::pair<int,int> p, const std::pair<int,int> q) { return std::make_pair(p.first+q.first, p.second+q.second); }


unsigned long long int calculate_cost(const std::pair<int,int> start)
{
    unsigned long long int area = 0;
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
            for (const auto& n : neighbours)
            {
                const std::pair<int,int> q = p+n;
                if (!in_bounds(q) || (at(q)!=source)) ++perimeter;
            
                if (in_bounds(q) && (at(q)==source) && !visited(q))
                    check_queue.push(q);
            }
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

