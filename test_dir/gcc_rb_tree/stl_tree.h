#ifndef STL_TREE_H_
#define STL_TREE_H_

#include <cstddef>

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
    _S_blakc = true
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
        _M_header._M_parent->_M_parent = &_M_header; //TODO WHY?? - for increment operation
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



#endif // STL_TREE_H_
