// Boost.Geometry Index
//
// R-tree strategies
//
// Copyright (c) 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_INDEX_HPP


#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

namespace services
{

template
<
    typename Geometry,
    typename CSTag = typename geometry::cs_tag<Geometry>::type
>
struct default_strategy
{
    /*BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Geometry>)
    );*/

    typedef geometry::default_strategy type;
};


// TEMP
// Utility to get index strategy from other strategy
// In the final version this utility will probably replaced with some other mechanism
// The issue is cross-dependencies between strategies
template <typename Strategy>
struct from_strategy
{
    /*BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THESE_TYPES
        , (types<Strategy>)
    );*/

    typedef geometry::default_strategy type;

    static inline type get(Strategy const&)
    {
        return type();
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_INDEX_HPP

/* index.hpp
lrCycNrmvveLKAtLdCJyvVzemyJXPrtiT6bSd9oJfJCbwEDA2grL42ZiXF+4H8IVRhZg0hA8bI8/tcHgZxyp/q1YrDw+CEk/O0S6eGupkBpc/gFhff12QgB7BkqZu0q9+/Qn1TvZ184PF9EsPyfC8zIAf0fX8FEgkupwiug0QjqX/dHRdua6whkRvGVY/YKKOpdnebnRaYLrbPIVR5/k4yZGtJ/C3oMJlpNuduAg5E+RYmKmnO+sE9XP9GFZvasvKo85OPePi7hdpK1tTKza4sGEI22ueddDP9xPypkRsJ7OXwp5GnnHhTcCLf5PVGzxU4suIm8f9SedWpegQNp9CLCL+G9D+iLSIsoi8iKqQygZ0jkcqxbXFmMBlSwkKySmh26nS6nx/d+7X8jNyBQ93rlJe/pz4U+4uWSHyN4onWJUtditRIcY3qgBEd2rb3CQnkLEe/DQQj70rH86nR/r2EFyJXMV+oT2GhUjVLLnj0/y0LtYi/wPQWmEQPZzmexHDghl30tQCBY5xo4YynQIoTJYbs1ry3hL5AOmInKgCHcIt6mgH+ua0wfUbLTiUI0exR/BRQ434l7yZBpx9E1m1Aly9uJGSqSEFlx2rKY0XBpludYDSsJOJ9L2nyZrkKlTpv0s+7lnM+2m1rweQP694GhbWH+hsO1qcTDAwmEh3XsU16EcxNG09JErL8PfvremRNPD2lDJWvVJc0XW
*/