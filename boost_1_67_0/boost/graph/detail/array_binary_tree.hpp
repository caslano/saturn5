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