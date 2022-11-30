// boost heap: heap merge algorithms
//
// Copyright (C) 2011 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_MERGE_HPP
#define BOOST_HEAP_MERGE_HPP

#include <algorithm>

#include <boost/concept/assert.hpp>
#include <boost/heap/heap_concepts.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_same.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif


namespace boost  {
namespace heap   {
namespace detail {

template <typename Heap1, typename Heap2>
struct heap_merge_emulate
{
    struct dummy_reserver
    {
        static void reserve (Heap1 & lhs, std::size_t required_size)
        {}
    };

    struct reserver
    {
        static void reserve (Heap1 & lhs, std::size_t required_size)
        {
            lhs.reserve(required_size);
        }
    };

    typedef typename boost::conditional<Heap1::has_reserve,
                                      reserver,
                                      dummy_reserver>::type space_reserver;

    static void merge(Heap1 & lhs, Heap2 & rhs)
    {
        if (Heap1::constant_time_size && Heap2::constant_time_size) {
            if (Heap1::has_reserve) {
                std::size_t required_size = lhs.size() + rhs.size();
                space_reserver::reserve(lhs, required_size);
            }
        }

        // FIXME: container adaptors could benefit from first appending all elements and then restoring the heap order
        // FIXME: optimize: if we have ordered iterators and we can efficiently insert keys with a below the lowest key in the heap
        //                  d-ary, b and fibonacci heaps fall into this category

        while (!rhs.empty()) {
            lhs.push(rhs.top());
            rhs.pop();
        }

        lhs.set_stability_count((std::max)(lhs.get_stability_count(),
                                           rhs.get_stability_count()));
        rhs.set_stability_count(0);
    }

};


template <typename Heap>
struct heap_merge_same_mergable
{
    static void merge(Heap & lhs, Heap & rhs)
    {
        lhs.merge(rhs);
    }
};


template <typename Heap>
struct heap_merge_same
{
    static const bool is_mergable = Heap::is_mergable;
    typedef typename boost::conditional<is_mergable,
                                      heap_merge_same_mergable<Heap>,
                                      heap_merge_emulate<Heap, Heap>
                                     >::type heap_merger;

    static void merge(Heap & lhs, Heap & rhs)
    {
        heap_merger::merge(lhs, rhs);
    }
};

} /* namespace detail */


/** merge rhs into lhs
 *
 *  \b Effect: lhs contains all elements that have been part of rhs, rhs is empty.
 *
 * */
template <typename Heap1,
          typename Heap2
         >
void heap_merge(Heap1 & lhs, Heap2 & rhs)
{
    BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap1>));
    BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap2>));

    // if this assertion is triggered, the value_compare types are incompatible
    BOOST_STATIC_ASSERT((boost::is_same<typename Heap1::value_compare, typename Heap2::value_compare>::value));

    const bool same_heaps = boost::is_same<Heap1, Heap2>::value;

    typedef typename boost::conditional<same_heaps,
                                      detail::heap_merge_same<Heap1>,
                                      detail::heap_merge_emulate<Heap1, Heap2>
                                     >::type heap_merger;

    heap_merger::merge(lhs, rhs);
}


} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_MERGE_HPP */

/* heap_merge.hpp
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
*/