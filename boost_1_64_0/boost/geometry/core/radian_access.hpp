// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_RADIAN_ACCESS_HPP
#define BOOST_GEOMETRY_CORE_RADIAN_ACCESS_HPP


#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


#include <boost/geometry/util/math.hpp>



namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template<std::size_t Dimension, typename Geometry>
struct degree_radian_converter
{
    typedef typename fp_coordinate_type<Geometry>::type coordinate_type;

    static inline coordinate_type get(Geometry const& geometry)
    {
        return boost::numeric_cast
            <
                coordinate_type
            >(geometry::get<Dimension>(geometry)
              * math::d2r<coordinate_type>());
    }

    static inline void set(Geometry& geometry, coordinate_type const& radians)
    {
        geometry::set<Dimension>(geometry, boost::numeric_cast
            <
                coordinate_type
            >(radians * math::r2d<coordinate_type>()));
    }

};


// Default, radian (or any other coordinate system) just works like "get"
template <std::size_t Dimension, typename Geometry, typename DegreeOrRadian>
struct radian_access
{
    typedef typename fp_coordinate_type<Geometry>::type coordinate_type;

    static inline coordinate_type get(Geometry const& geometry)
    {
        return geometry::get<Dimension>(geometry);
    }

    static inline void set(Geometry& geometry, coordinate_type const& radians)
    {
        geometry::set<Dimension>(geometry, radians);
    }
};

// Specialize, any "degree" coordinate system will be converted to radian
// but only for dimension 0,1 (so: dimension 2 and heigher are untouched)

template
<
    typename Geometry,
    template<typename> class CoordinateSystem
>
struct radian_access<0, Geometry, CoordinateSystem<degree> >
    : degree_radian_converter<0, Geometry>
{};


template
<
    typename Geometry,
    template<typename> class CoordinateSystem
>
struct radian_access<1, Geometry, CoordinateSystem<degree> >
    : degree_radian_converter<1, Geometry>
{};


template<std::size_t Index, std::size_t Dimension, typename Geometry>
struct degree_radian_converter_box_segment
{
    typedef typename fp_coordinate_type<Geometry>::type coordinate_type;

    static inline coordinate_type get(Geometry const& geometry)
    {
        return boost::numeric_cast
            <
                coordinate_type
            >(geometry::get<Index, Dimension>(geometry)
              * math::d2r<coordinate_type>());
    }

    static inline void set(Geometry& geometry, coordinate_type const& radians)
    {
        geometry::set<Index, Dimension>(geometry, boost::numeric_cast
            <
                coordinate_type
            >(radians * math::r2d<coordinate_type>()));
    }

};


// Default, radian (or any other coordinate system) just works like "get"
template <std::size_t Index, std::size_t Dimension, typename Geometry, typename DegreeOrRadian>
struct radian_access_box_segment
{
    typedef typename fp_coordinate_type<Geometry>::type coordinate_type;

    static inline coordinate_type get(Geometry const& geometry)
    {
        return geometry::get<Index, Dimension>(geometry);
    }

    static inline void set(Geometry& geometry, coordinate_type const& radians)
    {
        geometry::set<Index, Dimension>(geometry, radians);
    }
};

// Specialize, any "degree" coordinate system will be converted to radian
// but only for dimension 0,1 (so: dimension 2 and heigher are untouched)

template
<
    typename Geometry,
    template<typename> class CoordinateSystem,
    std::size_t Index
>
struct radian_access_box_segment<Index, 0, Geometry, CoordinateSystem<degree> >
    : degree_radian_converter_box_segment<Index, 0, Geometry>
{};


template
<
    typename Geometry,
    template<typename> class CoordinateSystem,
    std::size_t Index
>
struct radian_access_box_segment<Index, 1, Geometry, CoordinateSystem<degree> >
    : degree_radian_converter_box_segment<Index, 1, Geometry>
{};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief get coordinate value of a point, result is in Radian
\details Result is in Radian, even if source coordinate system
    is in Degrees
\return coordinate value
\ingroup get
\tparam Dimension dimension
\tparam Geometry geometry
\param geometry geometry to get coordinate value from
\note Only applicable to coordinate systems templatized by units,
    e.g. spherical or geographic coordinate systems
*/
template <std::size_t Dimension, typename Geometry>
inline typename fp_coordinate_type<Geometry>::type get_as_radian(Geometry const& geometry)
{
    return detail::radian_access<Dimension, Geometry,
            typename coordinate_system<Geometry>::type>::get(geometry);
}

/*!
\brief set coordinate value (in radian) to a point
\details Coordinate value will be set correctly, if coordinate system of
    point is in Degree, Radian value will be converted to Degree
\ingroup set
\tparam Dimension dimension
\tparam Geometry geometry
\param geometry geometry to assign coordinate to
\param radians coordinate value to assign
\note Only applicable to coordinate systems templatized by units,
    e.g. spherical or geographic coordinate systems
*/
template <std::size_t Dimension, typename Geometry>
inline void set_from_radian(Geometry& geometry,
            typename fp_coordinate_type<Geometry>::type const& radians)
{
    detail::radian_access<Dimension, Geometry,
            typename coordinate_system<Geometry>::type>::set(geometry, radians);
}

/*!
\brief get coordinate value of a segment or box, result is in Radian
\details Result is in Radian, even if source coordinate system
    is in Degrees
\return coordinate value
\ingroup get
\tparam Index index
\tparam Dimension dimension
\tparam Geometry geometry
\param geometry geometry to get coordinate value from
\note Only applicable to coordinate systems templatized by units,
    e.g. spherical or geographic coordinate systems
*/
template <std::size_t Index, std::size_t Dimension, typename Geometry>
inline typename fp_coordinate_type<Geometry>::type get_as_radian(Geometry const& geometry)
{
    return detail::radian_access_box_segment<Index, Dimension, Geometry,
            typename coordinate_system<Geometry>::type>::get(geometry);
}

/*!
\brief set coordinate value (in radian) to a segment or box
\details Coordinate value will be set correctly, if coordinate system of
    point is in Degree, Radian value will be converted to Degree
\ingroup set
\tparam Index index
\tparam Dimension dimension
\tparam Geometry geometry
\param geometry geometry to assign coordinate to
\param radians coordinate value to assign
\note Only applicable to coordinate systems templatized by units,
    e.g. spherical or geographic coordinate systems
*/
template <std::size_t Index, std::size_t Dimension, typename Geometry>
inline void set_from_radian(Geometry& geometry,
            typename fp_coordinate_type<Geometry>::type const& radians)
{
    detail::radian_access_box_segment<Index, Dimension, Geometry,
            typename coordinate_system<Geometry>::type>::set(geometry, radians);
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_RADIAN_ACCESS_HPP

/* radian_access.hpp
fii/LXK+6zPWfZrkPmNwnyf1Ufm3pKrNoPR4d9vxZV7+5p3eGO8733JUqooeH3cMd6O85bMB73+ry94W+614r/hU4D8hztOj3DqvszqP83cs54X9Gytzw/x7TdaV6epK1tPplFdMSLe3bZdfl66uQyd8t7DzkvVxK/d1EX2PJ/+eXVWvYFvP4mNTUtW/SlPVm/H5eparFmVea6uMU/4B+vfkCfJe7ZGp6n2QfSJ93O3aZd0Y5xxTDjzKEvpb/+mk/sN1Yh++w8lf5+c3vx+2f5ravzSd3x71/XNPpYanqu/AEukr12L5DsvfLz3W+m7zF/zbavqcPdm9EtjbPTBdHci63HdrBmtyF/vvraLFqWob6J/j7otbFn9N7Mo1EZ7QhXWPtW+cXBMTrlXy/PAej+eH8jdeAdpPB4vdbXqUcXxbtf3F/5bjLt+N8DzvvZ/z7JP4rNR916qzyr8zVVXflaqKTnL3JbGMffmFbXf5DkQLnXi/5vz7hD79t7T2M1Vnysla8FhKwC5r778B4nkNketqEe8RTmj9HqH8Tc7yVNVhBdfok939b11m6b+h57rSa5w71+134eQ7Xf2jqeqkxzi3XY9WZe71yv2FVu6DeF7SNeJcq0KPpKr5IGtE3Pm+fm+77KL6VDXIlAOvMre/97y0y1ItldrD/XfTbK3Hz/67Dp4vTwDcf/ToEfdsO91S6SfLv5c0Oa5PJ/7eU2v9XZJnlZ3N73P6uUSV+96AlZai0pgH3Xulq15cI3oV7cV4Mqbc41z5Vqq97ec2pKqhL6eqt7p2tPOM6xfsrt8nK2ItHwpzPpk+PTZyHwG+8ujTnGNmuvM3XcyLTPpnyrzopP/tRZ4l9eM8ywz1zDeez+M39ZVU1atbR82u5zg87Tz2as7DrtPzgHnVdYg9L2RsPFjGoJPWrKNme8NiqWoDmMT2YErk2AQT+yawve3OqmuVbNt7X8UnCd4rRe1l9RQt90RDn1G9rNXK3mKcd+LYJJbt+c9X7Pns+ez57Pm072P+m0VDzkuz19MbLQdzz0hTm87i+/UknrlwC/9BL6WW76vUut68V99fqVPRI9CPZin14D58T0TfRt3vqPuY+DOfUvv6lXqE+H3Ktuyn1BPghd7U76/UZZlKzeJxVi/KbsZjEPEXbKeQ+hD64j5KrYF/5P6iO9t5mPY3EN+TRUyfK/EfS5/niJ9lG78Cg9neIbQtJJ+/w0MoqyI+jHvCKfTdz0feIA90ovxA2jfSpi/1b1N2Bnif7Z5A36cp/5S8C8jpE7Yd60EdOJ1+G/vhBQ4k/jM5PLkvfdEXZdIPvgCPVOrupP8cnQ9tpsLfkvsk6grg4zPJ2Uf+8L/1P8WQRQ70vRYczRi81JPjQByg/cH0b6Bsx7740O7X4F3GMBe9kvI7aVNGvkf0BNT9jK9CnwSqafMbtjGceEkmecP3ge/w7Mn+jyTHvehTx7ZOweuJvhzDPnSn7Tk6B7aTQv1r4ArqH6P939i3l8FA+tRnMieIb6Xc4liU0G4c20zF/2P9JxZ4bCJe1Ys5RPup6Br8D6D9NPxmUPc5/S4krmNb46i/HpT52Bd8/gEGkWcF+nXqJ3MM/qg94BNB1j4cH/r3wK+CbZxF/sdR/iW+Z6DvJC7Sx5j+Z9JvIfwmvI76HeT6APGr7MN6PKJsaxt6NZ6b9XGgTR78Gds9nfyOgU8F26kvg/vRpyN8GP6LiFfS/tM+jEUP8gGz6HMDeZXCt4CzabcP27gpkxzgbHL9Pe0uoe9g6rdQnqPnFDiPsi7U/4f6n9Bj8Lmbsu5ZjD9tfcTTKTucPpfptmA4ubwBP9gdD9q8S+5P0eZk2vydfpvwyaf+j8Q=
*/