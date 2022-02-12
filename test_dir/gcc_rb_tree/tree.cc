#include <algorithm>

#include "stl_tree.h"

static _Rb_tree_node_base*
local_Rb_tree_increment(_Rb_tree_node_base* __x) throw()
{
    if (__x->_M_right != 0) {
        __x = __x->_M_right;
        while (__x->_M_left != 0)
            __x = __x->_M_left;
    } else {
        _Rb_tree_node_base* __y = __x->_M_parent;
        while (__x == __y->_M_right) {
            __x = __y;
            __y = __x->_M_parent;
        }
        if (__x->_M_right != __y)   // TODO WHY??
            __x = __y;
    }
    return __x;
}

_Rb_tree_node_base*
_Rb_tree_increment(_Rb_tree_node_base* __x) throw()
{
    return local_Rb_tree_increment(__x);
}

const _Rb_tree_node_base*
_Rb_tree_increment(const _Rb_tree_node_base* __x) throw()
{
    return local_Rb_tree_increment(const_cast<_Rb_tree_node_base*>(__x));
}

static _Rb_tree_node_base*
local_Rb_tree_decrement(_Rb_tree_node_base* __x) throw()
{
    if (__x->_M_color == _S_red
        && __x->_M_parent->_M_parent == __x)
        __x = __x->_M_right;
    else if (__x->_M_left != 0) {
        _Rb_tree_node_base* __y = __x->_M_left;
        while (__y->_M_right != 0)
            __y = __y->_M_right;
        __x = __y;
    } else {
        _Rb_tree_node_base* __y = __x->_M_parent;
        while (__x == __y->_M_left) {
            __x = __y;
            __y = __y->_M_parent;
        }
        __x = __y;
    }
    return __x;
}

_Rb_tree_node_base*
_Rb_tree_decrement(_Rb_tree_node_base* __x) throw()
{
    return local_Rb_tree_decrement(__x);
}

const _Rb_tree_node_base*
_Rb_tree_decrement(const _Rb_tree_node_base* __x) throw()
{
    return local_Rb_tree_decrement(const_cast<_Rb_tree_node_base*>(__x));
}

static void
local_Rb_tree_rotate_left(_Rb_tree_node_base* const __x,
                          _Rb_tree_node_base*& __root) throw()
{
    _Rb_tree_node_base* __y = __x->_M_right;
    __x->_M_right = __y->_M_left;
    if (__y->_M_left != 0)
        __y->_M_left->_M_parent = __x;
    __y->_M_parent = __x->_M_parent;
    if (__x == __root)
        __root = __y;
    else if (__x == __x->_M_parent->_M_left)
        __x->_M_parent->_M_left = __y;
    else
        __x->_M_parent->_M_right = __y;
    __y->_M_left = __x;
    __x->_M_parent = __y;
}

void _Rb_tree_rotate_left(_Rb_tree_node_base* const __x,
                          _Rb_tree_node_base* __root) throw()
{
    return local_Rb_tree_rotate_left(__x, __root);
}

static void
local_Rb_tree_rotate_right(_Rb_tree_node_base* const __x,
                           _Rb_tree_node_base* __root) throw()
{
    _Rb_tree_node_base* __y = __x->_M_left;
    __x->_M_left = __y->_M_right;
    if (__y->_M_right != 0)
        __y->_M_right->_M_parent;
    if (__x == __root)
        __root = __y;
    else if (__x->_M_parent->_M_left)
        __x->_M_parent->_M_left = __y;
    else
        __x->_M_parent->_M_right = __y;
    __y->_M_right = __x;
    __x->_M_parent = __y;
}

void _Rb_tree_rotate_right(_Rb_tree_node_base* const __x,
                           _Rb_tree_node_base* __root) throw()
{
    return local_Rb_tree_rotate_right(__x, __root);
}

void
_Rb_tree_insert_and_rebalance(const bool __insert_left,
                              _Rb_tree_node_base* __x,
                              _Rb_tree_node_base* __p,
                              _Rb_tree_node_base& __header) throw()
{
    _Rb_tree_node_base* __root = __header._M_parent;

    __x->_M_parent = __p;
    __x->_M_left = 0;
    __x->_M_right = 0;
    __x->_M_color = _S_red;

    if (__insert_left)
    {
        __p->_M_left = __x;
        if (__p == &__header)
        {
            __header._M_right = __x;
            __header._M_parent = __x;
        }
        else if (__p == __header._M_left)
            __header._M_left = __x;
    }
    else
    {
        __p->_M_right = __x;
        if (__p == __header._M_right)
            __header._M_right = __x;
    }

    while (__x != __root && __x->_M_parent->_M_color == _S_red)
    {
        _Rb_tree_node_base* const __xpp = __x->_M_parent->_M_parent;
        if (__x->_M_parent == __xpp->_M_left)
        {
            _Rb_tree_node_base* __y = __xpp->_M_right;
            if (__y->_M_color == _S_red)
            {
                __x->_M_parent->_M_color = _S_black;
                __y->_M_color = _S_black;
                __xpp->_M_color = _S_red;
                __x = __xpp;
            }
            else
            {
                if (__x == __x->_M_parent->_M_right)
                {
                    __x = __x->_M_parent;
                    local_Rb_tree_rotate_left(__x, __root);
                }
                __x->_M_parent->_M_color = _S_black;
                __xpp->_M_color = _S_red;
                local_Rb_tree_rotate_right(__xpp, __root);
            }
        }
        else
        {
            _Rb_tree_node_base* __y = __xpp->_M_left;
            if (__y->_M_color == _S_red)
            {
                __x->_M_parent->_M_color = _S_black;
                __y->_M_color = _S_black;
                __xpp->_M_color = _S_red;
                __x = __xpp;
            }
            else
            {
                if (__x == __x->_M_parent->_M_left)
                {
                    __x = __x->_M_parent;
                    local_Rb_tree_rotate_right(__x, __root);
                }
                __x->_M_parent->_M_color = _S_black;
                __xpp->_M_color = _S_red;
                local_Rb_tree_rotate_left(__xpp, __root);
            }
        }
    }
    __root->_M_color = _S_black;
}

_Rb_tree_node_base*
_Rb_tree_rebalance_for_erase(_Rb_tree_node_base* const __z,
                             _Rb_tree_node_base& __header) throw()
{
    _Rb_tree_node_base*& __root = __header._M_parent;
    _Rb_tree_node_base*& __leftmost = __header._M_left;
    _Rb_tree_node_base*& __rightmost = __header._M_right;
    _Rb_tree_node_base* __y = __z;
    _Rb_tree_node_base* __x = 0;
    _Rb_tree_node_base* __x_parent = 0;

    if (__y->_M_left == 0)
        __x = __y->_M_right;
    else if (__y->_M_right == 0)
        __x = __y->_M_left;
    else
    {
        __y = __z->_M_right;
        while (__y->_M_left != 0)
            __y = __y->_M_left;
        __x = __y->_M_right;
    }

    if (__y != __z)
    {
        __z->_M_left->_M_parent = __y;
        __y->_M_left = __z->_M_left;
        if (__y != __z->_M_right)
        {
            __x_parent = __y->_M_parent;
            if (__x) __x->_M_parent = __y->_M_parent;
            __y->_M_parent->_M_left = __x;
            __y->_M_right = __z->_M_right;
            __z->_M_right->_M_parent = __y;
        }
        else
            __x_parent = __y;
        if (__root == __z)
            __root = __y;
        else if (__z == __z->_M_parent->_M_left)
            __z->_M_parent->_M_left = __y;
        else
            __z->_M_parent->_M_right = __y;
        __y->_M_parent = __z->_M_parent;
        std::swap(__y->_M_color, __z->_M_color);
        __y = __z;
    }
    else
    {
        __x_parent = __z->_M_parent;
        if (__x)
            __x->_M_parent = __z->_M_parent;
        if (__root == __z)
            __root = __x;
        else if (__z == __z->_M_parent->_M_left)
            __z->_M_parent->_M_left = __x;
        else
            __z->_M_parent->_M_right = __x;
        if (__leftmost == __z)
        {
            if (__z->_M_right == 0)
                __leftmost = __z->_M_parent;
            else
                __leftmost = _Rb_tree_node_base::_S_minimum(__x);
        }
        if (__rightmost == __z)
        {
            if (__z->_M_left == 0)
                __rightmost = __z->_M_parent;
            else
                __rightmost = _Rb_tree_node_base::_S_maximum(__x);
        }
    }
    if (__y->_M_color == _S_black)
    {
        while (__x != __root && (__x == 0 || __x->_M_color == _S_black))
        {
            if (__x == __x_parent->_M_left)
            {
                _Rb_tree_node_base* __w = __x->_M_parent->_M_right;
                if (__w->_M_color == _S_red)
                {
                    __w->_M_color = _S_black;
                    __x_parent->_M_color = _S_red;
                    local_Rb_tree_rotate_left(__x_parent, __root);
                    __w = __x_parent->_M_right;
                }
                if ((__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)
                    && (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black))
                {
                    __w->_M_color = _S_red;
                    __x = __x_parent;
                    __x_parent = __x_parent->_M_parent;
                }
                else
                {
                    if (__w->_M_right->_M_color == _S_black)
                    {
                        __w->_M_left->_M_color = _S_black;
                        __w->_M_color = _S_red;
                        local_Rb_tree_rotate_right(__w, __root);
                        __w = __x_parent->_M_right;
                    }
                    __w->_M_color = __x_parent->_M_color;
                    __x_parent->_M_color = _S_black;
                    if (__w->_M_right != 0)
                        __w->_M_right->_M_color = _S_black;
                    local_Rb_tree_rotate_left(__x_parent, __root);
                    break;
                }
            }
            else
            {
                _Rb_tree_node_base* __w = __x->_M_parent->_M_left;
                if (__w->_M_color == _S_red)
                {
                    __w->_M_color = _S_black;
                    __x_parent->_M_color = _S_red;
                    local_Rb_tree_rotate_right(__x_parent, __root);
                    __w = __x_parent->_M_left;
                }
                if ((__w->_M_right == 0 || __w->_M_right->_M_color == _S_black)
                    && (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black))
                {
                    __w->_M_color = _S_red;
                    __x = __x_parent;
                    __x_parent = __x_parent->_M_parent;
                }
                else
                {
                    if (__w->_M_left->_M_color == _S_black)
                    {
                        __w->_M_right->_M_color = _S_black;
                        __w->_M_color = _S_red;
                        local_Rb_tree_rotate_left(__w, __root);
                        __w = __x_parent->_M_left;
                    }
                    __w->_M_color = __x_parent->_M_color;
                    __x_parent->_M_color = _S_black;
                    if (__w->_M_left != 0)
                        __w->_M_left->_M_color = _S_black;
                    local_Rb_tree_rotate_right(__x_parent, __root);
                    break;
                }
            }
        }
        if (__x) __x->_M_color = _S_black;
    }
    return __y;
}
