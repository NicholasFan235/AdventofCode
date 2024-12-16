#include <bits/stdc++.h>


std::vector<int> disk;
std::vector<int> file_sizes;
std::map<int,int> empty_blocks;

void print_empty_blocks()
{
    std::vector<bool> d = std::vector<bool>(disk.size(), true);
    for (const auto& b : empty_blocks)
    {
        for (int i = 0; i < b.second; i++)
        {
            d[b.first+i] = false;
        }
    }
    for (const bool b : d) std::cout << (b ? "-" : ".");
    // for (const int c : disk) std::cout << (c<0 ? "." : std::to_string(c%10));
    // for (const int c : disk) std::cout << (c<0? (char)'.' : (char)('0'+c));
    std::cout << std::endl;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U> p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

void condense_blocks()
{
    auto it = empty_blocks.begin();
    while (it != empty_blocks.end())
    {
        const std::pair<int,int> b = *it;

        if (b.second == 0)
        {
            ++it;
            empty_blocks.erase(b.first);
            continue;
        }

        if (empty_blocks.find(b.first+b.second) != empty_blocks.end())
        {
            int merge_loc = b.first+b.second;
            const int merge_size = empty_blocks.at(merge_loc);
            empty_blocks.erase(merge_loc);
            empty_blocks[b.first] = b.second + merge_size;
            // std::cout << "Merged block " << b << " with " << " (" << merge_loc << ", " << merge_size << ")" << std::endl;
            continue;
        }
        ++it;
    }
}


void move(int n, int from, int to)
{
    for (int i = 0; i < n; i++)
    {
        std::swap(disk[from-i], disk[to+i]);
    }
    const std::pair<int,int> b = *empty_blocks.find(to);
    empty_blocks.erase(to);
    if (b.second > n)
    {
        empty_blocks[to+n] = b.second - n;
    }
    empty_blocks[from-n+1] = n;
    // std::cout << from << " " << b.first << " " << b.second << " n=" << n << std::endl;
    // print_empty_blocks();
    condense_blocks();
}


int find_empty_block(int n)
{
    for (const auto& p : empty_blocks)
    {
        if (p.second >= n) return p.first;
    }
    return -1;
}

bool validate()
{
    bool valid = true;
    std::vector<bool> d = std::vector<bool>(disk.size(), true);
    for (const auto& b : empty_blocks)
    {
        for (int i = 0; i < b.second; i++)
        {
            if (i>0)
            {
                if (empty_blocks.find(b.first+i) != empty_blocks.end()) valid = false;
            }
            d[b.first+i] = false;
        }
    }

    for (int i = 0; i < d.size(); i++)
    {
        if ((disk[i]>=0) != d[i]) valid = false;
    }
    std::cout << "Valid: " << valid << std::endl;
    return valid;
}

void print_disk()
{
    for (const int c : disk) std::cout << (c<0 ? "." : "-");
    // for (const int c : disk) std::cout << (c<0 ? "." : std::to_string(c%10));
    // for (const int c : disk) std::cout << (c<0? (char)'.' : (char)('0'+c));
    std::cout << std::endl;
}

void solve()
{
    int max_file_id = file_sizes.size();
    for (int i = disk.size()-1; i>=0; --i)
    {
        if (disk[i] < 0 || disk[i] >= max_file_id) continue;
        int file_id = disk[i];
        max_file_id = file_id;
        const int file_size = file_sizes[file_id];
        int to = find_empty_block(file_size);
        if (to < 0 || to >= i)
        {
            // std::cout << disk[i] << " Can't Move" << std::endl;
            continue;
        }

        // std::cout << "moving file " << file_id << " to location " << to << std::endl;

        move(file_size, i, to);
    }

    unsigned long long int ans = 0;
    for (int i = 0; i < disk.size(); i++)
    {
        if (disk[i] < 0) continue;
        ans += i*disk[i];
    }
    // for (const int c : disk) std::cout << (c<0 ? "." : std::to_string(c%10));
    // // for (const int c : disk) std::cout << (c<0? (char)'.' : (char)('0'+c));
    // std::cout << std::endl;
    validate();
    std::cout << ans << std::endl;
}

int main()
{
    file_sizes = std::vector<int>();
    disk = std::vector<int>();

    bool data = true;
    char c;
    int i=0;
    while (std::cin >> c)
    {
        if (data)
        {
            file_sizes.push_back(c-'0');
            for (char n = '0'; n < c; n++)
                disk.push_back(i);
        }
        else
        {
            empty_blocks[disk.size()] = c-'0';
            for (char n = '0'; n < c; n++)
                disk.push_back(-1);
        }
        data = !data;
        i+=data;
    }
    validate();
    // while (disk.back() < 0) disk.pop_back();
    solve();
}

