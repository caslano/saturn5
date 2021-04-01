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
5QibbAwuceJB+krF6yZIkBwRNOL+EEXK75T94fIE2N/xvQ34nU7FOevT9qK5C/G0GEzJH4ofNB664/z04fFL4Pont7XLCVs6nZc/vPXSkgghgaOdZMEaOcFRECGP7m6CD0m6dpom7YXWh7aU2aieKbX8hG5Ei4bWoFYc/VvanKOpedbZtsibqo/t+VzQWwx7E0w5GkVaPGiSOJglETfZ15eVPEWOuEnFK1Q5CU9fhqNqlsMgubcwIT8g9yU4Oqupq5u/hAte8thVmAHxVU4j62AWlOvdvQ8RHxQoTcY90/w4kLrZyS/7rhJklm4+pthjmZKzx5X5KA5654Och6vmoMy89ksJ+7ba8E2FOhDZnulBsgHBrdD9XSCnIWhYQUbRD3NyoBohKxqsODsldyllPx3nl0CzxZlINmxXKDg8wwT311/swF6KsYKgAeqYI6ltpaBPGrnm00SiNxmvkrgwZE+U1XJwKOl7bCcTCsWT5F6AuQdzAMv235pskXiwnTKmsK5Z6KqgS33ztDx5vppSyeAwYp6JX2yw3NJm56sp6SGJRr9WT0S41ZHvEw==
*/