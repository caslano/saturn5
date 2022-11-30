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
#include <boost/geometry/core/coordinate_promotion.hpp>

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