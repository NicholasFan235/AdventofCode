#include <bits/stdc++.h>


std::map<int, std::vector<std::map<std::string, int>>> games;
std::map<std::string, int> max_cubes{
    {"red", 12}, {"green", 13}, {"blue", 14}
};


void interpret_game(std::istream& ss)
{
    std::string s;
    ss >> s;
    if (s != "Game")
    {
        return;
    }
    int game_num;
    ss >> game_num >> s;

    bool more_rounds = true;
    while (more_rounds)
    {
        games[game_num].push_back(std::map<std::string, int>());
        std::map<std::string, int>& round = games[game_num].back();
        bool more_rolls = true;
        while (more_rolls)
        {
            int n;
            ss >> n >> s;
            char c = s.back();
            
            switch (c)
            {
            case ',':
                s.pop_back();
                break;
            case ';':
                s.pop_back();
                more_rolls = false;
                break;
            default:
                more_rolls = false;
                more_rounds = false;
                break;
            }
            round[s] += n;
        }
    }
}

void print_games()
{
    for (const auto& p : games)
    {
        std::cout << "Game #" << p.first << std::endl;
        for (const auto& q : p.second)
        {
            for (const auto& r : q)
            {
                std::cout << '\t' << r.first << ": " << r.second << ' ';
            }
            std::cout << std::endl;
        }
    }
}

void solve()
{
    unsigned long long sum = 0;
    for (const auto& game : games)
    {
        bool b = false;
        sum += game.first;
        for (const auto& group : game.second)
        {
            for (const auto& p : group)
            {
                if (p.second > max_cubes[p.first])
                {
                    sum -= game.first;
                    b = true;
                    break;
                }
            }
            if (b) break;
        }
    }
    std::cout << sum << std::endl;
}


int main()
{
    while (std::cin)
    {
        interpret_game(std::cin);
    }
    solve();
}