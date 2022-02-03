#include <iostream>

#include <map>

int main()
{
    std::map<int, int> m;
    for (int i = 0; i < 3; ++i)
        m.insert(std::make_pair(i + 1, i + 1));
    typedef std::map<int, int>::iterator iter;
    iter end = m.end();
    for (iter i = m.begin(); i != end; ++i)
    {
        std::cout << i->first << ' ';
    }
    std::cout << '\n' << end->first << '\n';
    std::cout << '\n' << (--end)->first << '\n';
    std::cout << '\n' << (++end)->first << '\n';
    std::cout << '\n' << ()->first << '\n';
    return 0;
}
