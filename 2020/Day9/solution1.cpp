#include <bits/stdc++.h>

#define PREAMBLE_SIZE 25

std::vector<long long int> data;


void solve()
{
    std::map<long long int, int> M = std::map<long long int, int>();
    for (int i = 0; i < PREAMBLE_SIZE; i++)
    {
        M[data[i]]++;
    }

    for (int i = PREAMBLE_SIZE; i < data.size(); i++)
    {   
        bool found = false;
        for (const auto& p : M)
        {
            if (p.second < 1) continue;
            long long int other = data[i] - p.first;
            if (M[other] > (other == p.first)) found = true;
        }

        if (!found) std::cout << data[i] << std::endl;
        M[data[i]]++;
        M[data[i-PREAMBLE_SIZE]]--;
    }
}


int main()
{
    data = std::vector<long long int>();
    long long int n;
    while (!std::cin.eof())
    {
        std::cin >> n;
        data.push_back(n);
    }

    solve();
}


