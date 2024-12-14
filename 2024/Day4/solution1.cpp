#include <bits/stdc++.h>


std::vector<std::string> puzzle;
const std::string target = "XMAS";


bool search(int x, int y, int dx, int dy, int i)
{
    if (i >= target.size()) return true;

    if (x<0 || y<0 || y>=puzzle.size() || x>=puzzle[y].size()) return false;
    if (puzzle[y][x] != target[i]) return false;
    return search(x+dx, y+dy, dx, dy, i+1);
}

const std::vector<std::pair<int, int>> directions = {
    {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}
};

void solve()
{
    unsigned long long ans = 0;
    for (int i = 0; i < puzzle.size(); i++)
    {
        for (int j = 0; j < puzzle[i].size(); j++)
        {
            for (const std::pair<int, int> dir : directions)
                ans += search(j,i,dir.first,dir.second,0);
        }
    }
    std::cout << ans << std::endl;
}


int main()
{
    puzzle = std::vector<std::string>();
    std::string line;
    while (std::getline(std::cin, line, '\n'))
    {
        if (line.empty()) continue;
        puzzle.push_back(line);
    }
    solve();
}