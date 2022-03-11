// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENT_POINT_HPP


#include <boost/array.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/iterators/ever_circling_iterator.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/reversible_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace copy_segments
{


template <typename Range, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point_range
{
    static inline bool apply(Range const& range,
            SegmentIdentifier const& seg_id, int offset,
            PointOut& point)
    {
        typedef typename closeable_view
        <
            Range const,
            closure<Range>::value
        >::type cview_type;

        typedef typename reversible_view
        <
            cview_type const,
            Reverse ? iterate_reverse : iterate_forward
        >::type rview_type;

        cview_type cview(range);
        rview_type view(cview);

        typedef typename boost::range_iterator<rview_type>::type iterator;
        geometry::ever_circling_iterator<iterator> it(boost::begin(view), boost::end(view),
                    boost::begin(view) + seg_id.segment_index, true);

        for (signed_size_type i = 0; i < offset; ++i, ++it)
        {
        }

        geometry::convert(*it, point);
        return true;
    }
};


template <typename Polygon, bool Reverse, typename SegmentIdentifier, typename PointOut>
struct copy_segment_point_polygon
{
    static inline bool apply(Polygon const& polygon,
            SegmentIdentifier const& seg_id, int offset,
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
            SegmentIdentifier const& seg_id, int offset,
            PointOut& point)
    {
        signed_size_type index = seg_id.segment_index;
        for (int i = 0; i < offset; i++)
        {
            index++;
        }

        boost::array<typename point_type<Box>::type, 4> bp;
        assign_box_corners_oriented<Reverse>(box, bp);
        point = bp[index % 4];
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
                             SegmentIdentifier const& seg_id, int offset,
                             PointOut& point)
    {

        BOOST_GEOMETRY_ASSERT
            (
                seg_id.multi_index >= 0
                && seg_id.multi_index < int(boost::size(multi))
            );

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
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<GeometryIn>)
        );
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
            SegmentIdentifier const& seg_id, int offset,
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
            SegmentIdentifier const& seg_id, int offset,
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