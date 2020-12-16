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
OIF4KyUK4jyAOIeyU2a6ZbxmYwXdpdSbO42dkWW9RK8KAa8Dt9mMzm1Jwqb9VGq5+HY7ySYYR/2Rbp1oxmY32jIhPZfYbZnFdjxz8czFsxDPQjyL8SzG04Wnq315zX+Nr7BnNzuv2l/GBl3iiPL/kOP909UBgtIbj6RfJQa0myfzoveJBdEGHUa5lYfPWMH/wL8WTsKZlghOucQfe6GzMl1wnKuY2EkShaw4YSw/jDDSl5TYL0nBNabgxwgvEllargCsSMMWO13EaLGtshHYBmVtw1aADXGadApZkUl+uMSIqxuh+xgztCWjDfBNScOC203BRjN40ghU6bZhxIXAhJqSMGPQCJxWm600nujk0caP2sqipILJ5PMEy5vGmE//xsuHXHRAk7kwvRj/GARDmhYylvMBxHKwkWPviDK/KUZusBiD5Dcx2ZirsCFf0dehPFy6lcxXPrESPniL2VXZnc/LMVH4ZuAftfRdsUk71qzY8hvYrrOx8jQ36diBuwknjy+aEN0AMvYuJ2fCcBM/miZGFyfB0rMH0pB2wbQzMs+cvykEJQNZnYva/w5FgJCGmnaGBkCWD/uMTSnpY5pSDC1WfM5VSH7FVOMsNy8cuOgQuuiWeQMB5nKP6uOcBNbkNY/OLzeT1ySVEmsQkOfm10WeuZlkK4ZT4qJhxPXKgc7uywkJdcFlXAlOEupdHhJOc45DE9Sx3zL0T3X9ApM1gpVpveCzsUXgYujZE9Ptvm3U9FWZYkgeIV+vPwyVDY/pPq/siYiZ6gusnBVV+HbO9ffyPU49+CD15ZPCMGkQK2my2JMyWSIV7VW9KVK9dOtj7KPQAFuJVrPm5ubZLQCheM3Lelx4akWP6vcDXZaNMF5YYqzoHFyTFGxIqq6v+KyoviUZnirXGrGaPlPzm7SR0Sb3kjP4lH9lsb9QoPMQcd/J/vNF6JEY5H4N1URknsW3aVlXO7rWtw1Pv1n9wUdsFls2Rn08mVGFm9blk2Ls41AXfz8B7uEYcJcCnDTC+pc6Ot6aBbxiw8+Z4sJsdUu3AH1LE6ITM2MLXpSRZrpBx6X2bd6jqSJ6+3xJwP8gMeMzfL8X1ajexdUgUtXvFfgl9rWe7UtAdiuHkHf3g8GbcBx3lGLCJfqA6vTdIAG51K0REMVaOkp52XSIBZ19Ab2QkpZhiikyOzdy4/RS9aZLBPWb9hXbDSCxwEVKcQGORsMoJrJB+Ogs8N0s8zKL0HBsHi1M59/bqbc4Bk1U7Pb9UC/xelmtP4m03/lylDZ+YKJmhYjxNN8oHd0gFbsQBQ+UBTeiepzoYj1RtUxkk4l4C07+lXI7BFsjFb18Lj1Tjcz09x1apuOsEetfGg2w8BrAEFkL0xMrmnbOqvj7i4JpQacuNMTzB73+1IvAMdCF1O9+NHmp+t4WATNywyRmHL9CmD2tY/Df16A0tIM3y8dQifyABeOzleIcPKxwVCeoNgkbfRNAWYGuSoogv3RYBGS+yXZk/t6MKx0OvxgKlMhcs5qDUhl3MoqzjiOiy+mYIB1XP8Vlr964oIvfQFXxG0vVAx+J2tF25JCSSQEI7JWd966xBNJCJZOEdOQr0nttMSHwU/SaY/uxeg0MjCcucyBj0fQpEZwuFtAWjZtiwMsRghclJVcBKBhvWzdjn5dfvmqOMUNoP/0TMv1z7aRnerkD7D/2/jFuhxz6UzOSj375AWmH5J2fRMzJyvWWloya+r8Yef2ghq63QAwwkIQQyFZs6NkuxL3OQbRichpt1Q680Zc9xM+Gg8SUeVO8qvEw8zHkDs2bQjon2gn1qKPWSPaW7y+Psg7/TWj7h7dx22t3TkaK1PURTqzsRN4ekSKcw9g=
*/