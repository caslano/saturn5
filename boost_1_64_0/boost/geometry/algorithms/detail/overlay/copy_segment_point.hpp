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
L43nig+C7D6v0+fwmGnzi46PyO9abSyRwTND7nVsnfa5R4LseuPUMeR8Vu1N7WfHV4T4/ihyCTkfGZCRvmf0XO+dE0m+ZFBZWxuGjGlADnn9ntln+J6YQL5PTiW1r46+aoex87eCyMh9k7JrVw4/p3fOu3L4PdrvE3MF+u69+nlSW/tqc0x6fQ6PYW6f+hujrau1YSneQVv3ZCjoWe55vaz79Mf4BGVqaVsu116rTwXIzP2Tsmmfn8vc4J409JScghv1xXXb02ir9tW43juivU+ba+fwu2cdDJ/zOdWxpX5uqx0rosgrP9mW0N5s+uDcHizMRa7p9DU9ObonT8hnZufSaIffjau/HRj41LYM+psL7htC9rZrGBe/l9L31IEx0KfIwDi4N/zeHOSYzfNcP1Xbm7p/dF19yqIvuRxP5zgG4EWsiw30y/hA34Pt7qvh+c75m6eenc01fl6GFZjkeX4GnfLOmc7vMQ+D6p6RKaA7xriEvoXfn8s9abXHz64NCqT3s9/L53TOZwmUyYRoMsuhv64P/N7QeOwL25EoIE9ruuWeCdkC95BBBu8oQDb61DYn2YdtQLh94X5UCuiFsQDdD46G9RlHPfeHlM/PXN+rkLFL5Zhr1l2rXTkDeYRnhscoY0AHvds7RufwrCjvz+6aNIFapH7U1p+sZBX8mgIZ3OP4Sc9c7do96ck5lzb7pBvBNs9+Pb97Xdcxn/FsoC0+95TVjpD73FMjb2DOOVfXsaraWcp7PY8OBPeF7W9AfwrprzbNQVWypxN+91yMSE0mYb0N29bs+ptV212TpYDrw2ORNzBG7nPNgNzOFfOZJnCfY86lzRGwA2TuPrY4GJLOZwipXafdMY6VqOQa92RwbGZ4fkaSfURgbjifWjthjgd9kcd1Cak9V/99RdAYa2d6/YnycybPd25hlHM+y2ckF+fMc3+3iDydZxe1y/PzBeaKPmQgI2PFptBH7y4TkLWfC7INIf123wAyru05rmGrzLsb9TmeLHL7vaJ2u4Yd83eQtMu9vciZT2G7XJfW+bwoHzjmHFxDB/TNZ8uwfMPPidKHcL8i6XLIsyKcjyTPKLKO9Cwy5xuMDb1Kr81+jk7tnE92w7zWzkzOZ9PuHOxUWAeL6E+M/mpD27Avzao/tV2fJnAj3StHf1zLhwZlSnhmSD/D8kitfWG7n801PvmIoPxkfdQf/gDGIKt3okwW59wzM3fAPrk+Z8BG+70QvcvvvSUD/lSbw+8pH2i/PqULjI3rMwXa6h73rssYGAdy0o6OWTSvVGD86T8aun5bpPaEx9i5piHn9Y/NCyakArKk93tG7ckQsAVkE/ZPefQnrc9MAT/h2dlc18iYu25hcb+TSS/HDxbSnlh6Fo5LPJPNCvp6z56snpXDuLg+zvEMYVuS2rmwrXENOxCkxdSwP8noXFiOeQPy9Tz3T3SsbZ2A/ukzm+Sd+uS8MdF/flSfswfGVf98zqPLgfkT5d7D3sfuB7VzaxduK6UPnr9BH7xfTOF5Yd8HehP8HGGcIo1JJnKNJM8MgTnjWZHmlvveCjwnjbYG7g/52ac/teNTO123B20jtR/lsSFsiyPdn5GMwr4gpP8+10UG/LZnutf97vP+wLik8n9ZA/5Wn64lj1SerQ3ilMA7zVfPCxwjB78rRvpO+Gue/YBzfl2V2rXohM7oggR0RTck4mZ0Rw/0RC8koTf6oC+S0Q/9MQADMQiDMQRDMQzDMQIjcQtGYTTGYCxuxW0Yh9sxHhNwB+7EXZiIu3EP7sV9uB8P4EFMwmQ8hCmYiml4GNPxCB7FY5iBmXgcszAbczAXT+BJzMN8LMBTWIhFWIwlWBGWOe7HA3g=
*/