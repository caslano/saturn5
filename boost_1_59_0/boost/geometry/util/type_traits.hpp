// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_TYPE_TRAITS_HPP
#define BOOST_GEOMETRY_UTIL_TYPE_TRAITS_HPP


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry
{


namespace util
{


template <typename T>
struct is_geometry
    : bool_constant<! std::is_void<typename tag<T>::type>::value>
{};

template <typename T>
struct is_not_geometry
    : std::is_void<typename tag<T>::type>
{};

template <typename T>
struct is_point
    : std::is_same<point_tag, typename tag<T>::type>
{};

template <typename T>
struct is_multi_point
    : std::is_same<multi_point_tag, typename tag<T>::type>
{};

template <typename T>
struct is_pointlike
    : std::is_base_of<pointlike_tag, typename tag<T>::type>
{};


template <typename T>
struct is_segment
    : std::is_same<segment_tag, typename tag<T>::type>
{};

template <typename T>
struct is_linestring
    : std::is_same<linestring_tag, typename tag<T>::type>
{};

template <typename T>
struct is_multi_linestring
    : std::is_same<multi_linestring_tag, typename tag<T>::type>
{};

template <typename T>
struct is_polylinear
    : std::is_base_of<polylinear_tag, typename tag<T>::type>
{};

template <typename T>
struct is_linear
    : std::is_base_of<linear_tag, typename tag<T>::type>
{};


template <typename T>
struct is_box
    : std::is_same<box_tag, typename tag<T>::type>
{};

template <typename T>
struct is_ring
    : std::is_same<ring_tag, typename tag<T>::type>
{};

template <typename T>
struct is_polygon
    : std::is_same<polygon_tag, typename tag<T>::type>
{};

template <typename T>
struct is_multi_polygon
    : std::is_same<multi_polygon_tag, typename tag<T>::type>
{};

template <typename T>
struct is_polygonal
    : std::is_base_of<polygonal_tag, typename tag<T>::type>
{};

template <typename T>
struct is_areal
    : std::is_base_of<areal_tag, typename tag<T>::type>
{};


template <typename T>
struct is_segmental
    : bool_constant<is_linear<T>::value || is_polygonal<T>::value>
{};

template <typename T>
struct is_polysegmental
    : bool_constant<is_polylinear<T>::value || is_polygonal<T>::value>
{};


template <typename T>
struct is_multi
    : std::is_base_of<multi_tag, typename tag<T>::type>
{};


template <typename T>
struct is_multi_element
    : bool_constant<is_point<T>::value || is_linestring<T>::value || is_polygon<T>::value>
{};


template <typename T>
struct is_single
    : std::is_base_of<single_tag, typename tag<T>::type>
{};


template <typename T>
struct is_geometry_collection
    : std::is_same<geometry_collection_tag, typename tag<T>::type>
{};


template <typename T>
struct is_dynamic_geometry
    : std::is_same<dynamic_geometry_tag, typename tag<T>::type>
{};


template <typename Geometry, typename T = void>
struct enable_if_point
    : std::enable_if<is_point<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_point_t = typename enable_if_point<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_multi_point
    : std::enable_if<is_multi_point<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_multi_point_t = typename enable_if_multi_point<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_pointlike
    : std::enable_if<is_pointlike<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_pointlike_t = typename enable_if_pointlike<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_segment
    : std::enable_if<is_segment<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_segment_t = typename enable_if_segment<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_linestring
    : std::enable_if<is_linestring<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_linestring_t = typename enable_if_linestring<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_multi_linestring
    : std::enable_if<is_multi_linestring<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_multi_linestring_t = typename enable_if_multi_linestring<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polylinear
    : std::enable_if<is_polylinear<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polylinear_t = typename enable_if_polylinear<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_linear
    : std::enable_if<is_linear<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_linear_t = typename enable_if_linear<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_box
    : std::enable_if<is_box<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_box_t = typename enable_if_box<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_ring
    : std::enable_if<is_ring<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_ring_t = typename enable_if_ring<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_polygon
    : std::enable_if<is_polygon<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polygon_t = typename enable_if_polygon<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_multi_polygon
    : std::enable_if<is_multi_polygon<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_multi_polygon_t = typename enable_if_multi_polygon<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polygonal
    : std::enable_if<is_polygonal<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polygonal_t = typename enable_if_polygonal<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_areal
    : std::enable_if<is_areal<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_areal_t = typename enable_if_areal<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polysegmental
    : std::enable_if<is_polysegmental<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polysegmental_t = typename enable_if_polysegmental<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_dynamic_geometry
    : std::enable_if<is_dynamic_geometry<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_dynamic_geometry_t = typename enable_if_dynamic_geometry<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_geometry_collection
    : std::enable_if<is_geometry_collection<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_geometry_collection_t = typename enable_if_geometry_collection<Geometry, T>::type;


} // namespace util


// Deprecated utilities, defined for backward compatibility but might be
// removed in the future.


/*!
    \brief Meta-function defining "true" for areal types (box, (multi)polygon, ring),
    \note Used for tag dispatching and meta-function finetuning
    \note Also a "ring" has areal properties within Boost.Geometry
    \ingroup core
*/
using util::is_areal;


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DETAIL_HPP

/* type_traits.hpp
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
*/