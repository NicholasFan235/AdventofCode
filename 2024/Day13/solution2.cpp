#include <bits/stdc++.h>


const long long offset = 10000000000000;

struct Claw{ long long X=0; long long Y=0; };
struct Machine{ Claw A; Claw B; long long X,Y; };


std::vector<Machine> machines;

std::ostream& operator<<(std::ostream& os, const Claw& c)
{
    os << "Claw("<<c.X<<","<<c.Y<<")";
    return os;
}
std::ostream& operator<<(std::ostream& os, const Machine& m)
{
    os <<"Machine("<<m.A<<","<<m.B<<"("<<m.X<<","<<m.Y<<"))";
    return os;
}

long long solve_machine(const Machine& machine)
{
    long long det = machine.A.X*machine.B.Y - machine.A.Y*machine.B.X;
    if (det == 0) throw std::runtime_error("Degenerate Buttons");
    long long ndetA = machine.B.Y*machine.X - machine.B.X*machine.Y;
    long long ndetB = machine.A.X*machine.Y - machine.A.Y*machine.X;

    if (det < 0)
    {
        det = -det; ndetA = -ndetA; ndetB = -ndetB;
    }

    if ((std::gcd(det, ndetA) != det) || (std::gcd(det, ndetB) != det))
    {
        return -1;
    }

    long long nA = ndetA/det;
    long long nB = ndetB/det;
    return nA*3+nB;
}


void solve()
{
    long long ans = 0;
    for (int i = 0; i < machines.size(); i++)
    {
        const long long cost = solve_machine(machines.at(i));
        std::cout << i << ": " << machines.at(i) << " -> " << cost << std::endl;
        if (cost > 0) ans += cost;
    }
    std::cout << ans << std::endl;
}


int main()
{
    std::string l1, l2, l3;
    while (std::getline(std::cin, l1) && std::getline(std::cin, l2) && std::getline(std::cin, l3))
    {
        const std::regex regex("Button A: X\\+(\\d+), Y\\+(\\d+)Button B: X\\+(\\d+), Y\\+(\\d+)Prize: X=(\\d+), Y=(\\d+)");
        std::smatch m;
        const std::string l = l1+l2+l3;
        if (std::regex_match(l, m, regex))
        {
            machines.push_back({{atoi(m[1].str().c_str()), atoi(m[2].str().c_str())}, {atoi(m[3].str().c_str()), atoi(m[4].str().c_str())}, atoi(m[5].str().c_str())+offset, atoi(m[6].str().c_str())+offset});
        }
        else
        {
            throw std::runtime_error("Bad input: " + l1 + l2 + l3);
        }
        std::getline(std::cin, l1);
    }
    solve();
}

