#include <bits/stdc++.h>

std::vector<std::vector<int>> costs;

enum Direction {
    North = 0b0001,
    South = 0b0100,
    East = 0b0010,
    West = 0b1000,
};

struct State{
    int x, y;
    int straight_counter;
    Direction direction;
    unsigned long long cost;

    void move_forward()
    {
        straight_counter++;
        if (direction == North) y--;
        else if (direction == South) y++;
        else if (direction == East) x++;
        else if (direction == West) x--;

        if (valid()) cost += costs[y][x];
    }

    void turn_left()
    {
        if (direction == North) direction = West;
        else if (direction == West) direction = South;
        else if (direction == South) direction = East;
        else if (direction == East) direction = North;
        straight_counter = 0;
    }

    void turn_right()
    {
        if (direction == North) direction = East;
        else if (direction == East) direction = South;
        else if (direction == South) direction = West;
        else if (direction == West) direction = North;
        straight_counter = 0;
    }

    bool valid() const
    {
        return x>=0 && y>=0 && x < costs[0].size() && y < costs.size() && straight_counter <= 10;
    }

    std::string position() const
    {
        std::stringstream ss;
        ss << x << " " << y << " " << (int)direction << " " << straight_counter;
        return ss.str();
    }
};

std::priority_queue<State, std::vector<State>, std::function<bool(const State&, const State&)>> check_queue;
std::unordered_set<std::string> explored;

void try_add_state(const State& state)
{
    if (state.valid())
    {
        std::string p = state.position();
        if (explored.find(p) == explored.end())
        {
            check_queue.push(state);
            explored.insert(p);
        }
    }
}

void propagate_state(const State& state)
{
    State forward = State(state);
    forward.move_forward();
    try_add_state(forward);

    if (state.straight_counter >= 4)
    {
        State left = State(state);
        left.turn_left();
        left.move_forward();
        try_add_state(left);

        State right = State(state);
        right.turn_right();
        right.move_forward();
        try_add_state(right);
    }
}

void solve()
{
    check_queue.push(State{1,0,1,East,(unsigned long long)costs[0][1]});
    check_queue.push(State{0,1,1,South,(unsigned long long)costs[1][0]});

    while (!check_queue.empty())
    {
        const State current = check_queue.top();
        if (current.y == costs.size()-1 && current.x == costs[0].size()-1 && current.straight_counter >= 4) break;
        check_queue.pop();

        propagate_state(current);
    }
    std::cout << check_queue.top().cost << std::endl;
}

int main()
{
    check_queue = std::priority_queue<State, std::vector<State>, std::function<bool(const State&, const State&)>>(
        [](const State& l, const State& r){ return l.cost > r.cost; });

    costs = std::vector<std::vector<int>>();
    std::string s;
    while (std::cin >> s)
    {
        if (s.empty()) continue;
        std::vector<int> v = std::vector<int>();
        for (const char c : s) v.push_back(c - '0');
        costs.push_back(v);
    }
    solve();
}
