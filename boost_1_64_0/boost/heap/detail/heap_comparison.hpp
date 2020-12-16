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
dtNDQd2gFXrgpJ+wOkVQrr6CefrB+x/ruJLSEUPjo3z/y7PR9nx0BSqMZZ+gnzWO5yLms1vwSGM5hLbQo9XRjCZBurl/moLQDPC97GRTl4sTcnfRw1IzDrfciKcK3JRwLTXHFz8QOXo4DEdzJ6HWexd5a9AQtz0uDy/PRj5ECzqmuq1kk0e0NuFsdyWpGrwYtKY41d31Yv6kKia3UmpRQCDbrKez0odbT4EF8At8KCpc01c5EjzPuDq5hLcYv1QP/lxbunV4CwUJhUzCZYIErIw/I30lm1uX8lADgSUv6+siD2sXOqXjupZI6K2ad0lxHuZAJOIqRMDb601UuXk9BBcR8STNTrHViBXXkWJdUnNKvOxUcpkSzYlFIZ0T7GEl7+Pl50jKHnlJz+p7lBUvA2FVJkLBV3w0WAvPeFEPfwfhJXnf1D2JkZCjQn3jTu2YItk7n8+s8SzFP3W9aK8r1KcA4eQyBFexhTXuxkixoHRnclJs19qRdJZIuouSXiKTWgRyjJaOiPXNYJnDmdVCk8Zy7FQACzZ4VbHilA/0bCNMY1K6GEldw80dbRaMoHgy1U244XAYYKsARq+frsUrRdmxSryWu1Qy7TaSmqpNT+sSPXgfpunewdG650N90VReLN2D4cYtzPDuXYP8V34a53P9fyp6POwR9gN3sVypwV8KM3q2nWcffQEMvOQ5LHXnZjk0SMXU4Xz1aSxncO3D1e+oWL2e+cWP+ttzdrRmSFvqL8M1qcpLwXKj5s/LWMiVcSfkW0554VRz6vNys2oAvLhv4gzkjeIeSOSKZyhoPm6bmYbcFJUM+jEgPg3XKglgLA1Wz5bQhRo0CKAi0Dzva5D+eyIf93fSIZnXla0NMxz9beeRgy01rYG62q0h1Y6HfvRgcVXi8RT19k36AP5ArMl9pbouEDGIR5zXzIublWpDIKa18LJWI/yyJ/TwmxGOAJSlQlu4LbPwMd5mMNLIl4lwHTDarjsVr3AhYosQ4hatRpqG9uRIduOiszsSWcwdxNkd4eoIQwwcIrzuIXY/lWG7uo6q3XmoPumjTc/ntddaaDk2r2XxxUrToNPZY1qpv+VAgfJKcL6jNGuX8rLSjLu6c7/Ya2o3baMDFTQqp3M0dOSA7hOFnyX/9ozgFLhWKrMcgGvSFlu/KQfwMhj/Ctu0gLa8v9W9qkCMeZ9e9f2geTzwA2sWcGW9ttqaHCwwZpeG/R8Ya/5G+Mn8X54dCOAZ7xm2Ne+iNmsyNn1Fu9ZZzxcFxHsAb6S1kH19CsDgzhELqLj6Cv/l2lSUxtielvq1gMG8T0YdBbAI5QKY+hSD/S+2CpGPflTuRqwC8gSr41etfCLuAFT601kBfa1wEZ6c/ar9NhoB/GSdsN2gwekPhR8d+3BuiJegIW79jdYDlz8nuvem2XAVybcYKEl83jFbPRIU/QiGQLVXay0GUD2io6pjVOskqqRoVBiHAsVTQSLlax6SGMWaNONo1HFcyjiqJI6tTVE40POzwqdpu+xuzCvk7sYFlMECM46drNOq6rJMzxYd7U8ZbaJAWw0Vi8bLaLmUwEAv9HWHYXsBKydlL8DzdPB/2oFmlx+5n/XskzH7WQpszPjgI6rLIZqIL4WfRj5ShaUpeYxKnftbecZroOc1WXKPn57W4x+V/yEu/8FrqFVTJ9whHCzhqGoBjqru05NMwj/1TEWsg6g1L5K0fvCLyAAyw/NWRH0k7gcfFLjPZNzv3K7hhjsK8rPiVO+4kqnL2+bL8HygJ79SJvdqyYU3IZqTWKEvisKJWhMb7xMDKfQe5ZA8ht+frdBUEOR8puO7SuI7RcNHHirYSOXaeiqGo4G1g8bXSJns+Ts=
*/