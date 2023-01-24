// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP

#include <algorithm>

#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>
#include <boost/geometry/algorithms/detail/is_simple/failure_policy.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename MultiPoint>
struct is_simple_multipoint
{
    template <typename Strategy>
    static inline bool apply(MultiPoint const& multipoint, Strategy const&)
    {
        typedef typename Strategy::cs_tag cs_tag;
        typedef geometry::less
            <
                typename point_type<MultiPoint>::type,
                -1,
                cs_tag
            > less_type;

        if (boost::empty(multipoint))
        {
            return true;
        }

        MultiPoint mp(multipoint);
        std::sort(boost::begin(mp), boost::end(mp), less_type());

        simplicity_failure_policy policy;
        return !detail::is_valid::has_duplicates
            <
                MultiPoint, closed, cs_tag
            >::apply(mp, policy);
    }
};


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A MultiPoint is simple if no two Points in the MultiPoint are equal
// (have identical coordinate values in X and Y)
//
// Reference: OGC 06-103r4 (6.1.5)
template <typename MultiPoint>
struct is_simple<MultiPoint, multi_point_tag>
    : detail::is_simple::is_simple_multipoint<MultiPoint>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_MULTIPOINT_HPP

/* multipoint.hpp
wMoz5YHo8iwemf5dfUvKVDNMndca87gXAg/yPO6LyePkqOx/dvyQsdIdyS9aV+HyA5wnRvKr/yoNJeyGdfVt+GoFfOWNW0b/bkMZp0Dg2t2sjMW7o8t4HVH+i152Sd39w9R9jTHdeyDwK57ulph0z4/K/q51K7buG4fhc1/azfncU9akIdOvMtCYX7Ez8cRfRdO4WwT1NbxSWChmC92oBHZ8z3fa627873TKA2R6A2Oi9AZOw7tOjW/ROB5ZAx5kBXpRw0HX/orrHd4LnmfBvfUro40ESv8vNODYEQUnPkPJHL7A9Jv+oNcieGo0MbPtSsFCvrhUWoQtHwpCvsYNoHcVcV6yIzAeObQzcboasnKl7slAO8l6eAV4OvZofOQ6zQQFKRgTzONyKmw54aVkLGR25l1JMR122+0F32lcJWSLtVK7fNqyRnVZveACqs02z+639Qs+7EOFlIQh+BVrbxsylusQFGUDKdcR8Azu0WikIGe1MmMZDPGmfBT7vkiGj2CafoClD3vcGJMPjbwAfRVj79G9NwMVwBrqmwCeF/dqNMH6ITZaggYDzPzKASb4qhnfM9P+qRc0cR167r+QGSingX4aGNi8kwqgn2LHtfTNhcWYCU6VsLNofjT0itlgZmgVPi4wdc17JYpaVu7EdXKNkm1pBOp2wL4FO9z2tS6XO8+1xuN23Z3udiVhb2am21voWujzZXn97qxC
*/