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