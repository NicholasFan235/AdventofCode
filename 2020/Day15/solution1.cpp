#include <bits/stdc++.h>


std::vector<int> seq;
std::map<int, int> graph;
int nextNum;
int target;

unsigned long solve()
{
    int i = seq.size();
    while (i < target)
    {
        //std::cout << nextNum << " -> ";
        if (graph.find(nextNum) == graph.end())
        {
            // new number
            seq.push_back(nextNum);
            graph[nextNum] = i;
            nextNum = 0;
            //std::cout << 0 << std::endl;
        }
        else
        {
            seq.push_back(nextNum);
            int nextnextNum = i - graph[nextNum];
            //std::cout << nextnextNum << " from pos " << graph[nextNum] << std::endl;
            graph[nextNum] = i;
            nextNum = nextnextNum;
        }
        i++;
    }
    //std::cout << std::endl;
    return seq[i-1];
}

void reset()
{
    seq = std::vector<int>();
    graph.clear();
}

int main()
{
    int T;
    std::cin >> T;

    std::cin >> target;

    for (int t = 1; t <= T; t++)
    {
        reset();
        int n;
        std::cin >> n;
        for (int i = 0; i < n; i++)
        {
            int num;
            std::cin >> num;
            if (i < n-1)
            {
                graph[num] = i;
                seq.push_back(num);
            }
            else
            {
                nextNum = num;
            }
        }

        std::cout << "Test Case #" << t << ": " << solve() << std::endl;
    }
}
