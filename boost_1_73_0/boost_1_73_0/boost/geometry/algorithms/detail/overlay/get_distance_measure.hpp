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
qKKz3UUBT/rGNclNi48j3DR08oKHikTWZW74i7xYcEuH8xRT4t3IrHmo6Ua+Pyat/wL9UCOTC29GUfx4y+gkc2P/ZDLICbaGJWRXsxl3NI4NDe2pcFZ9GKEvJZJOr/msS6p1nG+iENKkAOuPXai8k+yfQatickEtj2VFEY7F0YSunQSxGnYsimRq2TSg1p23hWMYkBLdTqq5ujYq6aNsWTN3Yc8v0tsWkURb0zwxmSPC0N00btSG3vjVF3rZV8/pK1xeaMCdAKbyMCHJ6vWEO73slwxk0fWYZT3mQzzu0aHyMls4QMf17x6dld1uVtah8fIq9zC6RZd0OLCoL8ub5B4jM7eLVt1cWNp3zsPhPuvo3BtZjqbm4PkeHTnXP5b1Yx2N3Hv1rFuLlndpyUf3wVHnjr1S7LTk/Ht3tHxwRenvPnhKEZOqO7RIAGuVcUZNNoSlWTzTJpOcRxdUoJsNUb5lJmBstwvtmI4rGPyVZxDSM9A6IXavocA28KNib9M48bELYLONBcrbIUXGwsuZj86B4Q0GZQUhW2I5mwKUDrZGlYI3fTfCXaU+R+dXG3TXxR8X2caSh7xVQF5xvvlSZkERZ70uzOIAfYQb+r7M4h0dOa/P5ReU3EJjcAxHxZtJsIiWQzCyLA9iuWii
*/