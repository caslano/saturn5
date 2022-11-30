// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_ACCESS_HPP
#define BOOST_GEOMETRY_CORE_ACCESS_HPP


#include <cstddef>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry
{

/// Index of minimum corner of the box.
int const min_corner = 0;

/// Index of maximum corner of the box.
int const max_corner = 1;

namespace traits
{

/*!
\brief Traits class which gives access (get,set) to points.
\ingroup traits
\par Geometries:
///     @li point
\par Specializations should provide, per Dimension
///     @li static inline T get(G const&)
///     @li static inline void set(G&, T const&)
\tparam Geometry geometry-type
\tparam Dimension dimension to access
*/
template <typename Geometry, std::size_t Dimension, typename Enable = void>
struct access
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};


/*!
\brief Traits class defining "get" and "set" to get
    and set point coordinate values
\tparam Geometry geometry (box, segment)
\tparam Index index (min_corner/max_corner for box, 0/1 for segment)
\tparam Dimension dimension
\par Geometries:
    - box
    - segment
\par Specializations should provide:
    - static inline T get(G const&)
    - static inline void set(G&, T const&)
\ingroup traits
*/
template <typename Geometry, std::size_t Index, std::size_t Dimension>
struct indexed_access {};


} // namespace traits

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename Geometry,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access_non_pointer
{
    static constexpr CoordinateType get(Geometry const& geometry)
    {
        return traits::indexed_access<Geometry, Index, Dimension>::get(geometry);
    }
    static void set(Geometry& b, CoordinateType const& value)
    {
        traits::indexed_access<Geometry, Index, Dimension>::set(b, value);
    }
};

template
<
    typename Geometry,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access_pointer
{
    static constexpr CoordinateType get(Geometry const* geometry)
    {
        return traits::indexed_access<typename std::remove_pointer<Geometry>::type, Index, Dimension>::get(*geometry);
    }
    static void set(Geometry* geometry, CoordinateType const& value)
    {
        traits::indexed_access<typename std::remove_pointer<Geometry>::type, Index, Dimension>::set(*geometry, value);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template
<
    typename Tag,
    typename Geometry,
    typename
    CoordinateType,
    std::size_t Dimension,
    typename IsPointer
>
struct access
{
    //static inline T get(G const&) {}
    //static inline void set(G& g, T const& value) {}
};

template
<
    typename Tag,
    typename Geometry,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension,
    typename IsPointer
>
struct indexed_access
{
    //static inline T get(G const&) {}
    //static inline void set(G& g, T const& value) {}
};

template <typename Point, typename CoordinateType, std::size_t Dimension>
struct access<point_tag, Point, CoordinateType, Dimension, std::false_type>
{
    static constexpr CoordinateType get(Point const& point)
    {
        return traits::access<Point, Dimension>::get(point);
    }
    static void set(Point& p, CoordinateType const& value)
    {
        traits::access<Point, Dimension>::set(p, value);
    }
};

template <typename Point, typename CoordinateType, std::size_t Dimension>
struct access<point_tag, Point, CoordinateType, Dimension, std::true_type>
{
    static constexpr CoordinateType get(Point const* point)
    {
        return traits::access<typename std::remove_pointer<Point>::type, Dimension>::get(*point);
    }
    static void set(Point* p, CoordinateType const& value)
    {
        traits::access<typename std::remove_pointer<Point>::type, Dimension>::set(*p, value);
    }
};


template
<
    typename Box,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<box_tag, Box, CoordinateType, Index, Dimension, std::false_type>
    : detail::indexed_access_non_pointer<Box, CoordinateType, Index, Dimension>
{};

template
<
    typename Box,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<box_tag, Box, CoordinateType, Index, Dimension, std::true_type>
    : detail::indexed_access_pointer<Box, CoordinateType, Index, Dimension>
{};


template
<
    typename Segment,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<segment_tag, Segment, CoordinateType, Index, Dimension, std::false_type>
    : detail::indexed_access_non_pointer<Segment, CoordinateType, Index, Dimension>
{};


template
<
    typename Segment,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<segment_tag, Segment, CoordinateType, Index, Dimension, std::true_type>
    : detail::indexed_access_pointer<Segment, CoordinateType, Index, Dimension>
{};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Two dummy tags to distinguish get/set variants below.
// They don't have to be specified by the user. The functions are distinguished
// by template signature also, but for e.g. GCC this is not enough. So give them
// a different signature.
struct signature_getset_dimension {};
struct signature_getset_index_dimension {};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Get coordinate value of a geometry (usually a point)
\details \details_get_set
\ingroup get
\tparam Dimension \tparam_dimension_required
\tparam Geometry \tparam_geometry (usually a Point Concept)
\param geometry \param_geometry (usually a point)
\return The coordinate value of specified dimension of specified geometry

\qbk{[include reference/core/get_point.qbk]}
*/
template <std::size_t Dimension, typename Geometry>
constexpr inline typename coordinate_type<Geometry>::type get(Geometry const& geometry
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        , detail::signature_getset_dimension* = 0
#endif
        )
{
    typedef core_dispatch::access
        <
            typename tag<Geometry>::type,
            typename util::remove_cptrref<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Dimension,
            typename std::is_pointer<Geometry>::type
        > coord_access_type;

    return coord_access_type::get(geometry);
}


/*!
\brief Set coordinate value of a geometry (usually a point)
\details \details_get_set
\tparam Dimension \tparam_dimension_required
\tparam Geometry \tparam_geometry (usually a Point Concept)
\param geometry geometry to assign coordinate to
\param geometry \param_geometry (usually a point)
\param value The coordinate value to set
\ingroup set

\qbk{[include reference/core/set_point.qbk]}
*/
template <std::size_t Dimension, typename Geometry>
inline void set(Geometry& geometry
        , typename coordinate_type<Geometry>::type const& value
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        , detail::signature_getset_dimension* = 0
#endif
        )
{
    typedef core_dispatch::access
        <
            typename tag<Geometry>::type,
            typename util::remove_cptrref<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Dimension,
            typename std::is_pointer<Geometry>::type
        > coord_access_type;

    coord_access_type::set(geometry, value);
}


/*!
\brief get coordinate value of a Box or Segment
\details \details_get_set
\tparam Index \tparam_index_required
\tparam Dimension \tparam_dimension_required
\tparam Geometry \tparam_box_or_segment
\param geometry \param_geometry
\return coordinate value
\ingroup get

\qbk{distinguish,with index}
\qbk{[include reference/core/get_box.qbk]}
*/
template <std::size_t Index, std::size_t Dimension, typename Geometry>
constexpr inline typename coordinate_type<Geometry>::type get(Geometry const& geometry
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        , detail::signature_getset_index_dimension* = 0
#endif
        )
{
    typedef core_dispatch::indexed_access
        <
            typename tag<Geometry>::type,
            typename util::remove_cptrref<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Index,
            Dimension,
            typename std::is_pointer<Geometry>::type
        > coord_access_type;

    return coord_access_type::get(geometry);
}

/*!
\brief set coordinate value of a Box / Segment
\details \details_get_set
\tparam Index \tparam_index_required
\tparam Dimension \tparam_dimension_required
\tparam Geometry \tparam_box_or_segment
\param geometry geometry to assign coordinate to
\param geometry \param_geometry
\param value The coordinate value to set
\ingroup set

\qbk{distinguish,with index}
\qbk{[include reference/core/set_box.qbk]}
*/
template <std::size_t Index, std::size_t Dimension, typename Geometry>
inline void set(Geometry& geometry
        , typename coordinate_type<Geometry>::type const& value
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        , detail::signature_getset_index_dimension* = 0
#endif
        )
{
    typedef core_dispatch::indexed_access
        <
            typename tag<Geometry>::type,
            typename util::remove_cptrref<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Index,
            Dimension,
            typename std::is_pointer<Geometry>::type
        > coord_access_type;

    coord_access_type::set(geometry, value);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_ACCESS_HPP

/* access.hpp
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
*/