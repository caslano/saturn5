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
#ifndef BOOST_MUTABLE_QUEUE_HPP
#define BOOST_MUTABLE_QUEUE_HPP

#include <vector>
#include <algorithm>
#include <functional>
#include <boost/property_map/property_map.hpp>
#include <boost/pending/mutable_heap.hpp>
#include <boost/pending/is_heap.hpp>
#include <boost/graph/detail/array_binary_tree.hpp>
#include <iterator>

namespace boost
{

// The mutable queue whose elements are indexed
//
// This adaptor provides a special kind of priority queue that has
// and update operation. This allows the ordering of the items to
// change. After the ordering criteria for item x changes, one must
// call the Q.update(x)
//
// In order to efficiently find x in the queue, a functor must be
// provided to map value_type to a unique ID, which the
// mutable_queue will then use to map to the location of the
// item. The ID's generated must be between 0 and N, where N is the
// value passed to the constructor of mutable_queue

template < class IndexedType,
    class RandomAccessContainer = std::vector< IndexedType >,
    class Comp = std::less< typename RandomAccessContainer::value_type >,
    class ID = identity_property_map >
class mutable_queue
{
public:
    typedef IndexedType value_type;
    typedef typename RandomAccessContainer::size_type size_type;

protected:
    typedef typename RandomAccessContainer::iterator iterator;
#if !defined BOOST_NO_STD_ITERATOR_TRAITS
    typedef array_binary_tree_node< iterator, ID > Node;
#else
    typedef array_binary_tree_node< iterator, value_type, ID > Node;
#endif
    typedef compare_array_node< RandomAccessContainer, Comp > Compare;
    typedef std::vector< size_type > IndexArray;

public:
    typedef Compare value_compare;
    typedef ID id_generator;

    mutable_queue(size_type n, const Comp& x, const ID& _id)
    : index_array(n), comp(x), id(_id)
    {
        c.reserve(n);
    }
    template < class ForwardIterator >
    mutable_queue(ForwardIterator first, ForwardIterator last, const Comp& x,
        const ID& _id)
    : index_array(std::distance(first, last)), comp(x), id(_id)
    {
        while (first != last)
        {
            push(*first);
            ++first;
        }
    }

    bool empty() const { return c.empty(); }

    void pop()
    {
        value_type tmp = c.back();
        c.back() = c.front();
        c.front() = tmp;

        size_type id_f = get(id, c.back());
        size_type id_b = get(id, tmp);
        size_type i = index_array[id_b];
        index_array[id_b] = index_array[id_f];
        index_array[id_f] = i;

        c.pop_back();
        Node node(c.begin(), c.end(), c.begin(), id);
        down_heap(node, comp, index_array);
    }
    void push(const IndexedType& x)
    {
        c.push_back(x);
        /*set index-array*/
        index_array[get(id, x)] = c.size() - 1;
        Node node(c.begin(), c.end(), c.end() - 1, id);
        up_heap(node, comp, index_array);
    }

    void update(const IndexedType& x)
    {
        size_type current_pos = index_array[get(id, x)];
        c[current_pos] = x;

        Node node(c.begin(), c.end(), c.begin() + current_pos, id);
        update_heap(node, comp, index_array);
    }

    value_type& front() { return c.front(); }
    value_type& top() { return c.front(); }

    const value_type& front() const { return c.front(); }
    const value_type& top() const { return c.front(); }

    size_type size() const { return c.size(); }

    void clear() { c.clear(); }

#if 0
        // dwa 2003/7/11 - I don't know what compiler is supposed to
        // be able to compile this, but is_heap is not standard!!
    bool test() {
      return std::is_heap(c.begin(), c.end(), Comp());
    }
#endif

protected:
    IndexArray index_array;
    Compare comp;
    RandomAccessContainer c;
    ID id;
};

}

#endif // BOOST_MUTABLE_QUEUE_HPP

/* mutable_queue.hpp
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
*/