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
O9fSvTl++Fc6+tvGURv8fOLJPN6GjmeDfn/YG91csbLO1B37rMxxJZC4stDx7HUPHNTL0Tlwr15aaF6UFlKvLTURPfS33NgIYd3i/e7EB9HA9Mak3wggpjFNMfuJFCF/Nkky8AxM5U/Yz78MvMQDzvtNcnZ3JP+B6omUno+sfW+5i0ASthkkP2QznEB+TbTXTr1JoIlGW7QVRyfr4LJl2A5uri3CNRaOQxTyBqj9pEORBrj6gUTW2T+yrZRN0u816/UvSjPRWjMX04MT66eKxGjc2J3JWSRls3qmt+msZcVjeTP84KzempkZIDHRr5T2q/ZMYAWKnsjJGh4Hpn15vwSLLF6PwUuQi2Vyvx/JJbhsLN6oCNW+TpFtZULgI2angifBzGWwtW1cjVwRmXQEzjO2c5w7RolY5uKMdDWZc0waBBMpgnRxK6NY2wY/BJ8E2RgzDIlyyvafmycnhVYw1y/5VvjkRCuxirk/Ks8dtzKa2aDQwkBqaewFuMaez8TMs0FjrHWH3j/TGZHHPnoqU1IoQJjJnKYeyXgJcbjE1408KIND28LgJNO5GQfjFNAk/w1N/mDIbb7raW+z4jDp3NjNrfQFKgyLJl4wCxVNRONVqBzEazFULEhugWuoAzP+GDTKk/teMBpbqaGt
*/