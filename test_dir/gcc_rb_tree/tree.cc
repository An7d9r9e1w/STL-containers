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
        while (__x == __y->_M_left) {
            __x = __y;
            __y = __x->_M_parent;
        }
        if (__x->_M_right != __y)   // TODO WHY??
            __x = __y;
    }
    return __x;
}

_Rb_tree_node_base*
_Rb_tree_increment(_Rb_tree_node_base* __x)
{
    return local_Rb_tree_increment(__x);
}

const _Rb_tree_node_base*
_Rb_tree_increment(const _Rb_tree_node_base* __x)
{
    return local_Rb_tree_increment(const_cast<_Rb_tree_node_base*>(__x));
}
