// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_CS_HPP
#define BOOST_GEOMETRY_CORE_CS_HPP


#include <cstddef>

#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

/*!
\brief Unit of plane angle: Degrees
\details Tag defining the unit of plane angle for spherical coordinate systems.
    This tag specifies that coordinates are defined in degrees (-180 .. 180).
    It has to be specified for some coordinate systems.
\qbk{[include reference/core/degree_radian.qbk]}
*/
struct degree {};


/*!
\brief Unit of plane angle: Radians
\details Tag defining the unit of plane angle for spherical coordinate systems.
    This tag specifies that coordinates are defined in radians (-PI .. PI).
    It has to be specified for some coordinate systems.
\qbk{[include reference/core/degree_radian.qbk]}
*/
struct radian {};


#ifndef DOXYGEN_NO_DETAIL
namespace core_detail
{

template <typename DegreeOrRadian>
struct define_angular_units
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Coordinate system unit must be degree or radian.",
        DegreeOrRadian);
};

template <>
struct define_angular_units<geometry::degree>
{
    typedef geometry::degree units;
};

template <>
struct define_angular_units<geometry::radian>
{
    typedef geometry::radian units;
};

} // namespace core_detail
#endif // DOXYGEN_NO_DETAIL


namespace cs
{

/*!
\brief Cartesian coordinate system
\details Defines the Cartesian or rectangular coordinate system
    where points are defined in 2 or 3 (or more)
dimensions and usually (but not always) known as x,y,z
\see http://en.wikipedia.org/wiki/Cartesian_coordinate_system
\ingroup cs
*/
struct cartesian {};




/*!
\brief Geographic coordinate system, in degree or in radian
\details Defines the geographic coordinate system where points
    are defined in two angles and usually
known as lat,long or lo,la or phi,lambda
\see http://en.wikipedia.org/wiki/Geographic_coordinate_system
\ingroup cs
\note might be moved to extensions/gis/geographic
*/
template<typename DegreeOrRadian>
struct geographic
    : core_detail::define_angular_units<DegreeOrRadian>
{};



/*!
\brief Spherical (polar) coordinate system, in degree or in radian
\details Defines the spherical coordinate system where points are
    defined in two angles
    and an optional radius usually known as r, theta, phi
\par Coordinates:
- coordinate 0:
    0 <= phi < 2pi is the angle between the positive x-axis and the
        line from the origin to the P projected onto the xy-plane.
- coordinate 1:
    0 <= theta <= pi is the angle between the positive z-axis and the
        line formed between the origin and P.
- coordinate 2 (if specified):
    r >= 0 is the distance from the origin to a given point P.

\see http://en.wikipedia.org/wiki/Spherical_coordinates
\ingroup cs
*/
template<typename DegreeOrRadian>
struct spherical
    : core_detail::define_angular_units<DegreeOrRadian>
{};


/*!
\brief Spherical equatorial coordinate system, in degree or in radian
\details This one resembles the geographic coordinate system, and has latitude
    up from zero at the equator, to 90 at the pole
    (opposite to the spherical(polar) coordinate system).
    Used in astronomy and in GIS (but there is also the geographic)

\see http://en.wikipedia.org/wiki/Spherical_coordinates
\ingroup cs
*/
template<typename DegreeOrRadian>
struct spherical_equatorial
    : core_detail::define_angular_units<DegreeOrRadian>
{};



/*!
\brief Polar coordinate system
\details Defines the polar coordinate system "in which each point
    on a plane is determined by an angle and a distance"
\see http://en.wikipedia.org/wiki/Polar_coordinates
\ingroup cs
*/
template<typename DegreeOrRadian>
struct polar
    : core_detail::define_angular_units<DegreeOrRadian>
{};


/*!
\brief Undefined coordinate system
\ingroup cs
*/
struct undefined {};


} // namespace cs


namespace traits
{

/*!
\brief Traits class defining coordinate system tag, bound to coordinate system
\ingroup traits
\tparam CoordinateSystem coordinate system
*/
template <typename CoordinateSystem>
struct cs_tag
{
};


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS

template<typename DegreeOrRadian>
struct cs_tag<cs::geographic<DegreeOrRadian> >
{
    typedef geographic_tag type;
};

template<typename DegreeOrRadian>
struct cs_tag<cs::spherical<DegreeOrRadian> >
{
    typedef spherical_polar_tag type;
};

template<typename DegreeOrRadian>
struct cs_tag<cs::spherical_equatorial<DegreeOrRadian> >
{
    typedef spherical_equatorial_tag type;
};


template<>
struct cs_tag<cs::cartesian>
{
    typedef cartesian_tag type;
};


template <>
struct cs_tag<cs::undefined>
{
    typedef cs_undefined_tag type;
};

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


} // namespace traits


/*!
\brief Meta-function returning coordinate system tag (cs family) of any geometry
\tparam Geometry \tparam_geometry
\ingroup core
*/
template <typename Geometry>
struct cs_tag
{
    typedef typename traits::cs_tag
        <
            typename geometry::coordinate_system<Geometry>::type
        >::type type;
};


namespace traits
{

// cartesian or undefined
template <typename CoordinateSystem>
struct cs_angular_units
{
    typedef geometry::radian type;
};

#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS

template<typename DegreeOrRadian>
struct cs_angular_units<cs::geographic<DegreeOrRadian> >
{
    typedef DegreeOrRadian type;
};

template<typename DegreeOrRadian>
struct cs_angular_units<cs::spherical<DegreeOrRadian> >
{
    typedef DegreeOrRadian type;
};

template<typename DegreeOrRadian>
struct cs_angular_units<cs::spherical_equatorial<DegreeOrRadian> >
{
    typedef DegreeOrRadian type;
};

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


} // namespace traits


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Geometry>
struct cs_angular_units
{
    typedef typename traits::cs_angular_units
        <
            typename geometry::coordinate_system<Geometry>::type
        >::type type;
};


template <typename Units, typename CsTag>
struct cs_tag_to_coordinate_system
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this coordinate system.",
        Units, CsTag);
};

template <typename Units>
struct cs_tag_to_coordinate_system<Units, cs_undefined_tag>
{
    typedef cs::undefined type;
};

template <typename Units>
struct cs_tag_to_coordinate_system<Units, cartesian_tag>
{
    typedef cs::cartesian type;
};

template <typename Units>
struct cs_tag_to_coordinate_system<Units, spherical_equatorial_tag>
{
    typedef cs::spherical_equatorial<Units> type;
};

template <typename Units>
struct cs_tag_to_coordinate_system<Units, spherical_polar_tag>
{
    typedef cs::spherical<Units> type;
};

template <typename Units>
struct cs_tag_to_coordinate_system<Units, geographic_tag>
{
    typedef cs::geographic<Units> type;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_CS_HPP

/* cs.hpp
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
*/