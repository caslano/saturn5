// boost heap: heap node helper classes
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_DETAIL_HEAP_COMPARISON_HPP
#define BOOST_HEAP_DETAIL_HEAP_COMPARISON_HPP

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/concept/assert.hpp>
#include <boost/heap/heap_concepts.hpp>
#include <boost/type_traits/conditional.hpp>

#ifdef BOOST_HEAP_SANITYCHECKS
#define BOOST_HEAP_ASSERT BOOST_ASSERT
#else
#define BOOST_HEAP_ASSERT(expression)
#endif

namespace boost  {
namespace heap   {
namespace detail {

template <typename Heap1, typename Heap2>
bool value_equality(Heap1 const & lhs, Heap2 const & rhs,
                    typename Heap1::value_type lval, typename Heap2::value_type rval)
{
    typename Heap1::value_compare const & cmp = lhs.value_comp();
    bool ret = !(cmp(lval, rval)) && !(cmp(rval, lval));

    // if this assertion is triggered, the value_compare objects of lhs and rhs return different values
    BOOST_ASSERT((ret == (!(rhs.value_comp()(lval, rval)) && !(rhs.value_comp()(rval, lval)))));

    return ret;
}

template <typename Heap1, typename Heap2>
bool value_compare(Heap1 const & lhs, Heap2 const & rhs,
                    typename Heap1::value_type lval, typename Heap2::value_type rval)
{
    typename Heap1::value_compare const & cmp = lhs.value_comp();
    bool ret = cmp(lval, rval);

    // if this assertion is triggered, the value_compare objects of lhs and rhs return different values
    BOOST_ASSERT((ret == rhs.value_comp()(lval, rval)));
    return ret;
}

struct heap_equivalence_copy
{
    template <typename Heap1, typename Heap2>
    bool operator()(Heap1 const & lhs, Heap2 const & rhs)
    {
        BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap1>));
        BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap2>));

        // if this assertion is triggered, the value_compare types are incompatible
        BOOST_STATIC_ASSERT((boost::is_same<typename Heap1::value_compare, typename Heap2::value_compare>::value));

        if (Heap1::constant_time_size && Heap2::constant_time_size)
            if (lhs.size() != rhs.size())
                return false;

        if (lhs.empty() && rhs.empty())
            return true;

        Heap1 lhs_copy(lhs);
        Heap2 rhs_copy(rhs);

        while (true) {
            if (!value_equality(lhs_copy, rhs_copy, lhs_copy.top(), rhs_copy.top()))
                return false;

            lhs_copy.pop();
            rhs_copy.pop();

            if (lhs_copy.empty() && rhs_copy.empty())
                return true;

            if (lhs_copy.empty())
                return false;

            if (rhs_copy.empty())
                return false;
        }
    }
};


struct heap_equivalence_iteration
{
    template <typename Heap1, typename Heap2>
    bool operator()(Heap1 const & lhs, Heap2 const & rhs)
    {
        BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap1>));
        BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap2>));

        // if this assertion is triggered, the value_compare types are incompatible
        BOOST_STATIC_ASSERT((boost::is_same<typename Heap1::value_compare, typename Heap2::value_compare>::value));

        if (Heap1::constant_time_size && Heap2::constant_time_size)
            if (lhs.size() != rhs.size())
                return false;

        if (lhs.empty() && rhs.empty())
            return true;

        typename Heap1::ordered_iterator it1 = lhs.ordered_begin();
        typename Heap1::ordered_iterator it1_end = lhs.ordered_end();
        typename Heap1::ordered_iterator it2 = rhs.ordered_begin();
        typename Heap1::ordered_iterator it2_end = rhs.ordered_end();
        while (true) {
            if (!value_equality(lhs, rhs, *it1, *it2))
                return false;

            ++it1;
            ++it2;

            if (it1 == it1_end && it2 == it2_end)
                return true;

            if (it1 == it1_end || it2 == it2_end)
                return false;
        }
    }
};


template <typename Heap1,
          typename Heap2
         >
bool heap_equality(Heap1 const & lhs, Heap2 const & rhs)
{
    const bool use_ordered_iterators = Heap1::has_ordered_iterators && Heap2::has_ordered_iterators;

    typedef typename boost::conditional<use_ordered_iterators,
                                      heap_equivalence_iteration,
                                      heap_equivalence_copy
                                     >::type equivalence_check;

    equivalence_check eq_check;
    return eq_check(lhs, rhs);
}


struct heap_compare_iteration
{
    template <typename Heap1,
              typename Heap2
             >
    bool operator()(Heap1 const & lhs, Heap2 const & rhs)
    {
        typename Heap1::size_type left_size = lhs.size();
        typename Heap2::size_type right_size = rhs.size();
        if (left_size < right_size)
            return true;

        if (left_size > right_size)
            return false;

        typename Heap1::ordered_iterator it1 = lhs.ordered_begin();
        typename Heap1::ordered_iterator it1_end = lhs.ordered_end();
        typename Heap1::ordered_iterator it2 = rhs.ordered_begin();
        typename Heap1::ordered_iterator it2_end = rhs.ordered_end();
        while (true) {
            if (value_compare(lhs, rhs, *it1, *it2))
                return true;

            if (value_compare(lhs, rhs, *it2, *it1))
                return false;

            ++it1;
            ++it2;

            if (it1 == it1_end && it2 == it2_end)
                return true;

            if (it1 == it1_end || it2 == it2_end)
                return false;
        }
    }
};

struct heap_compare_copy
{
    template <typename Heap1,
              typename Heap2
             >
    bool operator()(Heap1 const & lhs, Heap2 const & rhs)
    {
        typename Heap1::size_type left_size = lhs.size();
        typename Heap2::size_type right_size = rhs.size();
        if (left_size < right_size)
            return true;

        if (left_size > right_size)
            return false;

        Heap1 lhs_copy(lhs);
        Heap2 rhs_copy(rhs);

        while (true) {
            if (value_compare(lhs_copy, rhs_copy, lhs_copy.top(), rhs_copy.top()))
                return true;

            if (value_compare(lhs_copy, rhs_copy, rhs_copy.top(), lhs_copy.top()))
                return false;

            lhs_copy.pop();
            rhs_copy.pop();

            if (lhs_copy.empty() && rhs_copy.empty())
                return false;
        }
    }
};

template <typename Heap1,
          typename Heap2
         >
bool heap_compare(Heap1 const & lhs, Heap2 const & rhs)
{
    const bool use_ordered_iterators = Heap1::has_ordered_iterators && Heap2::has_ordered_iterators;

    typedef typename boost::conditional<use_ordered_iterators,
                                      heap_compare_iteration,
                                      heap_compare_copy
                                     >::type compare_check;

    compare_check check_object;
    return check_object(lhs, rhs);
}


} /* namespace detail */
} /* namespace heap */
} /* namespace boost */


#undef BOOST_HEAP_ASSERT

#endif // BOOST_HEAP_DETAIL_HEAP_COMPARISON_HPP

/* heap_comparison.hpp
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
*/