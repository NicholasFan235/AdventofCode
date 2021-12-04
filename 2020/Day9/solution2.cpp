#include <bits/stdc++.h>

//#define PREV_ANSWER 10884537 // input.txt
#define PREV_ANSWER 530627549 // input2.txt

std::vector<long long int> data;


int solve()
{
    int front = 0, back = 1;
    long long int sum = data[0] + data[1];

    while (sum != PREV_ANSWER)
    {
        if (front >= back || back >= data.size()) return -1;
        if (sum < PREV_ANSWER) sum+=data[++back];
        if (sum > PREV_ANSWER) sum-=data[front++];
    }

    long long int min = data[front], max = 0;
    for (int i = front; i<=back; i++)
    {
        min = std::min(min, data[i]);
        max = std::max(max, data[i]);
    }
    printf("%d -> %d, %lld + %lld = %lld\n", front, back, min, max, min+max);
    return 0;
}


int main()
{
    data = std::vector<long long int>();
    long long int n;
    while (!std::cin.eof())
    {
        std::cin >> n;
        data.push_back(n);
    }

    int err = solve();
    std::cout << err << std::endl;
}


