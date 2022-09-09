#include <bits/stdc++.h>

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

class Number;
typedef std::shared_ptr<Number> NumberPtr;

class Number
{
public:
    NumberPtr left, right;
    Number *parent;

    bool isValue = false;
    int value;

    bool isLeft = false;

    Number(std::string str, Number *mParent = nullptr, bool l = false)
    {
        parent = mParent;
        isLeft = l;
        if (str.front() != '[')
        {
            value = atoi(str.c_str());
            isValue = true;
        }
        else
        {
            auto p = split(str);
            left = std::make_shared<Number>(p.first, this, true);
            right = std::make_shared<Number>(p.second, this, false);
        }
    }

    Number(NumberPtr l, NumberPtr r)
    {
        parent = nullptr; isLeft = false;
        left = l; right = r;
        isValue = false;
        left->parent = this; left->isLeft = true;
        right->parent = this; right->isLeft = false;
    }

    unsigned long long magnitude()
    {
        if (isValue) return static_cast<unsigned long long>(value);
        else return left->magnitude() * 3 + right->magnitude() * 2;
    }

    bool reduce()
    {
        if (reduceExplode()) return true;
        return reduceSplit();
    }

    bool reduceExplode(int depth = 0)
    {
        if (isValue)
            return false;
        else
        {
            if (depth >= 4)
            {
                // Explode
                if (!left->isValue || !right->isValue)
                    std::cout << "Explode Depth Error" << std::endl;
                auto l = nextLeft();
                if (l != nullptr)
                    l->value += left->value;
                auto r = nextRight();
                if (r != nullptr)
                    r->value += right->value;
                left = std::shared_ptr<Number>(nullptr);
                right = std::shared_ptr<Number>(nullptr);
                isValue = true;
                value = 0;
                return true;
            }
        }
        if (left->reduceExplode(depth + 1))
            return true;
        if (right->reduceExplode(depth + 1))
            return true;
        return false;
    }

    bool reduceSplit()
    {
        if (isValue)
        {
            if (value < 10)
                return false;
            else
            {
                isValue = false;
                left = std::make_shared<Number>(std::to_string(value / 2), this, true);
                right = std::make_shared<Number>(std::to_string(value / 2 + ((value % 2 == 0) ? 0 : 1)), this, false);
                return true;
            }
        }
        if (left->reduceSplit())
            return true;
        if (right->reduceSplit())
            return true;
        return false;
    }

    Number *nextLeft()
    {
        if (parent == nullptr)
            return nullptr;
        if (isLeft)
        {
            auto root = parent->firstNotLeft();
            if (root == nullptr)
                return nullptr;
            if (root->parent == nullptr)
                return nullptr;
            return root->parent->left->traverseRight();
        }
        else
        {
            return parent->left->traverseRight();
        }
    }

    Number *nextRight()
    {
        if (parent == nullptr)
            return nullptr;
        if (isLeft)
        {
            return parent->right->traverseLeft();
        }
        else
        {
            auto root = parent->firstNotRight();
            if (root == nullptr)
                return nullptr;
            if (root->parent == nullptr)
                return nullptr;
            return root->parent->right->traverseLeft();
        }
    }

    Number *firstNotRight()
    {
        if (isLeft)
            return this;
        if (parent == nullptr)
            return nullptr;
        return parent->firstNotRight();
    }

    Number *firstNotLeft()
    {
        if (!isLeft)
            return this;
        if (parent == nullptr)
            return nullptr;
        return parent->firstNotLeft();
    }

    Number *traverseRight()
    {
        if (isValue)
            return this;
        return right->traverseRight();
    }

    Number *traverseLeft()
    {
        if (isValue)
            return this;
        return left->traverseLeft();
    }

private:
    std::pair<std::string, std::string> split(std::string str)
    {
        int ctr = -1;
        int mark = 0;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '[')
                ++ctr;
            else if (str[i] == ']')
                --ctr;
            else if (str[i] == ',' && ctr == 0)
                mark = i;
        }
        return std::make_pair(str.substr(1, mark - 1), str.substr(mark + 1, str.length() - mark - 2));
    }

    friend std::ostream &operator<<(std::ostream &os, const Number &n);
};

std::ostream &operator<<(std::ostream &os, const Number &n)
{
    if (n.isValue)
        os << n.value;
    else
        os << "[" << *n.left << "," << *n.right << "]";
    return os;
}

NumberPtr add(NumberPtr a, std::string s)
{
    return std::make_shared<Number>(a, std::make_shared<Number>(s));
}
