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