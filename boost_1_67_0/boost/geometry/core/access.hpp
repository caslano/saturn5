// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_ACCESS_HPP
#define BOOST_GEOMETRY_CORE_ACCESS_HPP


#include <cstddef>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/util/bare_type.hpp>


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
   BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE, (types<Geometry>)
        );
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
    static inline CoordinateType get(Geometry const& geometry)
    {
        return traits::indexed_access<Geometry, Index, Dimension>::get(geometry);
    }
    static inline void set(Geometry& b, CoordinateType const& value)
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
    static inline CoordinateType get(Geometry const* geometry)
    {
        return traits::indexed_access<typename boost::remove_pointer<Geometry>::type, Index, Dimension>::get(*geometry);
    }
    static inline void set(Geometry* geometry, CoordinateType const& value)
    {
        traits::indexed_access<typename boost::remove_pointer<Geometry>::type, Index, Dimension>::set(*geometry, value);
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
struct access<point_tag, Point, CoordinateType, Dimension, boost::false_type>
{
    static inline CoordinateType get(Point const& point)
    {
        return traits::access<Point, Dimension>::get(point);
    }
    static inline void set(Point& p, CoordinateType const& value)
    {
        traits::access<Point, Dimension>::set(p, value);
    }
};

template <typename Point, typename CoordinateType, std::size_t Dimension>
struct access<point_tag, Point, CoordinateType, Dimension, boost::true_type>
{
    static inline CoordinateType get(Point const* point)
    {
        return traits::access<typename boost::remove_pointer<Point>::type, Dimension>::get(*point);
    }
    static inline void set(Point* p, CoordinateType const& value)
    {
        traits::access<typename boost::remove_pointer<Point>::type, Dimension>::set(*p, value);
    }
};


template
<
    typename Box,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<box_tag, Box, CoordinateType, Index, Dimension, boost::false_type>
    : detail::indexed_access_non_pointer<Box, CoordinateType, Index, Dimension>
{};

template
<
    typename Box,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<box_tag, Box, CoordinateType, Index, Dimension, boost::true_type>
    : detail::indexed_access_pointer<Box, CoordinateType, Index, Dimension>
{};


template
<
    typename Segment,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<segment_tag, Segment, CoordinateType, Index, Dimension, boost::false_type>
    : detail::indexed_access_non_pointer<Segment, CoordinateType, Index, Dimension>
{};


template
<
    typename Segment,
    typename CoordinateType,
    std::size_t Index,
    std::size_t Dimension
>
struct indexed_access<segment_tag, Segment, CoordinateType, Index, Dimension, boost::true_type>
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
inline typename coordinate_type<Geometry>::type get(Geometry const& geometry
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        , detail::signature_getset_dimension* dummy = 0
#endif
        )
{
    boost::ignore_unused(dummy);

    typedef core_dispatch::access
        <
            typename tag<Geometry>::type,
            typename geometry::util::bare_type<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Dimension,
            typename boost::is_pointer<Geometry>::type
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
        , detail::signature_getset_dimension* dummy = 0
#endif
        )
{
    boost::ignore_unused(dummy);

    typedef core_dispatch::access
        <
            typename tag<Geometry>::type,
            typename geometry::util::bare_type<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Dimension,
            typename boost::is_pointer<Geometry>::type
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
inline typename coordinate_type<Geometry>::type get(Geometry const& geometry
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        , detail::signature_getset_index_dimension* dummy = 0
#endif
        )
{
    boost::ignore_unused(dummy);

    typedef core_dispatch::indexed_access
        <
            typename tag<Geometry>::type,
            typename geometry::util::bare_type<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Index,
            Dimension,
            typename boost::is_pointer<Geometry>::type
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
        , detail::signature_getset_index_dimension* dummy = 0
#endif
        )
{
    boost::ignore_unused(dummy);

    typedef core_dispatch::indexed_access
        <
            typename tag<Geometry>::type,
            typename geometry::util::bare_type<Geometry>::type,
            typename coordinate_type<Geometry>::type,
            Index,
            Dimension,
            typename boost::is_pointer<Geometry>::type
        > coord_access_type;

    coord_access_type::set(geometry, value);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_ACCESS_HPP

/* access.hpp
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
*/