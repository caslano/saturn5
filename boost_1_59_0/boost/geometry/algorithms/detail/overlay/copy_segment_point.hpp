// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENT_POINT_HPP


#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/views/detail/closed_clockwise_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace copy_segments
{

inline signed_size_type circular_offset(signed_size_type segment_count, signed_size_type index,
                                        signed_size_type offset)
{
    signed_size_type result = (index + offset) % segment_count;
    if (result < 0)
    {
       result += segment_count;
    }
    return result;
}

template <typename Range, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point_range
{
    static inline bool apply(Range const& range,
            SegmentIdentifier const& seg_id, signed_size_type offset,
            PointOut& point)
    {
        using view_type = detail::closed_clockwise_view
            <
                Range const,
                closure<Range>::value,
                Reverse ? counterclockwise : clockwise
            >;

        view_type view(range);

        std::size_t const segment_count = boost::size(view) - 1;
        signed_size_type const target = circular_offset(segment_count, seg_id.segment_index, offset);
        BOOST_GEOMETRY_ASSERT(target >= 0
                           && std::size_t(target) < boost::size(view));

        geometry::convert(range::at(view, target), point);

        return true;
    }
};


template <typename Polygon, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point_polygon
{
    static inline bool apply(Polygon const& polygon,
            SegmentIdentifier const& seg_id, signed_size_type offset,
            PointOut& point)
    {
        // Call ring-version with the right ring
        return copy_segment_point_range
            <
                typename geometry::ring_type<Polygon>::type,
                Reverse,
                SegmentIdentifier,
                PointOut
            >::apply
                (
                    seg_id.ring_index < 0
                        ? geometry::exterior_ring(polygon)
                        : range::at(geometry::interior_rings(polygon), seg_id.ring_index),
                    seg_id, offset,
                    point
                );
    }
};


template <typename Box, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point_box
{
    static inline bool apply(Box const& box,
            SegmentIdentifier const& seg_id, signed_size_type offset,
            PointOut& point)
    {
        boost::array<typename point_type<Box>::type, 4> bp;
        assign_box_corners_oriented<Reverse>(box, bp);

        signed_size_type const target = circular_offset(4, seg_id.segment_index, offset);
        BOOST_GEOMETRY_ASSERT(target >= 0
                           && std::size_t(target) < bp.size());

        point = bp[target];
        return true;
    }
};


template
<
    typename MultiGeometry,
    typename SegmentIdentifier,
    typename PointOut,
    typename Policy
>
struct copy_segment_point_multi
{
    static inline bool apply(MultiGeometry const& multi,
                             SegmentIdentifier const& seg_id, signed_size_type offset,
                             PointOut& point)
    {
        BOOST_GEOMETRY_ASSERT(seg_id.multi_index >= 0
               && std::size_t(seg_id.multi_index) < boost::size(multi));

        // Call the single-version
        return Policy::apply(range::at(multi, seg_id.multi_index), seg_id, offset, point);
    }
};


}} // namespace detail::copy_segments
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Tag,
    typename GeometryIn,
    bool Reverse,
    typename SegmentIdentifier,
    typename PointOut
>
struct copy_segment_point
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not or not yet implemented for this Geometry type.",
        Tag, GeometryIn);
};


template <typename LineString, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point<linestring_tag, LineString, Reverse, SegmentIdentifier, PointOut>
    : detail::copy_segments::copy_segment_point_range
        <
            LineString, Reverse, SegmentIdentifier, PointOut
        >
{};


template <typename Ring, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point<ring_tag, Ring, Reverse, SegmentIdentifier, PointOut>
    : detail::copy_segments::copy_segment_point_range
        <
            Ring, Reverse, SegmentIdentifier, PointOut
        >
{};

template <typename Polygon, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point<polygon_tag, Polygon, Reverse, SegmentIdentifier, PointOut>
    : detail::copy_segments::copy_segment_point_polygon
        <
            Polygon, Reverse, SegmentIdentifier, PointOut
        >
{};


template <typename Box, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point<box_tag, Box, Reverse, SegmentIdentifier, PointOut>
    : detail::copy_segments::copy_segment_point_box
        <
            Box, Reverse, SegmentIdentifier, PointOut
        >
{};


template
<
    typename MultiGeometry,
    bool Reverse,
    typename SegmentIdentifier,
    typename PointOut
>
struct copy_segment_point
    <
        multi_polygon_tag,
        MultiGeometry,
        Reverse,
        SegmentIdentifier,
        PointOut
    >
    : detail::copy_segments::copy_segment_point_multi
        <
            MultiGeometry,
            SegmentIdentifier,
            PointOut,
            detail::copy_segments::copy_segment_point_polygon
                <
                    typename boost::range_value<MultiGeometry>::type,
                    Reverse,
                    SegmentIdentifier,
                    PointOut
                >
        >
{};

template
<
    typename MultiGeometry,
    bool Reverse,
    typename SegmentIdentifier,
    typename PointOut
>
struct copy_segment_point
    <
        multi_linestring_tag,
        MultiGeometry,
        Reverse,
        SegmentIdentifier,
        PointOut
    >
    : detail::copy_segments::copy_segment_point_multi
        <
            MultiGeometry,
            SegmentIdentifier,
            PointOut,
            detail::copy_segments::copy_segment_point_range
                <
                    typename boost::range_value<MultiGeometry>::type,
                    Reverse,
                    SegmentIdentifier,
                    PointOut
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
    \brief Helper function, copies a point from a segment
    \ingroup overlay
 */
template<bool Reverse, typename Geometry, typename SegmentIdentifier, typename PointOut>
inline bool copy_segment_point(Geometry const& geometry,
            SegmentIdentifier const& seg_id, signed_size_type offset,
            PointOut& point_out)
{
    concepts::check<Geometry const>();

    return dispatch::copy_segment_point
        <
            typename tag<Geometry>::type,
            Geometry,
            Reverse,
            SegmentIdentifier,
            PointOut
        >::apply(geometry, seg_id, offset, point_out);
}


/*!
    \brief Helper function, to avoid the same construct several times,
        copies a point, based on a source-index and two geometries
    \ingroup overlay
 */
template
<
    bool Reverse1, bool Reverse2,
    typename Geometry1, typename Geometry2,
    typename SegmentIdentifier,
    typename PointOut
>
inline bool copy_segment_point(Geometry1 const& geometry1, Geometry2 const& geometry2,
            SegmentIdentifier const& seg_id, signed_size_type offset,
            PointOut& point_out)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    BOOST_GEOMETRY_ASSERT(seg_id.source_index == 0 || seg_id.source_index == 1);

    if (seg_id.source_index == 0)
    {
        return dispatch::copy_segment_point
            <
                typename tag<Geometry1>::type,
                Geometry1,
                Reverse1,
                SegmentIdentifier,
                PointOut
            >::apply(geometry1, seg_id, offset, point_out);
    }
    else if (seg_id.source_index == 1)
    {
        return dispatch::copy_segment_point
            <
                typename tag<Geometry2>::type,
                Geometry2,
                Reverse2,
                SegmentIdentifier,
                PointOut
            >::apply(geometry2, seg_id, offset, point_out);
    }
    // Exception?
    return false;
}


/*!
    \brief Helper function, to avoid the same construct several times,
        copies a point, based on a source-index and two geometries
    \ingroup overlay
 */
template
<
    bool Reverse1, bool Reverse2,
    typename Geometry1, typename Geometry2,
    typename SegmentIdentifier,
    typename PointOut
>
inline bool copy_segment_points(Geometry1 const& geometry1, Geometry2 const& geometry2,
            SegmentIdentifier const& seg_id,
            PointOut& point1, PointOut& point2)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return copy_segment_point<Reverse1, Reverse2>(geometry1, geometry2, seg_id, 0, point1)
        && copy_segment_point<Reverse1, Reverse2>(geometry1, geometry2, seg_id, 1, point2);
}

/*!
    \brief Helper function, copies three points: two from the specified segment
    (from, to) and the next one
    \ingroup overlay
 */
template
<
    bool Reverse1, bool Reverse2,
    typename Geometry1, typename Geometry2,
    typename SegmentIdentifier,
    typename PointOut
>
inline bool copy_segment_points(Geometry1 const& geometry1, Geometry2 const& geometry2,
            SegmentIdentifier const& seg_id,
            PointOut& point1, PointOut& point2, PointOut& point3)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return copy_segment_point<Reverse1, Reverse2>(geometry1, geometry2, seg_id, 0, point1)
        && copy_segment_point<Reverse1, Reverse2>(geometry1, geometry2, seg_id, 1, point2)
        && copy_segment_point<Reverse1, Reverse2>(geometry1, geometry2, seg_id, 2, point3);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENT_POINT_HPP

/* copy_segment_point.hpp
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
*/