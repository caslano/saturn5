// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP

#include <cstddef>

#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/type_traits_std.hpp>

namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace num_points
{


template <bool AddForOpen>
struct range_count
{
    template <typename Range>
    static inline std::size_t apply(Range const& range)
    {
        std::size_t n = boost::size(range);
        if (AddForOpen
            && n > 0
            && geometry::closure<Range>::value == open
            )
        {
            return n + 1;
        }
        return n;
    }
};

}} // namespace detail::num_points
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    bool AddForOpen,
    typename Tag = typename tag_cast
        <
            typename tag<Geometry>::type, multi_tag
        >::type
>
struct num_points: not_implemented<Tag>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, point_tag>
    : detail::counting::other_count<1>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, box_tag>
    : detail::counting::other_count<(1 << geometry::dimension<Geometry>::value)>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, segment_tag>
    : detail::counting::other_count<2>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, linestring_tag>
    : detail::num_points::range_count<AddForOpen>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, ring_tag>
    : detail::num_points::range_count<AddForOpen>
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, polygon_tag>
    : detail::counting::polygon_count
        <
            detail::num_points::range_count<AddForOpen>
        >
{};

template <typename Geometry, bool AddForOpen>
struct num_points<Geometry, AddForOpen, multi_tag>
    : detail::counting::multi_count
        <
            num_points<typename boost::range_value<Geometry>::type, AddForOpen>
        >
{};

} // namespace dispatch
#endif


namespace resolve_dynamic
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct num_points
{
    static inline std::size_t apply(Geometry const& geometry, bool add_for_open)
    {
        concepts::check<Geometry const>();

        return add_for_open
             ? dispatch::num_points<Geometry, true>::apply(geometry)
             : dispatch::num_points<Geometry, false>::apply(geometry);
    }
};

template <typename Geometry>
struct num_points<Geometry, dynamic_geometry_tag>
{
    static inline std::size_t apply(Geometry const& geometry, bool add_for_open)
    {
        std::size_t result = 0;
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            result = num_points<util::remove_cref_t<decltype(g)>>::apply(g, add_for_open);
        }, geometry);
        return result;
    }
};


template <typename Geometry>
struct num_points<Geometry, geometry_collection_tag>
{
    static inline std::size_t apply(Geometry const& geometry, bool add_for_open)
    {
        std::size_t result = 0;
        detail::visit_breadth_first([&](auto const& g)
        {
            result += num_points<util::remove_cref_t<decltype(g)>>::apply(g, add_for_open);
            return true;
        }, geometry);
        return result;
    }
};


} // namespace resolve_dynamic


/*!
\brief \brief_calc{number of points}
\ingroup num_points
\details \details_calc{num_points, number of points}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\param add_for_open add one for open geometries (i.e. polygon types which are not closed)
\return \return_calc{number of points}

\qbk{[include reference/algorithms/num_points.qbk]}
*/
template <typename Geometry>
inline std::size_t num_points(Geometry const& geometry, bool add_for_open = false)
{
    return resolve_dynamic::num_points<Geometry>::apply(geometry, add_for_open);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_POINTS_HPP

/* num_points.hpp
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
*/