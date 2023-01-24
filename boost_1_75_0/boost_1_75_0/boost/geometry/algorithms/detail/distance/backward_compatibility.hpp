// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>
#include <boost/geometry/algorithms/detail/distance/point_to_geometry.hpp>
#include <boost/geometry/algorithms/detail/distance/multipoint_to_geometry.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template<typename Point, typename Segment, typename Strategy>
struct point_to_segment
{
    static inline typename strategy::distance::services::return_type
        <
            Strategy,
            Point,
            typename point_type<Segment>::type
        >::type
    apply(Point const& point, Segment const& segment, Strategy const& )
    {
        typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Segment>::type,
                Strategy
            >::type segment_strategy;

        typename point_type<Segment>::type p[2];
        geometry::detail::assign_point_from_index<0>(segment, p[0]);
        geometry::detail::assign_point_from_index<1>(segment, p[1]);
        return segment_strategy.apply(point, p[0], p[1]);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Point-segment version 1, with point-point strategy
template <typename Point, typename Segment, typename Strategy>
struct distance
<
    Point, Segment, Strategy,
    point_tag, segment_tag, strategy_tag_distance_point_point,
    false
> : detail::distance::point_to_segment<Point, Segment, Strategy>
{};


// Point-line version 1, where point-point strategy is specified
template <typename Point, typename Linestring, typename Strategy>
struct distance
<
    Point, Linestring, Strategy,
    point_tag, linestring_tag, strategy_tag_distance_point_point,
    false
>
{

    static inline typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Linestring>::type
        >::type
    apply(Point const& point,
          Linestring const& linestring,
          Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
                    <
                        Point,
                        typename point_type<Linestring>::type,
                        Strategy
                    >::type ps_strategy_type;

        return detail::distance::point_to_range
            <
                Point, Linestring, closed, ps_strategy_type
            >::apply(point, linestring, ps_strategy_type());
    }
};


// Point-ring , where point-point strategy is specified
template <typename Point, typename Ring, typename Strategy>
struct distance
<
    Point, Ring, Strategy,
    point_tag, ring_tag, strategy_tag_distance_point_point,
    false
>
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Ring>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
            Ring const& ring,
            Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Ring>::type,
                Strategy
            >::type ps_strategy_type;

        return detail::distance::point_to_ring
            <
                Point, Ring,
                geometry::closure<Ring>::value,
                ps_strategy_type
            >::apply(point, ring, ps_strategy_type());
    }
};


// Point-polygon , where point-point strategy is specified
template <typename Point, typename Polygon, typename Strategy>
struct distance
<
    Point, Polygon, Strategy,
    point_tag, polygon_tag, strategy_tag_distance_point_point,
    false
>
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Polygon>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    Polygon const& polygon,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Polygon>::type,
                Strategy
            >::type ps_strategy_type;

        return detail::distance::point_to_polygon
            <
                Point,
                Polygon,
                geometry::closure<Polygon>::value,
                ps_strategy_type
            >::apply(point, polygon, ps_strategy_type());
    }
};




template
<
    typename Point,
    typename MultiGeometry,
    typename MultiGeometryTag,
    typename Strategy
>
struct distance
    <
        Point, MultiGeometry, Strategy,
        point_tag, MultiGeometryTag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<MultiGeometry>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    MultiGeometry const& multigeometry,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<MultiGeometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                Point, MultiGeometry, ps_strategy_type,
                point_tag, MultiGeometryTag,
                strategy_tag_distance_point_segment, false
            >::apply(point, multigeometry, ps_strategy_type());
    }
};


template
<
    typename Geometry,
    typename MultiPoint,
    typename GeometryTag,
    typename Strategy
>
struct distance
    <
        Geometry, MultiPoint, Strategy,
        GeometryTag, multi_point_tag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint>::type,
            typename point_type<Geometry>::type
        >::type return_type;

    static inline return_type apply(Geometry const& geometry,
                                    MultiPoint const& multipoint,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                typename point_type<MultiPoint>::type,
                typename point_type<Geometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                Geometry, MultiPoint, ps_strategy_type,
                GeometryTag, multi_point_tag,
                strategy_tag_distance_point_segment, false
            >::apply(geometry, multipoint, ps_strategy_type());
    }
};


template
<
    typename MultiPoint,
    typename MultiGeometry,
    typename MultiGeometryTag,
    typename Strategy
>
struct distance
    <
        MultiPoint, MultiGeometry, Strategy,
        multi_point_tag, MultiGeometryTag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint>::type, 
            typename point_type<MultiGeometry>::type
        >::type return_type;

    static inline return_type apply(MultiPoint const& multipoint,
                                    MultiGeometry const& multigeometry,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                typename point_type<MultiPoint>::type,
                typename point_type<MultiGeometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                MultiPoint, MultiGeometry, ps_strategy_type,
                multi_point_tag, MultiGeometryTag,
                strategy_tag_distance_point_segment, false
            >::apply(multipoint, multigeometry, ps_strategy_type());
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP

/* backward_compatibility.hpp
fHqJp1x3XNjXt0LlOJQ3U8/VaaIVd8+H2FWQCLEg5jP8aV4+nrIIPD7Liq8ZAIsqS/K/iLukfLlILdNmihjmKgpEZMYwM7pxA9ANf49YlMgJgX04HCqLofzkRHc9uEPjbXe7tiDse2gFQwz5oeWEpQGkQGantKJL+IK0Tt6orFYnaGX6PKPO/amnwijWK7WE6pZXwMgZXh73u9FVavw0mF97H3vg7RMiBjd7TAh9BI1+v+Pr8Jp17+a02TloAdHP46VkKovtrcUJmuOL4V2FkC8e7BWztPx3Ym7GQeVRKG9CCfK8xWJu4Nmp20xK85kQ2HM8mSB3FeEGVRvw2Uh8O4e6OsX/DEuXvF7fMehc8flP0/H7Axd+l7IedDXMzjFX8tV+c3LQ4izxYCGM82H5Xhf7EP9HTsNKqZqrrRWgEnFvg+cpbSjxTcHyZAbSHJUjIIqO93l6W8+xdrGei9op7tF+sgn3+E61+Z1J7XzNm9hVfchjK9ptZ+r90PhFOz9Tt7Y7z9QnXfJFmjx1LJll2aoCyA28Rndd9cV2wW+8CZUvdYTRiA5TV91pYjlanjddNj7Swka32bXShK76Kx3WOUSBWHcbsTP4vBSXixS6q8r0MqPSfU02PsKwQieJOGK+RqmNZkNP+a+Dyn+01zu5vAyLGPhIh7xDv7cLvpI4CJdnoFzqYPYUupuSbE8lG9XFKkqyGLYXbUPshFUw
*/