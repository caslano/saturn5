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