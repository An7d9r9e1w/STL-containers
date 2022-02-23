#ifndef STACK_H_
#define STACK_H_

#include "vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{
public:
    typedef          Container                  container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

public:
    explicit stack(const Container& cont = Container());
    ~stack();

public:
    stack& operator=(const stack& other);

    /// element access
    reference       top();
    const_reference top() const;

    /// capacity
    bool      empty() const;
    size_type size() const;

    /// modifiers
    void push(const value_type& value);
    void pop();

    /// non-member
    template<class U, class Cont>
    friend bool operator==(const ft::stack<U,Cont>& lhs,
                           const ft::stack<U,Cont>& rhs);
    template<class U, class Cont>
    friend bool operator!=(const ft::stack<U,Cont>& lhs,
                           const ft::stack<U,Cont>& rhs);
    template<class U, class Cont>
    friend bool operator< (const ft::stack<U,Cont>& lhs,
                           const ft::stack<U,Cont>& rhs);
    template<class U, class Cont>
    friend bool operator<=(const ft::stack<U,Cont>& lhs,
                           const ft::stack<U,Cont>& rhs);
    template<class U, class Cont>
    friend bool operator> (const ft::stack<U,Cont>& lhs,
                           const ft::stack<U,Cont>& rhs);
    template<class U, class Cont>
    friend bool operator>=(const ft::stack<U,Cont>& lhs,
                           const ft::stack<U,Cont>& rhs);

protected:
    Container c;
};



template<class T, class Container>
stack<T, Container>::stack(const Container& cont)
    : c(cont)
{
}

template<class T, class Container>
stack<T, Container>::~stack()
{
}

template<class T, class Container>
inline stack<T, Container>&
stack<T, Container>::operator=(const stack& other)
{
    if (this != &other) {
        c = other.c;
    }
    return *this;
}

template<class T, class Container>
typename stack<T, Container>::reference
inline stack<T, Container>::top()
{
    return c.back();
}

template<class T, class Container>
typename stack<T, Container>::const_reference
inline stack<T, Container>::top() const
{
    return c.back();
}

template<class T, class Container>
inline bool stack<T, Container>::empty() const
{
    return c.empty();
}

template<class T, class Container>
typename stack<T, Container>::size_type
inline stack<T, Container>::size() const
{
    return c.size();
}

template<class T, class Container>
inline void stack<T, Container>::push(const value_type& value)
{
    c.push_back(value);
}

template<class T, class Container>
inline void stack<T, Container>::pop()
{
    c.pop_back();
}

template<class T, class Container>
bool operator==(const ft::stack<T,Container>& lhs,
                const ft::stack<T,Container>& rhs)
{
    return lhs.c == rhs.c;
}

template<class T, class Container>
bool operator!=(const ft::stack<T,Container>& lhs,
                const ft::stack<T,Container>& rhs)
{
    return !(lhs == rhs);
}

template<class T, class Container>
bool operator<(const ft::stack<T,Container>& lhs,
               const ft::stack<T,Container>& rhs)
{
    return lhs.c < rhs.c;
}

template<class T, class Container>
bool operator<=(const ft::stack<T,Container>& lhs,
                const ft::stack<T,Container>& rhs)
{
    return lhs.c <= rhs.c;
}

template<class T, class Container>
bool operator>(const ft::stack<T,Container>& lhs,
               const ft::stack<T,Container>& rhs)
{
    return !(lhs <= rhs);
}

template<class T, class Container>
bool operator>=(const ft::stack<T,Container>& lhs,
                const ft::stack<T,Container>& rhs)
{
    return !(lhs < rhs);
}


}

#endif /*STACK_H_*/
