//
//=======================================================================
// Copyright 2009 Trustees of Indiana University
// Authors: Jeremiah J. Willcock, Andrew Lumsdaine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_D_ARY_HEAP_HPP
#define BOOST_D_ARY_HEAP_HPP

#include <vector>
#include <cstddef>
#include <algorithm>
#include <utility>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/shared_array.hpp>
#include <boost/property_map/property_map.hpp>

// WARNING: it is not safe to copy a d_ary_heap_indirect and then modify one of
// the copies.  The class is required to be copyable so it can be passed around
// (without move support from C++11), but it deep-copies the heap contents yet
// shallow-copies the index_in_heap_map.

namespace boost
{

// Swap two elements in a property map without assuming they model
// LvaluePropertyMap -- currently not used
template < typename PropMap >
inline void property_map_swap(PropMap prop_map,
    const typename boost::property_traits< PropMap >::key_type& ka,
    const typename boost::property_traits< PropMap >::key_type& kb)
{
    typename boost::property_traits< PropMap >::value_type va
        = get(prop_map, ka);
    put(prop_map, ka, get(prop_map, kb));
    put(prop_map, kb, va);
}

namespace detail
{
    template < typename Value > class fixed_max_size_vector
    {
        boost::shared_array< Value > m_data;
        std::size_t m_size;

    public:
        typedef std::size_t size_type;
        fixed_max_size_vector(std::size_t max_size)
        : m_data(new Value[max_size]), m_size(0)
        {
        }
        std::size_t size() const { return m_size; }
        bool empty() const { return m_size == 0; }
        Value& operator[](std::size_t i) { return m_data[i]; }
        const Value& operator[](std::size_t i) const { return m_data[i]; }
        void push_back(Value v) { m_data[m_size++] = v; }
        void pop_back() { --m_size; }
        Value& back() { return m_data[m_size - 1]; }
        const Value& back() const { return m_data[m_size - 1]; }
    };
}

// D-ary heap using an indirect compare operator (use identity_property_map
// as DistanceMap to get a direct compare operator).  This heap appears to be
// commonly used for Dijkstra's algorithm for its good practical performance
// on some platforms; asymptotically, it has an O(lg N) decrease-key
// operation while that can be done in constant time on a relaxed heap.  The
// implementation is mostly based on the binary heap page on Wikipedia and
// online sources that state that the operations are the same for d-ary
// heaps.  This code is not based on the old Boost d-ary heap code.
//
// - d_ary_heap_indirect is a model of UpdatableQueue as is needed for
//   dijkstra_shortest_paths.
//
// - Value must model Assignable.
// - Arity must be at least 2 (optimal value appears to be 4, both in my and
//   third-party experiments).
// - IndexInHeapMap must be a ReadWritePropertyMap from Value to
//   Container::size_type (to store the index of each stored value within the
//   heap for decrease-key aka update).
// - DistanceMap must be a ReadablePropertyMap from Value to something
//   (typedef'ed as distance_type).
// - Compare must be a BinaryPredicate used as a less-than operator on
//   distance_type.
// - Container must be a random-access, contiguous container (in practice,
//   the operations used probably require that it is std::vector<Value>).
//
template < typename Value, std::size_t Arity, typename IndexInHeapPropertyMap,
    typename DistanceMap, typename Compare = std::less< Value >,
    typename Container = std::vector< Value > >
class d_ary_heap_indirect
{
    BOOST_STATIC_ASSERT(Arity >= 2);

public:
    typedef typename Container::size_type size_type;
    typedef Value value_type;
    typedef typename boost::property_traits< DistanceMap >::value_type key_type;
    typedef DistanceMap key_map;

    d_ary_heap_indirect(DistanceMap distance,
        IndexInHeapPropertyMap index_in_heap,
        const Compare& compare = Compare(), const Container& data = Container())
    : compare(compare)
    , data(data)
    , distance(distance)
    , index_in_heap(index_in_heap)
    {
    }
    /* Implicit copy constructor */
    /* Implicit assignment operator */

    size_type size() const { return data.size(); }

    bool empty() const { return data.empty(); }

    void push(const Value& v)
    {
        size_type index = data.size();
        data.push_back(v);
        put(index_in_heap, v, index);
        preserve_heap_property_up(index);
        verify_heap();
    }

    Value& top()
    {
        BOOST_ASSERT(!this->empty());
        return data[0];
    }

    const Value& top() const
    {
        BOOST_ASSERT(!this->empty());
        return data[0];
    }

    void pop()
    {
        BOOST_ASSERT(!this->empty());
        put(index_in_heap, data[0], (size_type)(-1));
        if (data.size() != 1)
        {
            data[0] = data.back();
            put(index_in_heap, data[0], (size_type)(0));
            data.pop_back();
            preserve_heap_property_down();
            verify_heap();
        }
        else
        {
            data.pop_back();
        }
    }

    // This function assumes the key has been updated (using an external write
    // to the distance map or such)
    // See
    // http://coding.derkeiler.com/Archive/General/comp.theory/2007-05/msg00043.html
    void update(const Value& v)
    { /* decrease-key */
        size_type index = get(index_in_heap, v);
        preserve_heap_property_up(index);
        verify_heap();
    }

    bool contains(const Value& v) const
    {
        size_type index = get(index_in_heap, v);
        return (index != (size_type)(-1));
    }

    void push_or_update(const Value& v)
    { /* insert if not present, else update */
        size_type index = get(index_in_heap, v);
        if (index == (size_type)(-1))
        {
            index = data.size();
            data.push_back(v);
            put(index_in_heap, v, index);
        }
        preserve_heap_property_up(index);
        verify_heap();
    }

    DistanceMap keys() const { return distance; }

private:
    Compare compare;
    Container data;
    DistanceMap distance;
    IndexInHeapPropertyMap index_in_heap;

    // The distances being compared using compare and that are stored in the
    // distance map
    typedef typename boost::property_traits< DistanceMap >::value_type
        distance_type;

    // Get the parent of a given node in the heap
    static size_type parent(size_type index) { return (index - 1) / Arity; }

    // Get the child_idx'th child of a given node; 0 <= child_idx < Arity
    static size_type child(size_type index, std::size_t child_idx)
    {
        return index * Arity + child_idx + 1;
    }

    // Swap two elements in the heap by index, updating index_in_heap
    void swap_heap_elements(size_type index_a, size_type index_b)
    {
        using std::swap;
        Value value_a = data[index_a];
        Value value_b = data[index_b];
        data[index_a] = value_b;
        data[index_b] = value_a;
        put(index_in_heap, value_a, index_b);
        put(index_in_heap, value_b, index_a);
    }

    // Emulate the indirect_cmp that is now folded into this heap class
    bool compare_indirect(const Value& a, const Value& b) const
    {
        return compare(get(distance, a), get(distance, b));
    }

    // Verify that the array forms a heap; commented out by default
    void verify_heap() const
    {
        // This is a very expensive test so it should be disabled even when
        // NDEBUG is not defined
#if 0
      for (size_t i = 1; i < data.size(); ++i) {
        if (compare_indirect(data[i], data[parent(i)])) {
          BOOST_ASSERT (!"Element is smaller than its parent");
        }
      }
#endif
    }

    // Starting at a node, move up the tree swapping elements to preserve the
    // heap property
    void preserve_heap_property_up(size_type index)
    {
        size_type orig_index = index;
        size_type num_levels_moved = 0;
        // The first loop just saves swaps that need to be done in order to
        // avoid aliasing issues in its search; there is a second loop that does
        // the necessary swap operations
        if (index == 0)
            return; // Do nothing on root
        Value currently_being_moved = data[index];
        distance_type currently_being_moved_dist
            = get(distance, currently_being_moved);
        for (;;)
        {
            if (index == 0)
                break; // Stop at root
            size_type parent_index = parent(index);
            Value parent_value = data[parent_index];
            if (compare(
                    currently_being_moved_dist, get(distance, parent_value)))
            {
                ++num_levels_moved;
                index = parent_index;
                continue;
            }
            else
            {
                break; // Heap property satisfied
            }
        }
        // Actually do the moves -- move num_levels_moved elements down in the
        // tree, then put currently_being_moved at the top
        index = orig_index;
        for (size_type i = 0; i < num_levels_moved; ++i)
        {
            size_type parent_index = parent(index);
            Value parent_value = data[parent_index];
            put(index_in_heap, parent_value, index);
            data[index] = parent_value;
            index = parent_index;
        }
        data[index] = currently_being_moved;
        put(index_in_heap, currently_being_moved, index);
        verify_heap();
    }

    // From the root, swap elements (each one with its smallest child) if there
    // are any parent-child pairs that violate the heap property
    void preserve_heap_property_down()
    {
        if (data.empty())
            return;
        size_type index = 0;
        Value currently_being_moved = data[0];
        distance_type currently_being_moved_dist
            = get(distance, currently_being_moved);
        size_type heap_size = data.size();
        Value* data_ptr = &data[0];
        for (;;)
        {
            size_type first_child_index = child(index, 0);
            if (first_child_index >= heap_size)
                break; /* No children */
            Value* child_base_ptr = data_ptr + first_child_index;
            size_type smallest_child_index = 0;
            distance_type smallest_child_dist
                = get(distance, child_base_ptr[smallest_child_index]);
            if (first_child_index + Arity <= heap_size)
            {
                // Special case for a statically known loop count (common case)
                for (size_t i = 1; i < Arity; ++i)
                {
                    Value i_value = child_base_ptr[i];
                    distance_type i_dist = get(distance, i_value);
                    if (compare(i_dist, smallest_child_dist))
                    {
                        smallest_child_index = i;
                        smallest_child_dist = i_dist;
                    }
                }
            }
            else
            {
                for (size_t i = 1; i < heap_size - first_child_index; ++i)
                {
                    distance_type i_dist = get(distance, child_base_ptr[i]);
                    if (compare(i_dist, smallest_child_dist))
                    {
                        smallest_child_index = i;
                        smallest_child_dist = i_dist;
                    }
                }
            }
            if (compare(smallest_child_dist, currently_being_moved_dist))
            {
                swap_heap_elements(
                    smallest_child_index + first_child_index, index);
                index = smallest_child_index + first_child_index;
                continue;
            }
            else
            {
                break; // Heap property satisfied
            }
        }
        verify_heap();
    }
};

} // namespace boost

#endif // BOOST_D_ARY_HEAP_HPP

/* d_ary_heap.hpp
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
*/