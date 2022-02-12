#include <iostream>

#include <ctime>
#include <map>

#include "tree/tree.hpp"
#include "functional.hpp"

using namespace ft;

template <typename T>
struct test_less
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    }
};

template <typename V>
void _print(const _Rb_tree_node_base* n, const int tabs)
{
    for (int i = 0; i < tabs; ++i)
        std::cout << "    ";
    if (n)
    {
        const _Rb_tree_node<V>* const& x = static_cast<const _Rb_tree_node<V>*>(n);
        std::cout << '[' << x->value_field.first << ',' << x->value_field.second
            << ',' << (n->color == RED ? 'R' : 'B') << ']' << '\n';
        _print<V>(n->left, tabs + 1);
        _print<V>(n->right, tabs + 1);
    }
    else
        std::cout << "NULL\n";
}

template <class Tree>
void print_tree(const Tree& t)
{
    _print<typename Tree::value_type>(t._header.header.parent, 0);
}

/*struct A
{
    int a;
    A(const int n) : a(n) { std::cout << "A::ctor(" << a << ")\n"; }
    A(const A& n) : a(n.a) { std::cout << "A::copy ctor(" << a << ")\n"; }
    ~A() { std::cout << "A::dtor(" << a << ")\n"; }
};*/

#define SIZE 1000000

int main()
{
    clock_t start, stop;
    double ins, del;
    typedef _Rb_tree<int, ft::pair<int,int>,
        _Select1st<ft::pair<int,int> >, test_less<int> > tree;
    tree t;


    std::map<int, int, test_less<int> > m;

    start = std::clock();
    for (int i = 0; i < SIZE; ++i)
    {
        t.insert(make_pair(i, (i * 10)));
    }
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    for (int i = 0; i < SIZE; ++i)
    {
        m.insert(std::make_pair(i, (i * 10)));
    }
    stop = std::clock();
    del = stop - start;
    std::cout << "create t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "create m = " << del / CLOCKS_PER_SEC << " s\n\n";

    start = std::clock();
    tree tp(t);
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    std::map<int,int, test_less<int> > mp(m);
    stop = std::clock();
    del = stop - start;
    std::cout << "copy t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "copy m = " << del / CLOCKS_PER_SEC << " s\n\n";

    start = std::clock();
    tp.clear();
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    mp.clear();
    stop = std::clock();
    del = stop - start;
    std::cout << "clear t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "clear m = " << del / CLOCKS_PER_SEC << " s\n\n";

    start = std::clock();
    tp = t;
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    mp = m;
    stop = std::clock();
    del = stop - start;
    std::cout << "recopy t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "recopy m = " << del / CLOCKS_PER_SEC << " s\n\n";

    start = std::clock();
    tp.erase(tp.begin(), tp.end());
    stop = std::clock();
    ins = stop - start;

    start = std::clock();
    mp.erase(mp.begin(), mp.end());
    stop = std::clock();
    del = stop - start;
    std::cout << "erase t = " << ins / CLOCKS_PER_SEC << " s\n";
    std::cout << "erase m = " << del / CLOCKS_PER_SEC << " s\n";

    return 0;
}
