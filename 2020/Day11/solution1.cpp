#include <bits/stdc++.h>


const std::map<char, int> states = {{'#',1}, {'.', 0}, {'L', -1}};

std::vector<std::vector<int>> seats;
int X, Y;

template <typename T>
void printVec(const std::vector<std::vector<T>>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            if (j > 0) std::cout << ", ";
            std::cout << vec[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int numAdjacent(int y, int x)
{
    int ctr = 0;
    for (int i = y-1; i <= y+1; i++)
    {
        for (int j = x-1; j <= x+1; j++)
        {
            if (i < 0 || j < 0 || i >= Y || j >= X) continue;
            if (i==y && j==x) continue;
            ctr += (seats[i][j] == 1);
        }
    }
    return ctr;
}

int step()
{
    int changes = 0;
    std::vector<std::vector<int>> counts = std::vector<std::vector<int>>(Y, std::vector<int>(X));
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            if (seats[i][j] != 0) counts[i][j] = numAdjacent(i, j);
        }
    }
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            if ((seats[i][j] == 1 && counts[i][j] >= 4) || (seats[i][j] == -1 && counts[i][j] == 0))
            {
                seats[i][j]*=-1;
                changes += 1;
            }
        }
    }
    return changes;
}

int count()
{
    int ctr = 0;
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            ctr += (seats[i][j] == 1);
        }
    }
    return ctr;
}

int main()
{
    seats = std::vector<std::vector<int>>();
    while (!std::cin.eof())
    {
        std::string l;
        std::cin >> l;
        if (l.empty()) break;

        std::vector<int> row = std::vector<int>();
        for (const char& c : l)
        {
            row.push_back(states.at(c));
        }
        seats.push_back(row);
    }

    Y = seats.size();
    X = seats[0].size();
    std::cout << Y << " x " << X << std::endl;

    while (true)
    {
        int numChanges = step();
        std::cout << numChanges << std::endl;
        if (numChanges < 1) break;
    }

    int ans = count();
    std::cout << ans << std::endl;

}


