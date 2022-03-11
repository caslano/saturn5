// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014-2018, Oracle and/or its affiliates.

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

#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/coordinate_system.hpp>
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
    BOOST_MPL_ASSERT_MSG
        ((false),
         COORDINATE_SYSTEM_UNITS_MUST_BE_DEGREES_OR_RADIANS,
         (types<DegreeOrRadian>));
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
    BOOST_MPL_ASSERT_MSG((false),
                         NOT_IMPLEMENTED_FOR_THIS_COORDINATE_SYSTEM,
                         (types<CsTag>));
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