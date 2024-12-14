#include <bits/stdc++.h>



struct Hand
{
    char cards[6];
    int bid;
    int strength;
    Hand(const std::string& s, const int& bid) : bid(bid)
    {
        for (int i = 0; i < 5; i++)
        {
            cards[i] = s[i];
        }
        cards[5] = '\0';

        compute_strength();
    }

private:
    void compute_strength()
    {
        std::map<char, int> card_map;
        for (int i= 0 ; i < 5; i++) card_map[cards[i]]++;

        if (card_map.size() == 1)
        {
            strength = 7; return;
        }

        if (card_map.size() == 2)
        {
            if (card_map.begin()->second == 1 || card_map.begin()->second == 4)
            {
                strength = 6; return;
            }
            strength = 5; return;
        }

        std::map<int, int> num_counts;
        for (const auto& p : card_map) num_counts[p.second]++;
        if (num_counts[3] == 1)
        {
            strength = 4; return;
        }
        if (num_counts[2] == 2)
        {
            strength = 3; return;
        }
        if (num_counts[2] == 1)
        {
            strength = 2; return;
        }
        if (num_counts[1] == 5)
        {
            strength = 1;
            return;
        }
        std::cout << "Cannot Classify Hand: " << cards << std::endl;
    }
};

std::map<char, int> cardRankMap{
    {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
};

bool operator>(const Hand& l, const Hand& r)
{
    if (l.strength == r.strength)
    {
        for (int i = 0; i < 5; i++)
        {
            if (cardRankMap[l.cards[i]] == cardRankMap[r.cards[i]])
            {
                continue;
            }
            return cardRankMap[l.cards[i]] > cardRankMap[r.cards[i]];
        }
        return false;
    }
    return l.strength > r.strength;
}

bool operator==(const Hand& l, const Hand& r)
{
    if (l.strength != r.strength) return false;
    for (int i = 0; i < 5; i++) if (l.cards[i] != r.cards[i]) return false;
    return true;
}

bool operator!=(const Hand& l, const Hand& r)
{
    return !(l==r);
}

bool operator>=(const Hand& l, const Hand& r)
{
    return l>r || l==r;
}

bool operator<(const Hand& l, const Hand& r)
{
    return !(l>=r);
}

bool operator<=(const Hand& l, const Hand& r)
{
    return !(l>r);
}

std::vector<Hand> hands;

std::map<int, std::string> classificationMap{
    {0, "Unclassified"},{1, "High card"}, {2, "One pair"}, {3, "Two pair"}, {4, "Three of a kind"}, {5, "Full house"}, {6, "Four of a kind"}, {7, "Five of a kind"}
};


void solve()
{
    std::sort(hands.begin(), hands.end(), std::less<Hand>());
    // for (int i = 0; i < hands.size(); i++)
    // {
    //     std::cout << hands[i].cards << " " <<  classificationMap[hands[i].strength] << " " << hands[i].bid << std::endl;
    // }

    unsigned long long ans = 0;
    for (int i = 0; i < hands.size(); i++)
    {
        ans += (unsigned long long)(i+1) * hands[i].bid;
    }
    std::cout << ans << std::endl;
}

int main()
{
    hands = std::vector<Hand>();

    std::string s;
    while (std::cin >> s)
    {
        int value;
        std::cin >> value;
        hands.push_back(Hand(s, value));
    }

    solve();
}
