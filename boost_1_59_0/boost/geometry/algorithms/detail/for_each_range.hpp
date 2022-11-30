// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_FOR_EACH_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_FOR_EACH_RANGE_HPP


#include <type_traits>
#include <utility>

#include <boost/concept/requires.hpp>
#include <boost/core/addressof.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/type_traits.hpp>

#include <boost/geometry/views/box_view.hpp>
#include <boost/geometry/views/segment_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace for_each
{


template <typename Point>
struct fe_range_point
{
    template <typename Functor>
    static inline bool apply(Point& point, Functor&& f)
    {
        Point* ptr = boost::addressof(point);
        return f(std::pair<Point*, Point*>(ptr, ptr + 1));
    }
};


template <typename Segment>
struct fe_range_segment
{
    template <typename Functor>
    static inline bool apply(Segment& segment, Functor&& f)
    {
        return f(segment_view<typename std::remove_const<Segment>::type>(segment));
    }
};


template <typename Range>
struct fe_range_range
{
    template <typename Functor>
    static inline bool apply(Range& range, Functor&& f)
    {
        return f(range);
    }
};


template <typename Polygon>
struct fe_range_polygon
{
    template <typename Functor>
    static inline bool apply(Polygon& polygon, Functor&& f)
    {
        return f(exterior_ring(polygon));

        // TODO: If some flag says true, also do the inner rings.
        // for convex hull, it's not necessary
    }
};

template <typename Box>
struct fe_range_box
{
    template <typename Functor>
    static inline bool apply(Box& box, Functor&& f)
    {
        return f(box_view<typename std::remove_const<Box>::type>(box));
    }
};

template <typename Multi, typename SinglePolicy>
struct fe_range_multi
{
    template <typename Functor>
    static inline bool apply(Multi& multi, Functor&& f)
    {
        auto const end = boost::end(multi);
        for (auto it = boost::begin(multi); it != end; ++it)
        {
            if (! SinglePolicy::apply(*it, f))
            {
                return false;
            }
        }
        return true;
    }
};

}} // namespace detail::for_each
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct for_each_range
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not or not yet implemented for this Geometry type.",
        Geometry, Tag);
};


template <typename Point>
struct for_each_range<Point, point_tag>
    : detail::for_each::fe_range_point<Point>
{};


template <typename Segment>
struct for_each_range<Segment, segment_tag>
    : detail::for_each::fe_range_segment<Segment>
{};


template <typename Linestring>
struct for_each_range<Linestring, linestring_tag>
    : detail::for_each::fe_range_range<Linestring>
{};


template <typename Ring>
struct for_each_range<Ring, ring_tag>
    : detail::for_each::fe_range_range<Ring>
{};


template <typename Polygon>
struct for_each_range<Polygon, polygon_tag>
    : detail::for_each::fe_range_polygon<Polygon>
{};


template <typename Box>
struct for_each_range<Box, box_tag>
    : detail::for_each::fe_range_box<Box>
{};


template <typename MultiPoint>
struct for_each_range<MultiPoint, multi_point_tag>
    : detail::for_each::fe_range_range<MultiPoint>
{};


template <typename Geometry>
struct for_each_range<Geometry, multi_linestring_tag>
    : detail::for_each::fe_range_multi
        <
            Geometry,
            detail::for_each::fe_range_range
                <
                    util::transcribe_const_t
                        <
                            Geometry,
                            typename boost::range_value<Geometry>::type
                        >
                >
        >
{};


template <typename Geometry>
struct for_each_range<Geometry, multi_polygon_tag>
    : detail::for_each::fe_range_multi
        <
            Geometry,
            detail::for_each::fe_range_polygon
                <
                    util::transcribe_const_t
                        <
                            Geometry,
                            typename boost::range_value<Geometry>::type
                        >
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

namespace detail
{


// Currently for Polygons p is checked only for exterior ring
// Should this function be renamed?
template <typename Geometry, typename UnaryPredicate>
inline bool all_ranges_of(Geometry const& geometry, UnaryPredicate p)
{
    return dispatch::for_each_range<Geometry const>::apply(geometry, p);
}


// Currently for Polygons p is checked only for exterior ring
// Should this function be renamed?
template <typename Geometry, typename UnaryPredicate>
inline bool any_range_of(Geometry const& geometry, UnaryPredicate p)
{
    return ! dispatch::for_each_range<Geometry const>::apply(geometry,
                [&](auto&& range)
                {
                    return ! p(range);
                });
}


// Currently for Polygons p is checked only for exterior ring
// Should this function be renamed?
template <typename Geometry, typename UnaryPredicate>
inline bool none_range_of(Geometry const& geometry, UnaryPredicate p)
{
    return dispatch::for_each_range<Geometry const>::apply(geometry,
                [&](auto&& range)
                {
                    return ! p(range);
                });
}


// Currently for Polygons f is called only for exterior ring
// Should this function be renamed?
template <typename Geometry, typename Functor>
inline Functor for_each_range(Geometry const& geometry, Functor f)
{
    dispatch::for_each_range<Geometry const>::apply(geometry,
        [&](auto&& range)
        {
            f(range);
            // TODO: Implement separate function?
            return true;
        });
    return f;
}


}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_FOR_EACH_RANGE_HPP

/* for_each_range.hpp
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
*/