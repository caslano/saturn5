//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_ARRAY_BINARY_TREE_HPP
#define BOOST_ARRAY_BINARY_TREE_HPP

#include <iterator>
#include <functional>
#include <boost/config.hpp>

namespace boost
{

/*
 * Note: array_binary_tree is a completey balanced binary tree.
 */
#if !defined BOOST_NO_STD_ITERATOR_TRAITS
template < class RandomAccessIterator, class ID >
#else
template < class RandomAccessIterator, class ValueType, class ID >
#endif
class array_binary_tree_node
{
public:
    typedef array_binary_tree_node ArrayBinaryTreeNode;
    typedef RandomAccessIterator rep_iterator;
#if !defined BOOST_NO_STD_ITERATOR_TRAITS
    typedef
        typename std::iterator_traits< RandomAccessIterator >::difference_type
            difference_type;
    typedef typename std::iterator_traits< RandomAccessIterator >::value_type
        value_type;
#else
    typedef int difference_type;
    typedef ValueType value_type;
#endif
    typedef difference_type size_type;

    struct children_type
    {
        struct iterator
        { // replace with iterator_adaptor implementation -JGS
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef ArrayBinaryTreeNode value_type;
            typedef size_type difference_type;
            typedef array_binary_tree_node* pointer;
            typedef ArrayBinaryTreeNode& reference;

            inline iterator() : i(0), n(0) {}
            inline iterator(const iterator& x)
            : r(x.r), i(x.i), n(x.n), id(x.id)
            {
            }
            inline iterator& operator=(const iterator& x)
            {
                r = x.r;
                i = x.i;
                n = x.n;
                /*egcs generate a warning*/
                id = x.id;
                return *this;
            }
            inline iterator(
                rep_iterator rr, size_type ii, size_type nn, const ID& _id)
            : r(rr), i(ii), n(nn), id(_id)
            {
            }
            inline array_binary_tree_node operator*()
            {
                return ArrayBinaryTreeNode(r, i, n, id);
            }
            inline iterator& operator++()
            {
                ++i;
                return *this;
            }
            inline iterator operator++(int)
            {
                iterator t = *this;
                ++(*this);
                return t;
            }
            inline iterator& operator--()
            {
                --i;
                return *this;
            }
            inline iterator operator--(int)
            {
                iterator t = *this;
                --(*this);
                return t;
            }
            inline bool operator==(const iterator& x) const { return i == x.i; }
            inline bool operator!=(const iterator& x) const
            {
                return !(*this == x);
            }
            rep_iterator r;
            size_type i;
            size_type n;
            ID id;
        };
        inline children_type() : i(0), n(0) {}
        inline children_type(const children_type& x)
        : r(x.r), i(x.i), n(x.n), id(x.id)
        {
        }
        inline children_type& operator=(const children_type& x)
        {
            r = x.r;
            i = x.i;
            n = x.n;
            /*egcs generate a warning*/
            id = x.id;
            return *this;
        }
        inline children_type(
            rep_iterator rr, size_type ii, size_type nn, const ID& _id)
        : r(rr), i(ii), n(nn), id(_id)
        {
        }
        inline iterator begin() { return iterator(r, 2 * i + 1, n, id); }
        inline iterator end() { return iterator(r, 2 * i + 1 + size(), n, id); }
        inline size_type size() const
        {
            size_type c = 2 * i + 1;
            size_type s;
            if (c + 1 < n)
                s = 2;
            else if (c < n)
                s = 1;
            else
                s = 0;
            return s;
        }
        rep_iterator r;
        size_type i;
        size_type n;
        ID id;
    };
    inline array_binary_tree_node() : i(0), n(0) {}
    inline array_binary_tree_node(const array_binary_tree_node& x)
    : r(x.r), i(x.i), n(x.n), id(x.id)
    {
    }
    inline ArrayBinaryTreeNode& operator=(const ArrayBinaryTreeNode& x)
    {
        r = x.r;
        i = x.i;
        n = x.n;
        /*egcs generate a warning*/
        id = x.id;
        return *this;
    }
    inline array_binary_tree_node(
        rep_iterator start, rep_iterator end, rep_iterator pos, const ID& _id)
    : r(start), i(pos - start), n(end - start), id(_id)
    {
    }
    inline array_binary_tree_node(
        rep_iterator rr, size_type ii, size_type nn, const ID& _id)
    : r(rr), i(ii), n(nn), id(_id)
    {
    }
    inline value_type& value() { return *(r + i); }
    inline const value_type& value() const { return *(r + i); }
    inline ArrayBinaryTreeNode parent() const
    {
        return ArrayBinaryTreeNode(r, (i - 1) / 2, n, id);
    }
    inline bool has_parent() const { return i != 0; }
    inline children_type children() { return children_type(r, i, n, id); }
    /*
    inline void swap(array_binary_tree_node x) {
      value_type tmp = x.value();
      x.value() = value();
      value() = tmp;
      i = x.i;
    }
    */
    template < class ExternalData >
    inline void swap(ArrayBinaryTreeNode x, ExternalData& edata)
    {
        using boost::get;

        value_type tmp = x.value();

        /*swap external data*/
        edata[get(id, tmp)] = i;
        edata[get(id, value())] = x.i;

        x.value() = value();
        value() = tmp;
        i = x.i;
    }
    inline const children_type children() const
    {
        return children_type(r, i, n);
    }
    inline size_type index() const { return i; }
    rep_iterator r;
    size_type i;
    size_type n;
    ID id;
};

template < class RandomAccessContainer,
    class Compare = std::less< typename RandomAccessContainer::value_type > >
struct compare_array_node
{
    typedef typename RandomAccessContainer::value_type value_type;
    compare_array_node(const Compare& x) : comp(x) {}
    compare_array_node(const compare_array_node& x) : comp(x.comp) {}

    template < class node_type >
    inline bool operator()(const node_type& x, const node_type& y)
    {
        return comp(x.value(), y.value());
    }

    template < class node_type >
    inline bool operator()(const node_type& x, const node_type& y) const
    {
        return comp(x.value(), y.value());
    }
    Compare comp;
};

} // namespace boost

#endif /* BOOST_ARRAY_BINARY_TREE_HPP */

/* array_binary_tree.hpp
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
*/