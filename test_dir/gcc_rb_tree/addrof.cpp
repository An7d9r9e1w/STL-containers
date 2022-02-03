#include <iostream>
#include <memory>
 
template<class T>
struct Ptr {
    T* pad; // add pad to show difference between 'this' and 'data'
    T* data;
    Ptr(T* arg) : pad(nullptr), data(arg) 
    {
        std::cout << "Ctor this = " << this << std::endl;
    }
 
    ~Ptr() { delete data; }
    T** operator&() { return &data; }
};
 
template<class T>
void f(Ptr<T>* p) 
{
    std::cout << "Ptr   overload called with p = " << p << '\n';
}
 
void f(int** p) 
{
    std::cout << "int** overload called with p = " << p << '\n';
}

template <class T>
T* addressof(T& arg)
{
    return reinterpret_cast<T*>(
            &const_cast<char&>(
            reinterpret_cast<const volatile char&>(arg)));
}

int main() 
{
    Ptr<int> p(new int(42));
    f(&p);                 // calls int** overload
    f(std::addressof(p));  // calls Ptr<int>* overload, (= this)
    f(reinterpret_cast<Ptr<int>*>(
        &const_cast<char&>(
            reinterpret_cast<const volatile char&>(p)))
    );
    f(addressof(p));
    return 0;
}
