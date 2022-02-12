#ifndef STL_TREE_H_
#define STL_TREE_H_

#include <cstddef>
#include <iterator>

template <class T>
T* addressof(T& arg)
{
    return reinterpret_cast<T*>(
                &const_cast<char&>(
                reinterpret_cast<const volatile char&>(arg)));
}

enum _Rb_tree_color
{
    _S_red = false,
    _S_black = true
};

struct _Rb_tree_node_base
{
    typedef _Rb_tree_node_base* _Base_ptr;
    typedef const _Rb_tree_node_base* _Const_Base_ptr;

    _Rb_tree_color _M_color;
    _Base_ptr      _M_parent;
    _Base_ptr      _M_left;
    _Base_ptr      _M_right;

    static _Base_ptr
    _S_minimum(_Base_ptr __x) throw()
    {
        while (__x->_M_left != 0) __x = __x->_M_left;
        return __x;
    }

    static _Const_Base_ptr
    _S_minimum(_Const_Base_ptr __x) throw()
    {
        while (__x->_M_left != 0) __x = __x->_M_left;
        return __x;
    }

    static _Base_ptr
    _S_maximum(_Base_ptr __x) throw()
    {
        while (__x->_M_right != 0) __x = __x->_M_right;
        return __x;
    }

    static _Const_Base_ptr
    _S_maximum(_Const_Base_ptr __x) throw()
    {
        while (__x->_M_right != 0) __x = __x->_M_right;
        return __x;
    }
};

struct _Rb_tree_header
{
    _Rb_tree_node_base _M_header;
    std::size_t        _M_node_count;

    _Rb_tree_header() throw()
    {
        _M_header._M_color = _S_red;
        _M_reset();
    }

    void _M_move_data(_Rb_tree_header& __from)
    {
        _M_header._M_color = __from._M_header._M_color;
        _M_header._M_parent = __from._M_header._M_parent;
        _M_header._M_left = __from._M_header._M_left;
        _M_header._M_right = __from._M_header._M_right;
        _M_header._M_parent->_M_parent = &_M_header; //TODO WHY?? - for increment/decrement operation
        _M_node_count = __from._M_node_count;

        __from._M_reset();
    }

    void _M_reset()
    {
        _M_header._M_parent = 0;
        _M_header._M_left = &_M_header;
        _M_header._M_right = &_M_header;
        _M_node_count = 0;
    }
};

template <typename _Val>
struct _Rb_tree_node : public _Rb_tree_node_base
{
    typedef _Rb_tree_node<_Val>* _Link_type;

    _Val _M_value_field;

    _Val* _M_valptr()
    {
        return addressof(_M_value_field);
    }

    const _Val* _M_valptr() const
    {
        return addressof(_M_value_field);
    }
};

_Rb_tree_node_base*
_Rb_tree_increment(_Rb_tree_node_base* __x) throw();

const _Rb_tree_node_base*
_Rb_tree_increment(const _Rb_tree_node_base* __x) throw();

_Rb_tree_node_base*
_Rb_tree_decrement(_Rb_tree_node_base* __x) throw();

const _Rb_tree_node_base*
_Rb_tree_decrement(const _Rb_tree_node_base* __x) throw();

template <typename _Tp>
struct _Rb_tree_iterator
{
    typedef _Tp  value_type;
    typedef _Tp& reference;
    typedef _Tp* pointer;

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t                       difference_type;

    typedef _Rb_tree_iterator<_Tp>          _Self;
    typedef _Rb_tree_node_base::_Base_ptr   _Base_ptr;
    typedef _Rb_tree_node<_Tp>*             _Link_type;

    _Rb_tree_iterator()
    : _M_node() {}

    explicit
    _Rb_tree_iterator(_Base_ptr __x)
    : _M_node(__x) {}

    reference
    operator*() const
    {
        return *static_cast<_Link_type>(_M_node)->_M_valptr();
    }

    pointer
    operator->() const
    {
        return static_cast<_Link_type>(_M_node)->_M_valptr();
    }

    _Self&
    operator++()
    {
        _M_node = _Rb_tree_increment(_M_node);
        return *this;
    }

    _Self&
    operator++(int)
    {
        _Self __tmp = *this;
        _M_node = _Rb_tree_increment(_M_node);
        return __tmp;
    }

    _Self&
    operator--()
    {
        _M_node = _Rb_tree_decrement(_M_node);
        return *this;
    }

    _Self&
    operator--(int)
    {
        _Self __tmp = *this;
        _M_node = _Rb_tree_decrement(_M_node);
        return __tmp;
    }

    friend bool
    operator==(const _Self& __x, const _Self& __y)
    {
        return __x._M_node == __y._M_node;
    }

    friend bool
    operator!=(const _Self& __x, const _Self& __y)
    {
        return __x._M_node != __y._M_node;
    }

    _Base_ptr _M_node;
};

template <typename _Tp>
struct _Rb_tree_const_iterator
{
    typedef _Tp        value_type;
    typedef const _Tp& reference;
    typedef const _Tp* pointer;

    typedef _Rb_tree_iterator<_Tp> iterator;

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t                       difference_type;

    typedef _Rb_tree_iterator<_Tp>          _Self;
    typedef _Rb_tree_node_base::_Base_ptr   _Base_ptr;
    typedef _Rb_tree_node<_Tp>*             _Link_type;

    _Rb_tree_const_iterator()
    : _M_node() {}

    explicit
    _Rb_tree_const_iterator(_Base_ptr __x)
    : _M_node(__x) {}

    _Rb_tree_const_iterator(const iterator& __it)
    : _M_node(__it._M_node) {}

    iterator
    _M_const_cast() const
    {
        return iterator(const_cast<typename iterator::_Base_ptr>(_M_node));
    }

    reference
    operator*() const
    {
        return *static_cast<_Link_type>(_M_node)->_M_valptr();
    }

    pointer
    operator->() const
    {
        return static_cast<_Link_type>(_M_node)->_M_valptr();
    }

    _Self&
    operator++()
    {
        _M_node = _Rb_tree_increment(_M_node);
        return *this;
    }

    _Self&
    operator++(int)
    {
        _Self __tmp = *this;
        _M_node = _Rb_tree_increment(_M_node);
        return __tmp;
    }

    _Self&
    operator--()
    {
        _M_node = _Rb_tree_decrement(_M_node);
        return *this;
    }

    _Self&
    operator--(int)
    {
        _Self __tmp = *this;
        _M_node = _Rb_tree_decrement(_M_node);
        return __tmp;
    }

    friend bool
    operator==(const _Self& __x, const _Self& __y)
    {
        return __x._M_node == __y._M_node;
    }

    friend bool
    operator!=(const _Self& __x, const _Self& __y)
    {
        return __x._M_node != __y._M_node;
    }

    _Base_ptr _M_node;
};

#endif // STL_TREE_H_
