// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2019-2021 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2022.
// Modifications copyright (c) 2022 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_DISTANCE_MEASURE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_DISTANCE_MEASURE_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/arithmetic/infinite_line_functions.hpp>
#include <boost/geometry/algorithms/detail/make/make.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

#include <cmath>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename T>
struct distance_measure
{
    T measure;

    distance_measure()
        : measure(T())
    {}

    // Returns true if the distance measure is absolutely zero
    bool is_zero() const
    {
      return ! is_positive() && ! is_negative();
    }

    // Returns true if the distance measure is positive. Distance measure
    // algorithm returns positive value if it is located on the left side.
    bool is_positive() const { return measure > T(0); }

    // Returns true if the distance measure is negative. Distance measure
    // algorithm returns negative value if it is located on the right side.
    bool is_negative() const { return measure < T(0); }
};

} // detail


namespace detail_dispatch
{

// TODO: this is effectively a strategy, but for internal usage.
// It might be moved to the strategies folder.

template <typename CalculationType, typename CsTag>
struct get_distance_measure
    : not_implemented<CsTag>
{};

template <typename CalculationType>
struct get_distance_measure<CalculationType, spherical_tag>
{
    // By default the distance measure is zero, no side difference
    using result_type = detail::distance_measure<CalculationType>;

    template <typename SegmentPoint, typename Point>
    static result_type apply(SegmentPoint const& , SegmentPoint const& ,
                             Point const& )
    {
        const result_type result;
        return result;
    }
};

template <typename CalculationType>
struct get_distance_measure<CalculationType, geographic_tag>
    : get_distance_measure<CalculationType, spherical_tag>
{};

template <typename CalculationType>
struct get_distance_measure<CalculationType, cartesian_tag>
{
    using result_type = detail::distance_measure<CalculationType>;

    template <typename SegmentPoint, typename Point>
    static result_type apply(SegmentPoint const& p1, SegmentPoint const& p2,
                             Point const& p)
    {
        // Get the distance measure / side value
        // It is not a real distance and purpose is
        // to detect small differences in collinearity

        auto const line = detail::make::make_infinite_line<CalculationType>(p1, p2);
        result_type result;
        result.measure = arithmetic::side_value(line, p);
        return result;
    }
};

} // namespace detail_dispatch

namespace detail
{

// Returns a (often very tiny) value to indicate its side, and distance,
// 0 (absolutely 0, not even an epsilon) means collinear. Like side,
// a negative means that p is to the right of p1-p2. And a positive value
// means that p is to the left of p1-p2.

template <typename SegmentPoint, typename Point, typename Strategies>
inline auto get_distance_measure(SegmentPoint const& p1, SegmentPoint const& p2, Point const& p,
                                 Strategies const&)
{
    return detail_dispatch::get_distance_measure
            <
                typename select_coordinate_type<SegmentPoint, Point>::type,
                typename Strategies::cs_tag
            >::apply(p1, p2, p);

}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_DISTANCE_MEASURE_HPP

/* get_distance_measure.hpp
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
*/