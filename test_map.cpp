#include <iostream>
#include <string>

#include <ctime>
#include <map>

#include "map.hpp"

//using namespace ft;

#define SIZE 1000000

void test()
{
    clock_t start, stop;
    double ins, del;

    ft::map<int, int> m1;
    std::map<int, int> m2;

    start = std::clock();
    for (int i = 0; i < SIZE; ++i)
    {
        m1.insert(ft::make_pair(i, (i * 10)));
    }
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    for (int i = 0; i < SIZE; ++i)
    {
        m2.insert(std::make_pair(i, (i * 10)));
    }
    stop = std::clock();
    del = stop - start;

    typedef ft::map<int,int>::iterator iter1;
    typedef std::map<int,int>::iterator iter2;

    // print
/*    iter1 end1 = m1.end();
    for (iter1 i = m1.begin(); i != end1; ++i)
        std::cout << i->second << ' ';
    std::cout << '\n';

    iter2 end2 = m2.end();
    for (iter2 i = m2.begin(); i != end2; ++i)
        std::cout << i->second << ' ';
    std::cout << '\n';
*/
    std::cout << "create t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "create m = " << del / CLOCKS_PER_SEC << " s\n\n";

    start = std::clock();
    ft::map<int,int> m1p(m1);
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    std::map<int,int> m2p(m2);
    stop = std::clock();
    del = stop - start;
    std::cout << "copy t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "copy m = " << del / CLOCKS_PER_SEC << " s\n\n";

    start = std::clock();
    m1p.clear();
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    m2p.clear();
    stop = std::clock();
    del = stop - start;
    std::cout << "clear t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "clear m = " << del / CLOCKS_PER_SEC << " s\n\n";

    start = std::clock();
    m1p = m1;
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    m2p = m2;
    stop = std::clock();
    del = stop - start;
    std::cout << "recopy t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "recopy m = " << del / CLOCKS_PER_SEC << " s\n\n";

    start = std::clock();
    m1p.erase(m1p.begin(), m1p.end());
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    m2p.erase(m2p.begin(), m2p.end());
    stop = std::clock();
    del = stop - start;
    std::cout << "erase t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "erase m = " << del / CLOCKS_PER_SEC << " s\n\n";

//    ft::map<int,int> m1p;
//    std::map<int,int> m2p;

    start = std::clock();
    m1p.insert(m1.begin(), m1.end());
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    m2p.insert(m2.begin(), m2.end());
    stop = std::clock();
    del = stop - start;
    std::cout << "range t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "range m = " << del / CLOCKS_PER_SEC << " s\n\n";
}

template <class Key, class Val>
void max_size_test()
{
    ft::map<Key,Val> m1;
    std::map<Key,Val> m2;

    std::cout << m1.max_size() << '\n' << m2.max_size() << '\n';
}

int main()
{
    max_size_test<int,int>();
    max_size_test<int,double>();
    max_size_test<double,double>();
    max_size_test<std::string,std::string>();
    return 0;
}
