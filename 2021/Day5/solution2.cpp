#include <bits/stdc++.h>


std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines;
std::vector<std::vector<int>> vents;
int X, Y;
long N;

void addVent(int y, int x)
{
    vents[y][x]++;
    if (vents[y][x] == 2) N++;
}

long solve()
{
    N = 0;
    for (const auto& l : lines)
    {
        std::pair<int, int> l1 = l.first, l2 = l.second;
        if (l1.first == l2.first)
        {
            for (int y = std::min(l1.second, l2.second); y <= std::max(l1.second, l2.second); y++)
            {
                addVent(y, l1.first);
            }
        }
        else if (l1.second == l2.second)
        {
            for (int x = std::min(l1.first, l2.first); x <= std::max(l1.first, l2.first); x++)
            {
                addVent(l1.second, x);
            }
        }
        else
        {
            for (int i = 0; i <= std::max(l1.first, l2.first) - std::min(l1.first, l2.first); i++)
            {
                //printf("(%d, %d) -> (%d, %d), i = %d\n", l1.first, l1.second, l2.first, l2.second, i);
                int xMul = (l2.first > l1.first) ? 1 : -1;
                int yMul = (l2.second > l1.second) ? 1 : -1;
                //printf("%d, %d\n", l1.first + xMul*i, l1.second + yMul*i);
                addVent(l1.second + yMul*i, l1.first + xMul*i);
            }
        }
    }
    return N;
}

int main()
{
    std::string s;
    char c;
    int n1, n2, n3, n4;

    lines = std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>();
    X = 0; Y = 0;
    while (std::cin >> n1 >> c >> n2 >> s >> n3 >> c >> n4)
    {
        lines.push_back(std::make_pair(
            std::make_pair(n1, n2), std::make_pair(n3, n4)));
        X = std::max(X, std::max(n1, n3));
        Y = std::max(Y, std::max(n2, n4));
    }
    vents = std::vector<std::vector<int>>(Y+1, std::vector<int>(X+1, 0));

    std::cout << solve() << std::endl;
}

