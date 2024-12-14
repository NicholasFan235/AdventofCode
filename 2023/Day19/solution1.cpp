#include <bits/stdc++.h>

struct Part
{
    std::map<char, int> ratings;
    
    Part(std::string s) : ratings()
    {
        std::stringstream ss(s);
        char o, c; ss >> o;
        int n;
        while (ss >> c >> o >> n >> o)
        {
            ratings[c] = n;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Part& part)
{
    os << "{";
    for (auto it = part.ratings.begin(); it != part.ratings.end(); ++it)
    {
        os << (it == part.ratings.begin() ? "" : ", ") << it->first << ": " << it->second;
    }
    os << "}";
    return os;
}

struct Rule
{
    std::function<bool(const Part&)> comparator;
    std::string next_workflow;

    Rule(std::string s)
    {
        if (s.size() > 1 && s[1] == '>' || s[1] == '<')
        {
            std::stringstream ss(s);
            char c, o, tmp;
            int n;
            ss >> c >> o >> n >> tmp >> next_workflow;
            comparator = [=](const Part& p)
            {
                if (o == '>') return p.ratings.at(c) > n;
                else if (o == '<') return p.ratings.at(c) < n;
                else
                {
                    std::cout << "Unknown operator " << o << std::endl;
                    return false;
                }
            };
        }
        else
        {
            next_workflow = s;
            comparator = [](const Part&){ return true; };
        }
    }
};

struct Workflow
{
    std::string name;
    std::vector<Rule> rules;

    Workflow(std::string s) : rules()
    {
        std::stringstream ss(s);
        std::getline(ss, name, '{');

        std::string r;
        while (std::getline(ss, r, ','))
        {
            if (r.back() == '}') r.pop_back();
            rules.push_back(Rule(r));
        }
    }

    Workflow() : rules(), name() {}

    std::string apply(const Part& part)
    {
        for (const Rule& rule : rules)
        {
            if (rule.comparator(part)) return rule.next_workflow;
        }
        return "";
    }
};


std::map<std::string, Workflow> workflows;
std::vector<Part> parts;

bool apply_workflow(std::string n, const Part& p)
{
    std::string w = workflows[n].apply(p);
    if (w == "A") return true;
    else if (w == "R") return false;
    else return apply_workflow(w, p);
}

void solve()
{
    long long int ans = 0;
    for (const Part& p : parts)
    {
        bool accepted = apply_workflow("in", p);
        if (accepted)
        {
            for (const auto& p : p.ratings) ans += p.second;
        }
    }
    std::cout << ans << std::endl;
}


int main()
{
    std::string s;
    while (std::getline(std::cin, s))
    {
        if (s.empty()) break;
        Workflow w = Workflow(s);
        workflows[w.name] = w;
    }

    while (std::getline(std::cin, s))
    {
        if (s.empty()) break;
        parts.emplace_back(s);
    }

    solve();
}

