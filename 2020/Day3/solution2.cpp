#include <bits/stdc++.h>

std::vector<std::vector<bool>> map;
int m;

int subSolve(int horz, int vert)
{
    int ctr = 0;
    for (int i = vert; i < map.size(); i += vert)
    {
        ctr += map[i][(i*horz/vert) % m];
    }
    return ctr;
}

long long int solve()
{
    int a1 = subSolve(1,1);
    int a2 = subSolve(3,1);
    int a3 = subSolve(5,1);
    int a4 = subSolve(7,1);
    int a5 = subSolve(1,2);
    printf("%d, %d, %d, %d, %d\n", a1, a2, a3, a4, a5);
    return (long long int)a1*a2*a3*a4*a5;
}

int main()
{
    std::string l;
    map = std::vector<std::vector<bool>>();
    while (std::cin >> l)
    {
        std::vector<bool> row = std::vector<bool>(l.length());
        for (int i = 0; i < l.length(); i++)
        {
            row[i] = l[i] == '#';
        }
        map.push_back(row);
    }
    m = static_cast<int>(map[0].size());

    long long int ans = solve();
    std::cout << ans << std::endl;

}