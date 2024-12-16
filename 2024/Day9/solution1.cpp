#include <bits/stdc++.h>


std::vector<int> disk;


void solve()
{
    int i = -1;
    while (++i < disk.size())
    {
        if (disk[i] >= 0) continue;
        disk[i] = disk[disk.size()-1];
        disk.pop_back();

        while (disk.back() < 0) disk.pop_back();
    }

    unsigned long long int ans = 0;
    for (int i = 0; i < disk.size(); i++)
    {
        ans += i*disk[i];
    }
    // for (const int c : disk) std::cout << c;
    // std::cout << std::endl;
    std::cout << ans << std::endl;
}

int main()
{
    bool data = true;
    char c;
    int i=0;
    while (std::cin >> c)
    {
        if (data)
            for (char n = '0'; n < c; n++)
                disk.push_back(i);
        else
            for (char n = '0'; n < c; n++)
                disk.push_back(-1);
        data = !data;
        i+=data;
    }

    while (disk.back() < 0) disk.pop_back();
    solve();
}

