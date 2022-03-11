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