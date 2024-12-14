#include <bits/stdc++.h>

struct Pulse
{
    std::string origin, destination;
    bool high;
};

std::ostream& operator<<(std::ostream& os, const Pulse& p)
{
    os << p.origin << (p.high ? " -high-> " : " -low-> ") << p.destination;
    return os;
}

std::vector<Pulse> pulse_history;
std::queue<Pulse> pulse_queue;


struct Module
{
public:
    std::string name;
    std::vector<std::string> connections;

    Module() : name(), connections() {}
    Module(std::string n) : name(n), connections() {}
    Module(const Module& m) : name(m.name), connections() {
        for (const auto& s : m.connections) connections.push_back(s); }

    virtual void operator()(const Pulse& high) {}
    virtual void add_input(std::string input) {}

    void send_pulse(bool high)
    {
        for (const std::string& c : connections)
            pulse_queue.push(Pulse{name, c, high});
    }
};

struct FlipFlop : Module
{
    bool state = false;

    FlipFlop() : Module() {}
    FlipFlop(std::string n) : Module(n) {}

    virtual void operator()(const Pulse& p) override
    {
        if (p.high) return;
        state = !state;
        send_pulse(state);
    }
};

struct Conjunction : Module
{
    bool state = false;
    std::map<std::string, bool> inputs;

    Conjunction() : Module(), inputs() {}
    Conjunction(std::string n) : Module(n), inputs() {}
    virtual void add_input(std::string input) override
    {
        inputs[input] = false;
    }

    virtual void operator()(const Pulse& p) override
    {
        inputs[p.origin] = p.high;

        bool all_high = true;
        for (const auto& i : inputs) if (i.second != true) all_high = false;

        send_pulse(!all_high);
    }
};

struct Broadcast : Module
{
    Broadcast() : Module() {}
    Broadcast(std::string n) : Module(n) {}

    virtual void operator()(const Pulse& p) override
    {
        send_pulse(p.high);
    }
};


std::ostream& operator<<(std::ostream& os, Module& m)
{
    Module* mp = &m;
    if (dynamic_cast<FlipFlop*>(mp) != nullptr) os << "FlipFlop ";
    if (dynamic_cast<Conjunction*>(mp) != nullptr) os << "Conjunction ";
    if (dynamic_cast<Broadcast*>(mp) != nullptr) os << "Broadcast "; 
    os << m.name << " -> ";
    for (int i = 0; i < m.connections.size(); i++) os << (i==0 ? "" : ", ") << m.connections.at(i);
    return os;
}


std::map<std::string, Module*> modules;


void link_conjugation_modules()
{
    for (const auto& p : modules)
    {
        for (const std::string m : p.second->connections)
        {
            if (modules.find(m) != modules.end())
                modules.at(m)->add_input(p.first);
        }
    }
}

void push_button()
{
    pulse_queue.push(Pulse{"button", "broadcaster", false});
    while (!pulse_queue.empty())
    {
        Pulse p = pulse_queue.front();
        pulse_queue.pop();
        pulse_history.push_back(p);

        if (modules.find(p.destination) != modules.end())
            modules.at(p.destination)->operator()(p);
    }
}

void solve()
{
    link_conjugation_modules();
    pulse_history = std::vector<Pulse>();

    for (int i = 0; i < 1000; i++)
    {
        push_button();
    }

    long long int highs = 0, lows = 0;
    for (const Pulse& p : pulse_history)
    {
        if (p.high) highs++;
        else lows++;
    }
    std::cout << highs * lows << std::endl;
}

int main()
{
    std::string line;
    while (std::getline(std::cin, line, '\n'))
    {
        if (line.empty()) break;

        std::stringstream ss(line);
        char c; std::string name, b;

        ss >> c >> name >> b;
        if (c == 'b') name = c+name;
        
        Module* module;
        switch (c)
        {
            case 'b': module = new Broadcast(name); break;
            case '%': module = new FlipFlop(name); break;
            case '&': module = new Conjunction(name); break;
            default: std::cout << "Unknown module type " << c << std::endl; break;
        }

        std::string s;
        while (ss >> s)
        {
            if (s.empty()) continue;
            if (s.back() == ',') s.pop_back();
            module->connections.push_back(s);
        }
        modules[module->name] = module;
    }
    solve();
}
