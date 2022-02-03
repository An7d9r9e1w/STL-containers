#include <iostream>
#include <functional>

struct equal : std::binary_function<int, int, bool>
{
    bool operator()(int a, int b)
    {
        return a == b;
    }
};

int main(void)
{
    equal a;
    std::cout << a(1, 1) << '\n';
    return 0;
}
