// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2019 Barend Gehrels, Amsterdam, the Netherlands.

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

    bool is_small() const { return false; }
    bool is_zero() const { return false; }
    bool is_positive() const { return false; }
    bool is_negative() const { return false; }
};

template <typename T>
struct distance_measure_floating
{
    T measure;

    distance_measure_floating()
        : measure(T())
    {}

    // Returns true if the distance measure is small.
    // This is an arbitrary boundary, to enable some behaviour
    // (for example include or exclude turns), which are checked later
    // with other conditions.
    bool is_small() const { return std::abs(measure) < 1.0e-3; }

    // Returns true if the distance measure is absolutely zero
    bool is_zero() const { return measure == 0.0; }

    // Returns true if the distance measure is positive. Distance measure
    // algorithm returns positive value if it is located on the left side.
    bool is_positive() const { return measure > 0.0; }

    // Returns true if the distance measure is negative. Distance measure
    // algorithm returns negative value if it is located on the right side.
    bool is_negative() const { return measure < 0.0; }
};

template <>
struct distance_measure<long double>
    : public distance_measure_floating<long double> {};

template <>
struct distance_measure<double>
    : public distance_measure_floating<double> {};

template <>
struct distance_measure<float>
    : public distance_measure_floating<float> {};

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
struct get_distance_measure<CalculationType, cartesian_tag>
{
    typedef detail::distance_measure<CalculationType> result_type;

    template <typename SegmentPoint, typename Point>
    static result_type apply(SegmentPoint const& p1, SegmentPoint const& p2,
                             Point const& p)
    {
        // Get the distance measure / side value
        // It is not a real distance and purpose is
        // to detect small differences in collinearity

        typedef model::infinite_line<CalculationType> line_type;
        line_type const line = detail::make::make_infinite_line<CalculationType>(p1, p2);
        result_type result;
        result.measure = arithmetic::side_value(line, p);
        return result;
    }
};

template <typename CalculationType>
struct get_distance_measure<CalculationType, spherical_tag>
{
    typedef detail::distance_measure<CalculationType> result_type;

    template <typename SegmentPoint, typename Point>
    static result_type apply(SegmentPoint const& , SegmentPoint const& ,
                             Point const& )
    {
        // TODO, optional
        result_type result;
        return result;
    }
};

template <typename CalculationType>
struct get_distance_measure<CalculationType, geographic_tag>
        : get_distance_measure<CalculationType, spherical_tag> {};


} // namespace detail_dispatch

namespace detail
{

// Returns a (often very tiny) value to indicate its side, and distance,
// 0 (absolutely 0, not even an epsilon) means collinear. Like side,
// a negative means that p is to the right of p1-p2. And a positive value
// means that p is to the left of p1-p2.

template <typename cs_tag, typename SegmentPoint, typename Point>
static distance_measure<typename select_coordinate_type<SegmentPoint, Point>::type>
get_distance_measure(SegmentPoint const& p1, SegmentPoint const& p2, Point const& p)
{
    return detail_dispatch::get_distance_measure
            <
                typename select_coordinate_type<SegmentPoint, Point>::type,
                cs_tag
            >::apply(p1, p2, p);

}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_DISTANCE_MEASURE_HPP

/* get_distance_measure.hpp
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
*/