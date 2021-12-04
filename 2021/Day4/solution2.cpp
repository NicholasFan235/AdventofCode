#include <bits/stdc++.h>


class Bingo
{
public:
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> mask;
    int N;
    
    Bingo(int n) :
        board(n, std::vector<int>(n)),
        mask(n, std::vector<bool>(n, false)),
        N(n)
    {}

    bool check(int y, int x)
    {
        bool row = true, col = true;
        for (int i = 0; i < N; i++)
        {
            if (!mask[y][i]) row = false;
            if (!mask[i][x]) col = false;
        }
        return row || col;
    }

    bool markPos(int y, int x)
    {
        mask[y][x] = true;
        return check(y,x);
    }

    bool addNumber(int n)
    {
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                if (board[y][x] == n)
                {
                    if (markPos(y, x)) return true;
                }
            }
        }
        return false;
    }

    int score(int n)
    {
        int tot = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (!mask[i][j]) tot += board[i][j];
            }
        }
        return tot * n;
    }
};

std::ostream& operator<<(std::ostream& os, const Bingo& b)
{
    for (int i = 0; i < b.board.size(); i++)
    {
        for (int j = 0; j < b.board[i].size(); j++)
        {
            os << b.board[i][j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

std::vector<int> numbers;
std::vector<Bingo> boards;


long solve()
{
    std::set<int> completed = std::set<int>();
    for (const int n : numbers)
    {
        for (int b = 0; b < boards.size(); b++)
        {
            if (completed.find(b) != completed.end()) continue;

            if (boards[b].addNumber(n))
            {
                completed.insert(b);
            }

            if (completed.size() >= boards.size())
            {
                return boards[b].score(n);
            }
        }
    }

    return -1;
}


int main()
{
    std::string s;
    std::getline(std::cin, s, '\n');
    std::istringstream ss(s);
    int n;
    while (ss >> n)
    {
        numbers.push_back(n);
        char d; ss >> d;
    }

    int i = 0;
    while (std::cin >> n)
    {
        boards.push_back(Bingo(5));
        boards[i].board[0][0] = n;
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (k==0 && j == 0) continue;
                std::cin >> boards[i].board[j][k];
            }
        }
        i++;
    }

    int ans = solve();
    std::cout << ans << std::endl;
}
