/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:50:35 by nnamor            #+#    #+#             */
/*   Updated: 2022/02/02 22:03:43 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_H_
#define RB_TREE_H_

#include <memory>
#include <cstddef>

#include "functional.hpp"
#include "utility.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{

template <
    class Key,
    class T,
    class Compare = less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
> class RBTree
{
public:
    typedef          Key                                            key_type;
    typedef          T                                              mapped_type;
    typedef          ft::pair<const Key, T>                         value_type;
    typedef          Compare                                        key_compare;
    typedef          Allocator                                      allocator_type;
    typedef          value_type&                                    reference;
    typedef          const value_type&                              const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;

    typedef          ft::NodeIterator<value_type>                   iterator;
    typedef          const ft::NodeIterator<value_type>             const_iterator;
    typedef          ft::reverse_iterator<iterator>                 reverse_iterator;
    typedef          ft::reverse_iterator<const_iterator>           const_reverse_iterator;

    typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
    typedef          size_t                                         size_type;

public:
    /// default constructor
    explicit RBTree(const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type()); //TODO
    /// range constructor
    template <class InputIterator>
        RBTree(InputIterator first, InputIterator last,
               const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type(),
               typename ft::enable_if<ft::is_iterator<InputIterator>::value, bool>::type = 0); //TODO
    /// copy constructor
    RBTree(const RBTree& t); //TODO

    ~RBTree(); //TODO

public:
    RBTree&        operator=(const RBTree& t); //TODO
    allocator_type get_allocator() const; //TODO

    /// element access
    mapped_type&       operator[](const key_type& k); //TODO
//  mapped_type&       at(const key_type& k);       // C++11
//  const mapped_type& at(const key_type& k) const; // C++11

    /// iterators
    iterator       begin(); //TODO
    const_iterator begin() const; //TODO
    iterator       end(); //TODO
    const_iterator end() const; //TODO

    reverse_iterator       rbegin(); //TODO
    const_reverse_iterator rbegin() const; //TODO
    reverse_iterator       rend(); //TODO
    const_reverse_iterator rend() const; //TODO

    /// capacity
    bool      empty() const; //TODO
    size_type size() const; //TODO
    size_type max_size() const; //TODO

    // modifiers
    void clear(); //TODO

    ft::pair<iterator, bool> insert(const value_type& value); //TODO
    iterator insert(iterator hint, const value_type& value); //map
    template <class InputIterator>
        void insert(InputIterator first, InputIterator last,
                    typename ft::enable_if<ft::is_iterator<InputIterator>::value, bool>::type = 0); //map

    void      erase(iterator pos); //TODO
    void      erase(iterator first, iterator last); //map
    size_type erase(const Key& key); //map

    void swap(RBTree& t); //TODO

    /// lookup
    size_type      count(const Key& key) const; // map
    iterator       find(const Key& key); //TODO
    const_iterator find(const Key& key) const; //TODO

    ft::pair<iterator, iterator>             equal_range(const Key& key); //map
    ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const; //map

    iterator       lower_bound(const Key& key); //TODO
    const_iterator lower_bound(const Key& key) const; //TODO
    iterator       upper_bound(const Key& key); //TODO
    const_iterator upper_bound(const Key& key) const; //TODO

    /// observers
    key_compare   key_comp() const; //TODO
//  value_compare value_comp() const; //TODO

    template <class K, class V, class Comp, class Alloc>
        friend bool operator==(const RBTree<K, V, Comp, Alloc>& lhs,
                               const RBTree<K, V, Comp, Alloc>& rhs); //TODO
    template <class K, class V, class Comp, class Alloc>
        friend bool operator!=(const RBTree<K, V, Comp, Alloc>& lhs,
                               const RBTree<K, V, Comp, Alloc>& rhs); //TODO
    template <class K, class V, class Comp, class Alloc>
        friend bool operator< (const RBTree<K, V, Comp, Alloc>& lhs,
                               const RBTree<K, V, Comp, Alloc>& rhs); //TODO
    template <class K, class V, class Comp, class Alloc>
        friend bool operator<=(const RBTree<K, V, Comp, Alloc>& lhs,
                               const RBTree<K, V, Comp, Alloc>& rhs); //TODO
    template <class K, class V, class Comp, class Alloc>
        friend bool operator> (const RBTree<K, V, Comp, Alloc>& lhs,
                               const RBTree<K, V, Comp, Alloc>& rhs); //TODO
    template <class K, class V, class Comp, class Alloc>
        friend bool operator>=(const RBTree<K, V, Comp, Alloc>& lhs,
                               const RBTree<K, V, Comp, Alloc>& rhs); //TODO

    template <class K, class V, class Comp, class Alloc>
        friend void swap(RBTree<K, V, Comp, Alloc>& lhs,
                         RBTree<K, V, Comp, Alloc>& rhs); //map

private:
    enum Color_ : uint8_t
    {
        RED,
        BLACK
    };

    struct Node_
    {
        Node_*     parent;
        Node_*     left;
        Node_*     right;
        value_type pair;
        Color_     color;
    };

private:
    void destroy_(); //TODO
    void init_();
    void newNode_(Node_* p, value_type& pr);

private:
    Node_*                root_;
    Node_*                sentinel_;
    pointer               begin_;
    size_type             size_;
    allocator_type        alloc_;
    std::allocator<Node_*> nodeAlloc_;
    key_compare           comp_;
};

/// RBTree
template <class K, class T, class C, class A>
RBTree<K, T, C, A>::RBTree(const key_compare& comp, const allocator_type& alloc)
    : root_(NULL),
    sentinel_(NULL),
    begin_(NULL),
    size_(0),
    alloc_(alloc),
    comp_(comp)
{
    init_();
}

template <class K, class T, class C, class A>
RBTree<K, T, C, A>::~RBTree()
{
    destroy_();
}

///private
template <class K, class T, class C, class A>
void RBTree<K, T, C, A>::destroy_()
{
}

template <class K, class T, class C, class A>
void RBTree<K, T, C, A>::init_()
{
    sentinel_ = newNode_(NULL, 
    root_ = newNode_();
    begin_
    size_
}

template <class K, class T, class C, class A>
void RBTree<K, T, C, A>::newNode_(Node_* p, value_type& pr)
{
    Node_* n = nodeAlloc_.allocate(1);
    n->parent = p;
    n->left = sentinel_;
    n->right = sentinel_;
    n->pair = pr;
    n->color = RED;
}

}

#endif /*RB_TREE_H_*/
