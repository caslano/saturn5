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
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
*/