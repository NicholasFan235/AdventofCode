#include <bits/stdc++.h>


enum Move
{
    Rock=0,
    Paper=1,
    Scissors=2
};

enum Outcome
{
    Win=1,
    Draw=0,
    Loss=-1
};


std::vector<std::pair<int,int>> rounds;


void solve()
{
    unsigned long long ans = 0;
    for (const auto& round : rounds)
    {
        Move move = static_cast<Move>((3 + static_cast<int>(round.first) + static_cast<int>(round.second))%3);
        
        ans += static_cast<int>(move)+1 + (static_cast<int>(round.second)+1)*3;
    }
    std::cout << ans << std::endl;
}


int main()
{
    char o,p;
    while (std::cin >> o >> p)
    {
        rounds.push_back(std::make_pair(static_cast<Move>(o-'A'), static_cast<Outcome>(p-'Y')));
    }

    solve();
}
