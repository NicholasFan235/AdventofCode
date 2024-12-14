#include <bits/stdc++.h>

struct Galaxy {
    int x, y;
};


std::vector<std::string> universe;
std::vector<Galaxy> galaxies;
int N, M;
std::vector<int> x_projection;
std::vector<int> y_projection;
std::vector<std::vector<int>> distances;

std::vector<int> x_axis;
std::vector<int> y_axis;


void project()
{
    y_projection = std::vector<int>(N,0);
    x_projection = std::vector<int>(M,0);
    for (const auto& g : galaxies)
    {
        y_projection[g.y]++;
        x_projection[g.x]++;
    }

    y_axis = std::vector<int>(N,0);
    x_axis = std::vector<int>(M,0);
    for (int i = 1; i < N; i++)
        y_axis[i] = y_axis[i-1] + (y_projection[i] != 0 ? 1 : 2);
    for (int j = 1; j < M; j++)
        x_axis[j] = x_axis[j-1] + (x_projection[j] != 0 ? 1 : 2);
}

int calculate_distance(const Galaxy g1, const Galaxy g2)
{
    return std::abs(y_axis[g2.y] - y_axis[g1.y]) + std::abs(x_axis[g2.x] - x_axis[g1.x]);
}

void calculate_distances()
{
    distances = std::vector<std::vector<int>>(galaxies.size(), std::vector<int>(galaxies.size(), 0));
    for (int i = 0; i < galaxies.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            int d = calculate_distance(galaxies[i], galaxies[j]);
            distances[i][j] = d;
            distances[j][i] = d;
        }
    }
}


void solve()
{
    project();
    calculate_distances();

    unsigned long long total = 0;
    for (int i = 0; i < galaxies.size(); i++)
        for (int j = 0; j < i; j++)
            total += distances[i][j];
    std::cout << total << std::endl;
}


int main()
{
    universe = std::vector<std::string>();
    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) continue;
        universe.push_back(s);
    }
    N = universe.size();
    M = universe.front().size();

    galaxies = std::vector<Galaxy>();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (universe[i][j] == '#') galaxies.push_back(Galaxy{j,i});
        }
    }

    solve();
}
