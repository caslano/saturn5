// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2016, 2017.
// Modifications copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_AZIMUTH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_AZIMUTH_HPP


#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/spherical.hpp>
#include <boost/geometry/formulas/vincenty_inverse.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

// An azimuth is an angle between a vector/segment from origin to a point of
// interest and a reference vector. Typically north-based azimuth is used.
// North direction is used as a reference, angle is measured clockwise
// (North - 0deg, East - 90deg). For consistency in 2d cartesian CS
// the reference vector is Y axis, angle is measured clockwise.
// http://en.wikipedia.org/wiki/Azimuth

#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch
{

template <typename ReturnType, typename Tag>
struct azimuth
    : not_implemented<Tag>
{};

template <typename ReturnType>
struct azimuth<ReturnType, geographic_tag>
{
    template <typename P1, typename P2, typename Spheroid>
    static inline ReturnType apply(P1 const& p1, P2 const& p2, Spheroid const& spheroid)
    {
        return geometry::formula::vincenty_inverse<ReturnType, false, true>().apply
                    ( get_as_radian<0>(p1), get_as_radian<1>(p1),
                      get_as_radian<0>(p2), get_as_radian<1>(p2),
                      spheroid ).azimuth;
    }

    template <typename P1, typename P2>
    static inline ReturnType apply(P1 const& p1, P2 const& p2)
    {
        return apply(p1, p2, srs::spheroid<ReturnType>());
    }
};

template <typename ReturnType>
struct azimuth<ReturnType, spherical_equatorial_tag>
{
    template <typename P1, typename P2, typename Sphere>
    static inline ReturnType apply(P1 const& p1, P2 const& p2, Sphere const& /*unused*/)
    {
        return geometry::formula::spherical_azimuth<ReturnType, false>
                    ( get_as_radian<0>(p1), get_as_radian<1>(p1),
                      get_as_radian<0>(p2), get_as_radian<1>(p2)).azimuth;
    }

    template <typename P1, typename P2>
    static inline ReturnType apply(P1 const& p1, P2 const& p2)
    {
        return apply(p1, p2, 0); // dummy model
    }
};

template <typename ReturnType>
struct azimuth<ReturnType, spherical_polar_tag>
    : azimuth<ReturnType, spherical_equatorial_tag>
{};

template <typename ReturnType>
struct azimuth<ReturnType, cartesian_tag>
{
    template <typename P1, typename P2, typename Plane>
    static inline ReturnType apply(P1 const& p1, P2 const& p2, Plane const& /*unused*/)
    {
        ReturnType x = get<0>(p2) - get<0>(p1);
        ReturnType y = get<1>(p2) - get<1>(p1);

        // NOTE: azimuth 0 is at Y axis, increasing right
        // as in spherical/geographic where 0 is at North axis
        return atan2(x, y);
    }

    template <typename P1, typename P2>
    static inline ReturnType apply(P1 const& p1, P2 const& p2)
    {
        return apply(p1, p2, 0); // dummy model
    }
};

} // detail_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/// Calculate azimuth between two points.
/// The result is in radians.
template <typename ReturnType, typename Point1, typename Point2>
inline ReturnType azimuth(Point1 const& p1, Point2 const& p2)
{
    return detail_dispatch::azimuth
            <
                ReturnType,
                typename geometry::cs_tag<Point1>::type
            >::apply(p1, p2);
}

/// Calculate azimuth between two points.
/// The result is in radians.
template <typename ReturnType, typename Point1, typename Point2, typename Model>
inline ReturnType azimuth(Point1 const& p1, Point2 const& p2, Model const& model)
{
    return detail_dispatch::azimuth
            <
                ReturnType,
                typename geometry::cs_tag<Point1>::type
            >::apply(p1, p2, model);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_AZIMUTH_HPP

/* azimuth.hpp
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
*/