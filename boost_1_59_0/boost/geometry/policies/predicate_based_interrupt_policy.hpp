// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_POLICIES_PREDICATE_BASED_INTERRUPT_POLICY_HPP

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


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
        // if there is at least one unacceptable turn in the range, return true
        bool const has_unacceptable_turn = std::any_of(boost::begin(range), boost::end(range),
            [](auto const& turn) { 
                return ! IsAcceptableTurnPredicate::apply(turn);
            });
        
        has_intersections = has_unacceptable_turn
                && !(AllowEmptyTurnRange && boost::empty(range));

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
        // if there is at least one unacceptable turn in the range, return true
        bool const has_unacceptable_turn = std::any_of(boost::begin(range), 
                                                       boost::end(range),
                                                       [&]( auto const& turn ) { 
                                                           return ! m_predicate.apply(turn);
                                                       });
        
        has_intersections = has_unacceptable_turn
            && !(AllowEmptyTurnRange && boost::empty(range));

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