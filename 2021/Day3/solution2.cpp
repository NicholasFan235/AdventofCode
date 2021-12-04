#include <bits/stdc++.h>

std::vector<std::string> input;
int N;

class Node
{
public:
    int count;
    int val;

    std::shared_ptr<Node> ones;
    std::shared_ptr<Node> zeros;

    Node(int c, int v) : count(c), val(v) {}

    void process(const std::string &s, int i)
    {
        if (i == 0)
            count += 1;
        if (i >= s.length())
            return;
        if (s[i] == '1')
        {
            addOne();
            ones->process(s, i + 1);
        }
        else
        {
            addZero();
            zeros->process(s, i + 1);
        }
    }

    void init()
    {
        if (ones == nullptr)
            ones = std::make_shared<Node>(0, 1);
        if (zeros == nullptr)
            zeros = std::make_shared<Node>(0, 0);
    }

    void addOne()
    {
        init();
        ones->count++;
    }

    void addZero()
    {
        init();
        zeros->count++;
    }
};

std::shared_ptr<Node> makeTree()
{
    std::shared_ptr<Node> tree = std::make_shared<Node>(0, 0);
    for (const std::string &s : input)
    {
        tree->process(s, 0);
    }
    return tree;
}

unsigned long long int getO2(std::shared_ptr<Node> node)
{
    unsigned long long int ans = 0;
    while (node->ones != nullptr)
    {
        if (node->ones->count >= node->zeros->count)
        {
            ++ans;
            node = node->ones;
        }
        else
        {
            node = node->zeros;
        }
        ans <<= 1;
    }
    return ans >> 1;
}

unsigned long long int getCO2(std::shared_ptr<Node> node)
{
    unsigned long long int ans = 0;
    while (node->ones != nullptr)
    {
        if (node->count > 1)
        {
            if (node->ones->count >= node->zeros->count)
            {
                node = node->zeros;
            }
            else
            {
                ++ans;
                node = node->ones;
            }
            ans <<= 1;
        }
        else
        {
            if (node->ones->count > node->zeros->count)
            {
                node = node->ones;
                ++ans;
            }
            else
            {
                node = node->zeros;
            }
            ans <<= 1;
        }
    }
    return ans >> 1;
}

unsigned long long int solve()
{
    std::shared_ptr<Node> tree = makeTree();
    auto o = getO2(tree);
    auto c = getCO2(tree);
    std::cout << "Oxygen: " << o << ", CarbonDioxide: " << c << std::endl;
    return o * c;
}

int main()
{
    std::string s;
    while (std::cin >> s)
    {
        input.push_back(s);
    }
    N = input.size();

    unsigned long long int ans = solve();
    std::cout << ans << std::endl;
}
