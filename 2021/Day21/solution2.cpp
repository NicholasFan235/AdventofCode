#include <bits/stdc++.h>

struct State
{
    int p1, p2, s1, s2;
    bool p1Turn;
};

struct compare
{
    bool operator()(const State& l, const State& r) const
    {
        if (l.s1 != r.s1) return l.s1 < r.s1;
        if (l.s2 != r.s2) return l.s2 < r.s2;
        if (l.p1 != r.p1) return l.p1 < r.p1;
        if (l.p2 != r.p2) return l.p2 < r.p2;
        return l.p1Turn < r.p1Turn;
    }
};
std::vector<std::pair<int, int>> rolls = {{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1}};

std::map<State, unsigned long long, compare> states;

unsigned long long p1Wins, p2Wins;

void solve()
{
    while (!states.empty())
    {
        auto state = states.begin();

        for (const auto& roll : rolls)
        {
            auto nextState = std::make_pair(state->first, state->second * roll.second);
            nextState.first.p1Turn = !state->first.p1Turn;
            if (state->first.p1Turn)
            {
                nextState.first.p1 = ((nextState.first.p1 + roll.first - 1) % 10) + 1;
                nextState.first.s1 += nextState.first.p1;

                if (nextState.first.s1 >= 21) p1Wins += nextState.second;
                else states[nextState.first] += nextState.second;
            }
            else
            {
                nextState.first.p2 = ((nextState.first.p2 + roll.first - 1) % 10) + 1;
                nextState.first.s2 += nextState.first.p2;

                if (nextState.first.s2 >= 21) p2Wins += nextState.second;
                else states[nextState.first] += nextState.second;
            }
        }

        states[state->first] -= state->second;
        if (states[state->first] <= 0) states.erase(state->first);
    }

    std::cout << "P1 Wins " << p1Wins << " times, P2 Wins " << p2Wins << " times." << std::endl;
    std::cout << std::max(p1Wins, p2Wins) << std::endl;
}

int main()
{
    std::string s;

    std::regex regex("^Player [1,2] starting position: ([0-9]*)$");
    std::smatch match;
    int p1, p2;
    getline(std::cin, s);
    if (std::regex_search(s, match, regex))
        p1 = atoi(match[1].str().c_str());
    getline(std::cin, s);
    if (std::regex_search(s, match, regex))
        p2 = atoi(match[1].str().c_str());
    states[{p1, p2, 0, 0, true}] = 1;
    p1Wins = 0; p2Wins = 0;

    solve();
}
