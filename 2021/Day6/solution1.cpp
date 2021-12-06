#include <bits/stdc++.h>


std::map<int, int> fish;


long long int solve()
{
    std::map<int, int> next;
    for (int d = 1; d <= 80; d++)
    {
        next.clear();
        for (int t = 0; t < 8; t++)
        {
            next[t] = fish[t+1];
        }
        next[6] += fish[0];
        next[8] += fish[0];
        std::swap(fish, next);

        /*
        long long ctr = 0;
        for (int i = 0; i < 9; i++) ctr += fish[i];
        printf("Day %d: %lld\n", d, ctr);
        */
    }

    long long int ctr = 0;
    for (int i = 0; i < 9; i++) ctr += fish[i];
    return ctr;
}

int main()
{
    int n;
    fish.clear();
    while (std::cin >> n)
    {
        fish[n]++;
    }

    std::cout << solve() << std::endl;
}
