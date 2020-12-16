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
qRO76/stKDZbmQosMnF9KrHdzdK+Cr3uNFYsu0of7mh2YmIkO3qmAf+IdEYxJR1Kh8B0Fke/qzM4vN5Vue1Wma9b8ZT6yYH+EzKPh48OZuSa07ZbjlZnbuPeyuN3XyVXvlwulu8k6Xf27qm4WyvuvWb2b925r+IenMZ9b8XtnxrFwx0r7vHsKEFaap52uSkfOboN+6Im9glbuW7dTPtX8mOvcZTe3swV8NcJxeA3CcVgV1IxWJ5UDB6XVAyexI7wPO6SwZOTJAG9g4F8JwZfxF0y+AvuNCdOWCKl5+1JJd9tk0q+iwkl36sSSq6vJZVcc0lF+HXc5VWm/5A/oe6vTij+7SnFdwX+SdTKlOLTkVJ8VqVU2qtTKt01KZVeZ0qlvzYV1Oc6jree8V3Mt5vpNjD/jcx3E6e/2eDzgZmov/r+P//5T7HIazbKBzIs/vrGTOP+M47/gsdniUfc/qT5QLdLuM5dHz7p68SnzeCTEtd+dV4nPpuuE59bMB9Vs6/96tF8UHeu/Tqg+aAuXvs1QHyWbtAPlnwaqD/1rpzBp0Nc+zXBfJaatarHZ4l149HXic95j88SbfqpHp8l2vSF68TnxR6fJZb9RcmnQV8ed13y+Cyxjn0gxOeiuLbr4x6fJfqOz4f8/F+voU2W19x14nPZ9M9L4POd68Tnyrnr09/4hcHHWYL/WTD1vIT6ftXUzxL4/M3g8+lrzZS8Hnl92ouUx2eJvrXN47NE39rh8VmiT+z0+CzRJ24iPksX6BaPvD714jY2eVKL1/ReC58DA4s3yLtY+Jy/uHgLOmzhM7uQFIu9jtj00yMWfQ3Y+MwuXp772/iIxfMZ9/ksrVM2Q3yWXuGfKvksPVvixcRn6RXstcxnqSp6I/NZqoouXSc+7/D4LNG3ztbgk16kgj7v8Vmib73s8VmiT/yOyWcJ/c0rBp+lVNdfxPBxFsHnT9eJT/pRtfkkF8Gn81GNz//E2XjXIvjE2bi7CD5x3mTboxqfZ4uz8R6DT8IMNh3E8BkI8XGukc+N68Z147pxXc/r4LFjOJ9zfOBY//H+E0Mn7y7f+QrAD/ff/eB9jg2p9UlsoKB7/+EjdMc2CHnHG2D9fXTHTULljeJgmwRuPr3xynEJot75jZ6xqYvuclsD7llKG3dsrJF3ecvKfQ8SBj4SSzf5Tkxwl7Q9vKxI77RFQj/LO6cjsyQFV9kgXpQ5SgKXTP4gMAcZL5OQpHsO958ifN9ehF46s+KdVZH3PDPgvR+8p93by053GeiDd7j36TsiRfdxhfc5Bd79+LwfTD7L4yLyg3x4lHdh7DJhmY4f7COcYuftYlGqojXUs3uAHzp26iwx8Z53EXvjXen12Mn7ieP9h4/eB/k4cvQeZAN3PzpwinVM+6KgMrlHb09onzbhoecgvqH9LFiIlYvsu0brnIeSEfWZKDpT9aDCQ+jQWF26XOF0vlLNTOar48Vc5UFQjDwDBv1mjh6+/0PcLftdKmp1NSCHnZ8sq3oMT2MhfyeyEX7Hpkr/Xe4rMvFyn5D8tGLg/XaSgGx35xGYgXe2yNyfSXAyIH3xPksrvhY94sfSm/hTQ4P6uCfVpb5j/fftP7bfe7/P0aH+Q0jh5IljDzDfUf8C+GD8O/Y2so/+To3unheCfaPpU++0xeI877SFvQBfnhs03R8/Ub2js1F8PNV0YagX2253e31eb48E7L79PoKoctyGzHiv0h+Z7+SbTAByZ77SO7JrviPnFMV85yjspwiv36P4fRTBePcj9GE/yMREIUsRjHeKwD5U4Ux/RdiAn7utt+/VkF5+TjS8j47GCCdOnujnOE4g2C/qszc4bPz0U9HfjxntfKMO/ic=
*/