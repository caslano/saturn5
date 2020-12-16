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
lXxZUNmWcqq/lbonGvK7AJOEGYvZ7GtDbJdyKh0TeWRHaTyEL6tKv56eY9tN7IOMLvybqN8NtkdSZrW7Ojp/nC72eCNcWUqAnUQnSewl2o8UR5mdwgnepdOLylSZ1TotrW89fmW6TTJQrrXnuzUSX8bKHlS+fO4mbjon+Mzxz6iXM+Odaajiv4uuv9WzK3n34HQReT+djvYzSHqpdQPJyepcXkwTzDTM87Wob/3pVTQ1b3THzNPzeg0bmFdROrHM34aQuJ+l0srSbSv2kdifEfsIvQ+ZKfNsVRpp/da6ztwo9l6if2ktie8iSR+V9k/J9WFiz9HuW0r69BJ9bo0JflKnqjT4g+g0FftQ7aa5hDGqjtQTcui+Ve+8INdr6Lr+bbE3c373zXSecf+BegYrfc9C+BFmP6Zn8vHTt7pK30pJS9p+Km33i13iS7fniRNkxIkjTXuJzH5uZ5oeqBmcpm/6yuB7zjRls8uhdppOr5qm6FZN0yHYw6ap0nem6UDsx0rT/lx3pCnuj5+mfdBxpClujp2mw7nuTNNC7MdK0wveC52mn5xkmk7/DdPU2vdzQ63gNK3Hy3ldlTS103NaQHquC0jPvcdJz3UB6bnrOOn5fkB6rjuB9NwekJ7rjpOeHwek51fHSc8fwqTnpyeZntN+0/T0vyfHp/oDek29J5/FvFqP9+cOlZ6SlDRpSyut+EAu0UGYkqZKtwf1fpxKZ3Z1FVlcYLqKmwHaTTflBpntJjBtxU1OUDjIbDch0zdF5YnRovM4dtOYi5F01v7Vdn6P6jR7Sq7F6HbmTWKfSp7nu1H1oz2egiLPRWzodUDnid4j9joldT/OtQ0rRYdvapWnHxJ7Lv3cNZXMCq8T99bY8LXrNvJsy4n7OxN87cVsaS+2oGUXql2XovQ3on+XT7/aSC/v/KD2opUf3+VatmNNwfG/D8lrkLxAvlJ5QfJacJ7MCZEnRwflSdtP4hS5xKnkU2td4dq6hvwGYxpg+mDe8Y0vvC/5dAKrb8oqJxgS711TDWR5uZXTi/OnOMp5V9FtovKo5TZD3CQniJs+anq9ypOWTmNdv2SJvaXaZ9W5/idvWHEFTRtHe24kurI3KulRxD314xlykkiPehk6LYYk+dMifJw3lDhPUXHJsxE/6tkc8cn9I3fcP9+wORI++Ty1apl/oZ7f59tUmb8a80wqeqdJXE4sLvOlX15hAXKVz1WZt+NypOjOVnGp3HI31fT+p4V6D+Vz/f46ylm5Xts5Va5lc81a01ag47pErk3X9ea13OwyzBrpFzl+vSltV52n1P2rurMcg0zlMfXNoDzLcJHHFLcTV+P9eWxK/qRiX2Ml3LeC0mut+xqXiP078x4jKtz7TblpqfvG7L5C+1s5R+s1Fr9HYF8gdo/rMcMd/vtAu+st/rO3W8jvf8e3O/r2t/vK4/TtZQbor8Fu9WEYdh+G9HEM+kD6MHSfhWH3Wehvq9Wi86rRAYmqP7UeXxi6DXCz6O21dQhLNBxrGKNF5xL66T1GqPWg2+X6laT/MM7Ea6DXt5bu9MmT/X6r9YDsrMtwsj/8Pvh9lzxzf3SwU1f/Tex3mP3xzdE/IPsDJ6rvvwdFpwf3go7ILHepRk/ydw105xEv8zFQ6uIFQlv+GS+mfRhLvpu/D2J+Vd9xOcdsQ3gSWn7g7L/jmzvEt/kVIerwZbpfTvKk1Dkrgr/nRL4yzPf6mpDf63addPtphvxGRdGvpvhBPcq7pMc8fwqonrWg8qfW177tT7so/T0o9n5GUL+a2mv7TbleR/QHaP0ORprKZy+IvUlUe/aI7+ouNJ+P6GmM8zxspqh39OJ9XOdk/u7GGOaIx5u6P8A=
*/