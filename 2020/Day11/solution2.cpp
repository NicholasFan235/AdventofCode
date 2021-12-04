#include <bits/stdc++.h>


const std::map<char, int> states = {{'#',1}, {'.', 0}, {'L', -1}};

std::vector<std::vector<int>> seats;
int Y, X;

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

void printSeats()
{
    for (int i = 0; i < seats.size(); i++)
    {
        for (int j = 0; j < seats[i].size(); j++)
        {
            if (seats[i][j] == 1) std::cout << '#';
            else if (seats[i][j] == -1) std::cout << 'L';
            else std::cout << '.';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int lookDir(int y, int x, int down, int right)
{
    int xi = x + right, yi = y + down;
    while (xi < X && xi >= 0 && yi < Y && yi >= 0)
    {
        if (seats[yi][xi] == 1) return 1;
        if (seats[yi][xi] == -1) return 0;
        xi += right;
        yi += down;
    }
    return 0;
}

int numSeen(int y, int x)
{
    return
        lookDir(y, x, 1, 0) +
        lookDir(y, x, -1, 0) +
        lookDir(y, x, 0, 1) +
        lookDir(y, x, 0, -1) +
        lookDir(y, x, 1, 1) +
        lookDir(y, x, 1, -1) +
        lookDir(y, x, -1, 1) +
        lookDir(y, x, -1, -1);
}

int step()
{
    //printSeats();
    int changes = 0;
    std::vector<std::vector<int>> counts = std::vector<std::vector<int>>(Y, std::vector<int>(X));
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            if (seats[i][j] != 0) counts[i][j] = numSeen(i, j);
        }
    }
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            if ((seats[i][j] == 1 && counts[i][j] >= 5) || (seats[i][j] == -1 && counts[i][j] == 0))
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
    //printSeats();

    int ans = count();
    std::cout << ans << std::endl;
}


