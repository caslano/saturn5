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
fF1M1uU9jKUHLLGViso0GL+r25X0MuuMEko1qSxLrXWZywTBvKlzIQMQCaNnLZgDvLypj4K3mfBhgjfz/ihRslZO3xAUYoPiOWG2zhgksuxqVDyHzNblsaUHkSVgk/AABVx1BIrDurynGTgmxEXYEelArCBwniQQRQIOeCLtpQcQWwJvtO6ViIcjBWIDHbGPxV76GWK3ISxG99rRDabvss5YB1Ta4ZHWgmJ47Z6fjSiQ8B03WWffAV8mZ2Md4XGkb7fObh/JOn9O1vn+YJ3bfT3i1JZZskEl24taIEzUvuJ1JSZABfw7Fc8pCj5C8Ban+PqfQklj7SvZboQMOMt2qGLtgDqvltitjtL84wTgq0qvHN8QcX6/EZJej+aIwiZYZ9wfQV/5lVTLoShxAmt9JCtoqKigoZj3iTzNih8Gy5U4UvFXKemV1hnXMqV5j0yYVAlO66VrVjedui2Q8mczNaPSpe4U6REniIQlhslPgmiWiBZXWEJpUTHMSOhQy2BTnOoOu387RZtjMshBIEwYjIowLSV2X68O2rb79PUhvaky1Qea5X5pwYYH8Ymc6bMbteeQIJRrUSDXy820G5l5NGW+fs+LfFE6hKqZeZ39bFazowA5fa7E86AwJcTSamBK7esdiQ3N6jZ7oSPRplaWHrLZC/smNvKNiSutttgLXYlWO1p1YwMeojY3MLoFI1oySbx9fURiC9ZrfirrzR2TQ3zjKX9NEzW6tBYkAFmXR/NtUtTMuU4vGrC6vlRDVG5inGd9Q0bFhlmZJF3jUnYIVYOxEXpWz8b4ehhhZrTP7pUGl+U9KWf2LrUSgrT7sttrY+6l0ZvWRIRudKqbEXqFNuheOfh8A2+Hul4YyM3aDYDwTl8/JR1ClzUUq7W/V5rNhaDN1cSXLfXs6q0S4ZE3Tvj9gIst7AczRKD7Ci4tSEtOtqebhHU//lmEtPQYh72pWe+VKiB62pQqreW9svJzttZXlpdGoy+YkphtyG1ch4O9CFfLq98SPcPsBXz5HpmL2n7PKPz95uZ4l8QZg7GALHWgGPY0RdswRjQkSE19WO9sR2/j+/ZCX/8rBY9CiFvBkNZiNEs43UI53k0GPkEJs6km1R3RqQTLvFCWOTKszNdqF7AkleiN2WMxR70nU9GTCZi9MWG9a1fRtYtw3/MsUcombQ9H8vlrOZIYcns5qq3ag5Uu5CBz9ctcHzko+lHmar9S+9M9PCF+Koy59yTayIMh5jpUDwb7jHxIRvbUaUgMe9FzLGK3UxJnPHBq9gXpjZZJ4sPopVSfH57jEIlx9EAI45rq2pOS2i0moSwC44MwjCeqd+kYfbmueJfOYCYz30pfuklyFhpBzD8QGEH8+W7ekDwZJpwUycPYAyHhDNUKiTbpZBirl+vlD2dEG0a03jo3bcjAbPrOFwxcjpTVD/rDsoqVNKLDskquPhnOzEZZ3C8/DWGM1n4eJUc9PwNz07nn3PPf9yhFgeGzC3t45pQSLCE1FksrLq/dUv6L6zezN+vrN7UKRwp7XWl2y9jWitqYM/8XCmH/jelylabdZEvY2sivWShRVGN5XdhuwZh3nODU2BijXgV8ilzKz5jeM8liyG0JMhguGASew2tS/BjtOi3gpH4iUYamQFe8JikGo9HVzq6jnv4UxVMSUzcJSVhtDVzqdmvjuMQc67i9lhyndVpVFubSGS41ItHpr7KDBae/RK10pVeOTXKqJS5zqSupyuWNSHRhbGax2iIS7dbGpkDeireHBVKKR+bitekfP5KfbzaG+Nlblx8nhstjewiGPNUmcGTBL8Po9JSI8T1Yq/oF1sy/g7VgfZjGJsn6sIhZgzeGEJkQlDNjS1k=
*/