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
zlrWMeDyX79kBgdx4VCFq0DHQO7zQznpPXSPO3PN7wydOvcXN+efrfUmDrVPdWQrINTkyR22alG79MDJrW2cLMXMFcMWuZuN/1ieDu5cKD58vc3QEe0g7kyI+Hfk6MPUyOdpQhW19JvJ8Vm6lW5vbx9unxo9XNr0e+YrCm6d3HCVhgTrI7sWzWVkr4Z3Cu8TloipOgbyIw4NeaZZfEfe45jqgo3L4yfLzskmvKFe8BpgrMW2BSLbex7Ghu6xMsTJ6Z1c/bf1e/a4wtpXZLzrabmpsWLrSWnHVOlvFMXjh9jW7m1VZwYv5OhwvtMvxeOz3ktZP21GdihnHjdDcEDuP4XrPQd0feE/H07btdvlSGth1fwDfj/C2MKDExnTVqeccJwZu6Ubaqh4HVnjlTrp2X2KxcS09j/lobaocPVguRH4g6LxB/3v8DXIuRjutVbhscyRh7FpfhH9wlUw8oVjsv0rjbtNQUxY1ZF7tEFMqTA9dl5tzqpfOnBCvmVo2P3Ra9b4MOrMvdQPhGLC9aV/iWo/kw6XtD6/IqCc6WJ/CinYM/BL8s+Qp0DLcL5P11fm4mPllu1ajG9hnw4nuvZPZOA1f52QvqYWEzA2N+4E+TfOfqGGQi++lBE+pn/3Xl/nyZb3XvO3uqiCtle77o98/Jk8w/0IAwtRddJ+k7A+eBeYFPdLquu8tj3N/U2ETEKlmmva5dXhI8zAA03s
*/