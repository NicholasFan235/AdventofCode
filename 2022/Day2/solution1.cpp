#include <bits/stdc++.h>

std::map<char, char> wins = {{'R', 'S'}, {'S', 'P'}, {'P', 'R'}};

std::vector<std::pair<char,char>> rounds;

int outcome(char o, char p)
{
    if (p == o) return 3;
    if (wins.at(p) == o) return 6;
    return 0;
}

int play_score(char p)
{
    switch (p)
    {
    case 'R': return 1;
    case 'P': return 2;
    case 'S': return 3;
    default:
        std::stringstream ss;
        ss << "Invalid play: " << p;
        throw std::runtime_error(ss.str());
    }
}

unsigned long long score(std::map<char, char> move_map)
{
    unsigned long long ans = 0;
    for (const auto& p : rounds)
    {
        char play = move_map.at(p.second);
        int round_score = play_score(play) + outcome(p.first, play);
        ans += round_score;
    }
    return ans;
}

void solve()
{
    const std::map<char,char> move_map = {{'X','R'}, {'Y','P'}, {'Z','S'}};
    unsigned long long ans = score(move_map);
    std::cout << ans << std::endl;
}


const std::map<char,char> opponent_map = {{'A','R'}, {'B','P'}, {'C','S'}};
int main()
{
    char o,p;
    while (std::cin >> o >> p)
    {
        rounds.push_back(std::make_pair(opponent_map.at(o),p));
    }

    solve();
}
