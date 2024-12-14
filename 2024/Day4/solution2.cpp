#include <bits/stdc++.h>


std::vector<std::string> puzzle;

inline bool check_mas(const char& a, const char& b, const char& c)
{
    return b=='A' && ((a=='M' && c=='S') || (a=='S' && c=='M'));
}

inline bool check(const int& i, const int& j)
{
    if (i<1 || i>=puzzle.size()-1 || j<1 || j>=puzzle[i].size()-1) return false;
    return check_mas(puzzle[i-1][j-1], puzzle[i][j], puzzle[i+1][j+1]) &&
        check_mas(puzzle[i-1][j+1], puzzle[i][j], puzzle[i+1][j-1]);
}

void solve()
{
    unsigned long long ans = 0;
    for (int i = 0; i < puzzle.size(); i++)
    {
        for (int j = 0; j < puzzle[i].size(); j++)
        {
            ans += check(i,j);
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