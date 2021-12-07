#include <bits/stdc++.h>



std::vector<int> crabs;
int maxCrab;

unsigned long long eval(int n)
{
    unsigned long long ans = 0;
    for (const auto i : crabs)
    {
        ans += std::abs(n-i);
    }
    return ans;
}

unsigned long long solveBinary()
{
    int l = 0, u = maxCrab+1, m = (l+u)/2;
    unsigned long long el = eval(l), eu = eval(u), em = eval(m);
    while (true)
    {
        if (el < eu)
        {
            u = m; eu = em;
        }
        else
        {
            l = m; el = em;
        }
        m = (l+u)/2;
        em = eval(m);
        if (l==m)
        {
            if (eu < em) { em = eu; m = u; }
            std::cout << m << ": ";
            return em;
        }
    }
}


int main()
{
    int n;
    char c;
    crabs.clear();
    maxCrab = 0;
    while (std::cin >> n)
    {
        crabs.push_back(n);
        maxCrab = std::max(maxCrab, n);
        std::cin >> c;
    }
    std::cout << solveBinary() << std::endl;
}



