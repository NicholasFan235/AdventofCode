#include <bits/stdc++.h>

struct Part
{
    std::map<char, std::pair<int, int>> ratings;
    
    Part() : ratings()
    {
        for (char c : {'x', 'm', 'a', 's'}) ratings[c] = std::make_pair(1, 4000);
    }

    Part(const Part& p) : ratings()
    {
        for (const auto& q : p.ratings) ratings[q.first] = q.second;
    }

    long long int C() const
    {
        long long int r = 1;
        for (const auto& p : ratings)
        {
            r *= static_cast<long long int>(p.second.second - p.second.first + 1);
        }
        return r;
    }
};

std::ostream& operator<<(std::ostream& os, const Part& p)
{
    os << "{";
    for (auto it = p.ratings.begin(); it != p.ratings.end(); ++it)
        os << (it != p.ratings.begin() ? ", " : "") << it->first << ": [" << it->second.first << ", " << it->second.second << "]";
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); ++it)
        os << (it != v.begin() ? " -> " : "") << *it;
    os << "}";
    return os;
}

struct Rule
{
    char c, o;
    int n;
    std::string next_workflow;

    Rule(std::string s)
    {
        if (s.size() > 1 && s[1] == '>' || s[1] == '<')
        {
            std::stringstream ss(s);
            char tmp;
            ss >> c >> o >> n >> tmp >> next_workflow;
        }
        else
        {
            next_workflow = s;
            o = '=';
            n = 0;
        }
    }

    std::pair<int, int> rule_passes(std::pair<int, int> in)
    {
        if (o == '=') return in;
        else if (o == '<')
        {
            if (in.first >= n) return std::make_pair(-1,-1);
            else if (in.second < n) return in;
            else return std::make_pair(in.first, n-1);
        }
        else // o == '>'
        {
            if (in.second <= n) return std::make_pair(-1, -1);
            else if (in.first > n) return in;
            else return std::make_pair(n+1, in.second);
        }
    }

    std::pair<int, int> rule_fails(std::pair<int, int> in)
    {
        if (o == '=') return std::make_pair(-1, -1);
        else if (o == '<')
        {
            if (in.second < n) return std::make_pair(-1, -1);
            else if (in.first >= n) return in;
            else return std::make_pair(n, in.second);
        }
        else // o == '>'
        {
            if (in.first > n) return std::make_pair(-1, -1);
            else if (in.second <= n) return in;
            else return std::make_pair(in.first, n);
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
};


std::map<std::string, Workflow> workflows;
std::vector<Part> allowed_parts;
std::vector<std::string> search_path;

void apply_workflow(std::string n, const Part& p)
{
    Part tmp(p);
    for (Rule& rule : workflows[n].rules)
    {
        std::pair<int, int> rating = tmp.ratings.at(rule.c);

        // rule passes
        Part pass(tmp);
        std::pair<int, int> updated = rule.rule_passes(rating);
        if (updated.first != -1)
        {
            search_path.push_back(rule.next_workflow);
            pass.ratings[rule.c] = updated;
            if (rule.next_workflow == "A") 
            {
                std::cout << search_path << std::endl;
                allowed_parts.push_back(pass);
            }
            else if (rule.next_workflow == "R") {}
            else apply_workflow(rule.next_workflow, pass);
            search_path.pop_back();
        }

        updated = rule.rule_fails(rating);
        if (updated.first == -1) break;
        tmp.ratings[rule.c] = updated;
    }
}

void solve()
{
    search_path = std::vector<std::string>();
    Part p = Part();
    apply_workflow("in", p);
    
    long long int ans = 0;
    for (const auto& part : allowed_parts)
    {
        std::cout << part << ": " << part.C() << std::endl;
        ans += part.C();
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

    solve();
}

