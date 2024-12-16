#include <bits/stdc++.h>


std::vector<std::string> map;
int N,M;

bool in_bounds(int i, int j)
{
    return i>=0 && j>=0 && i<N && j<N;
}


int traverse(int i, int j)
{
    // int ans = 0;
    char height = map[i][j];
    if (height == '9') return 1;

    auto try_traverse = [height](int i, int j)
    {
        if (!in_bounds(i,j)) return 0;
        if (map[i][j] != static_cast<char>(height+1)){
            return 0;
        }
        return traverse(i,j);
    };
    
    return try_traverse(i+1,j) + try_traverse(i-1,j) + try_traverse(i,j+1) + try_traverse(i,j-1);
}


void solve()
{
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j] != '0') continue;
            int score = traverse(i,j);
            // std::cout << score << std::endl;
            ans += score;
        }
    }
    std::cout << ans << std::endl;
}


int main()
{
    std::string line;
    while (std::cin >> line)
    {
        if (line.empty()) break;
        map.push_back(line);
    }
    N = map.size();
    M = map.front().size();

    solve();
}

