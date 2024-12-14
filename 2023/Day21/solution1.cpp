#include <bits/stdc++.h>

typedef std::pair<std::pair<int, int>, int> State;

std::vector<std::string> map;
std::vector<std::vector<bool>> visited;
int start_x, start_y;
std::set<State> explored_states;
std::queue<State> check_queue;
std::set<std::pair<int, int>> final_locations;


State make_state(int x, int y, int steps)
{
    return std::make_pair(std::make_pair(x, y), steps);
}


void explore_state(const State s)
{
    if (map[s.first.second][s.first.first] == '#') return;

    if (explored_states.find(s) != explored_states.end()) return;

    explored_states.insert(s);
    check_queue.push(s);
}


void solve()
{
    explored_states= std::set<State>();
    final_locations = std::set<std::pair<int, int>>();

    State start = make_state(start_x, start_y, 64);
    explored_states.insert(start);
    check_queue.push(start);

    while (!check_queue.empty())
    {
        State s = check_queue.front();
        check_queue.pop();

        if (s.second <= 0)
        {
            final_locations.insert(s.first);
            continue;
        }

        int x = s.first.first;
        int y = s.first.second;
        int c = s.second;
        if (x > 0) explore_state(make_state(x-1, y, c-1));
        if (y > 0) explore_state(make_state(x, y-1, c-1));
        if (x < map[0].size()-1) explore_state(make_state(x+1, y, c-1));
        if (y < map.size()-1) explore_state(make_state(x, y+1, c-1));
    }

    std::cout << final_locations.size() << std::endl;
}


int main()
{
    map = std::vector<std::string>();
    
    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) break;
        map.push_back(s);
    }

    visited = std::vector<std::vector<bool>>(map.size(),
        std::vector<bool>(map.front().size(), false));

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 'S')
            {
                start_x = j; start_y = i;
            }
        }
    }

    solve();
}
