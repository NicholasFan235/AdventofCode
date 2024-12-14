#include <bits/stdc++.h>


struct Lens
{
    std::string label;
    int focal_length;
};

struct Box
{
    std::set<std::string> lens_labels;
    std::list<Lens> lens_list;
};

int hash(const std::string& s)
{
    int ans = 0;
    for (const char& c : s) ans = ((ans+static_cast<int>(c))*17)%256;
    return ans;
}

struct Instruction
{
    std::string label;
    int box;
    char operation;
    int focal_length=0;

    Instruction(std::string s)
    {
        if (s.back() == '-')
        {
            s.pop_back();
            operation = '-';
        }
        else
        {
            focal_length = s.back() - '0';
            operation = '=';
            s.pop_back(); s.pop_back();
        }
        label = s;
        box = hash(s);
    }
};


std::vector<std::string> input;
std::vector<Box> boxes;
std::vector<Instruction> instructions;

void apply_instruction(const Instruction& instruction)
{
    Box& box = boxes.at(instruction.box);
    if (instruction.operation == '-')
    {
        if (box.lens_labels.find(instruction.label) != box.lens_labels.end())
        {
            box.lens_labels.erase(instruction.label);
            auto it = box.lens_list.begin();
            while (it->label != instruction.label) ++it;
            box.lens_list.erase(it);
        }
    }
    else if (instruction.operation == '=')
    {
        if (box.lens_labels.find(instruction.label) != box.lens_labels.end())
        {
            auto it = box.lens_list.begin();
            while (it->label != instruction.label) ++it;
            it->focal_length = instruction.focal_length;
        }
        else
        {
            box.lens_labels.insert(instruction.label);
            box.lens_list.emplace_back(Lens{instruction.label, instruction.focal_length});
        }
    }
}

void solve()
{
    boxes = std::vector<Box>(256);
    
    for (const Instruction& instruction : instructions) apply_instruction(instruction);

    unsigned long long power = 0;
    for (int b = 0; b < boxes.size(); b++)
    {
        Box& box = boxes[b];

        int ctr = 0;
        for (auto it = box.lens_list.begin(); it != box.lens_list.end(); ++it)
        {
            power += static_cast<unsigned long long>((b+1) * ++ctr * it->focal_length);
        }
    }
    std::cout << power << std::endl;
}

int main()
{
    instructions = std::vector<Instruction>();
    input = std::vector<std::string>();

    std::string s;
    while (getline(std::cin, s, ','))
    {
        if (s.empty()) continue;
        if (s.back() == '\n') s.pop_back();
        input.push_back(s);
        instructions.emplace_back(s);
    }
    solve();
}