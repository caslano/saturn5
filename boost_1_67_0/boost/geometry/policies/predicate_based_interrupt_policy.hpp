// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template
<
    typename IsAcceptableTurnPredicate,
    bool AllowEmptyTurnRange = true // by default, allow an empty turn range
>
struct stateless_predicate_based_interrupt_policy
{
    static bool const enabled = true;
    bool has_intersections; // set to true if there is at least one
                            // unacceptable turn

    inline stateless_predicate_based_interrupt_policy()
        : has_intersections(false)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // if there is at least one unacceptable turn in the range, return false
        has_intersections = !detail::check_iterator_range
            <
                IsAcceptableTurnPredicate,
                AllowEmptyTurnRange
            >::apply(boost::begin(range), boost::end(range));

        return has_intersections;
    }
};




template
<
    typename IsAcceptableTurnPredicate,
    bool AllowEmptyTurnRange = true // by default, allow an empty turn range
>
struct predicate_based_interrupt_policy
{
    static bool const enabled = true;
    bool has_intersections; // set to true if there is at least one
                            // unacceptable turn
    IsAcceptableTurnPredicate const& m_predicate;

    inline
    predicate_based_interrupt_policy(IsAcceptableTurnPredicate const& predicate)
        : has_intersections(false)
        , m_predicate(predicate)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // if there is at least one unacceptable turn in the range, return false
        has_intersections = !detail::check_iterator_range
            <
                IsAcceptableTurnPredicate,
                AllowEmptyTurnRange
            >::apply(boost::begin(range), boost::end(range), m_predicate);

        return has_intersections;
    }
};




}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP

/* predicate_based_interrupt_policy.hpp
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
*/