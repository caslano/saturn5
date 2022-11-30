// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_POINT_TO_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_POINT_TO_GEOMETRY_HPP

#include <iterator>
#include <type_traits>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/closest_feature/geometry_to_range.hpp>
#include <boost/geometry/algorithms/detail/closest_feature/point_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/iterator_selector.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/relate/services.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_points
{

struct point_to_point
{
    template <typename P1, typename P2, typename Segment, typename Strategies>
    static inline void apply(P1 const& p1, P2 const& p2,  
                             Segment& shortest_seg, Strategies const&)
    {
        set_segment_from_points::apply(p1, p2, shortest_seg);
    }
};

struct point_to_segment
{
    template <typename Point, typename Segment, typename OutputSegment, typename Strategies>
    static inline void apply(Point const& point, Segment const& segment,
                             OutputSegment& shortest_seg, Strategies const& strategies)
    {
        typename point_type<Segment>::type p[2];
        geometry::detail::assign_point_from_index<0>(segment, p[0]);
        geometry::detail::assign_point_from_index<1>(segment, p[1]);

        boost::ignore_unused(strategies);

        auto closest_point = strategies.closest_points(point, segment)
            .apply(point, p[0], p[1]);

        set_segment_from_points::apply(point, closest_point, shortest_seg);    
    }
};

/*
struct point_to_box
{
    template<typename Point, typename Box, typename Strategies>
static inline auto apply(Point const& point, Box const& box,
                             Strategies const& strategies)
    {
        boost::ignore_unused(strategies);
        return strategies.closest_points(point, box).apply(point, box);
    }
};
*/

template <closure_selector Closure>
class point_to_range
{
public:

    template <typename Point, typename Range, typename Segment, typename Strategies>
    static inline void apply(Point const& point, Range const& range,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        using point_to_point_range = detail::closest_feature::point_to_point_range
            <
                Point, Range, Closure
            >;

        if (boost::size(range) == 0)
        {
            set_segment_from_points::apply(point, point, shortest_seg);
            return;
        }

        closest_points::creturn_t<Point, Range, Strategies> cd_min;
        
        auto comparable_distance = strategy::distance::services::get_comparable
            <
                decltype(strategies.distance(point, range))
            >::apply(strategies.distance(point, range));
        
        auto closest_segment = point_to_point_range::apply(point, 
                                                           boost::begin(range),
                                                           boost::end(range), 
                                                           comparable_distance,
                                                           cd_min);
        
        auto closest_point = strategies.closest_points(point, range)
            .apply(point, *closest_segment.first, *closest_segment.second);

        set_segment_from_points::apply(point, closest_point, shortest_seg);        
    }
};


template<closure_selector Closure>
struct point_to_ring
{
    template <typename Point, typename Ring, typename Segment, typename Strategies>
    static inline auto apply(Point const& point,
                             Ring const& ring,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        if (within::within_point_geometry(point, ring, strategies))
        {
            set_segment_from_points::apply(point, point, shortest_seg); 
        }
        else
        {
            point_to_range
            <
                closure<Ring>::value
            >::apply(point, ring, shortest_seg, strategies);
        }
            
    }
};


template <closure_selector Closure>
class point_to_polygon
{
    template <typename Polygon>
    struct distance_to_interior_rings
    {
        template 
        <
            typename Point, 
            typename InteriorRingIterator, 
            typename Segment, 
            typename Strategies
        >
        static inline void apply(Point const& point,
                                 InteriorRingIterator first,
                                 InteriorRingIterator last,
                                 Segment& shortest_seg,
                                 Strategies const& strategies)
        {
            using per_ring = point_to_range<Closure>;

            for (InteriorRingIterator it = first; it != last; ++it)
            {
                if (within::within_point_geometry(point, *it, strategies))
                {
                    // the point is inside a polygon hole, so its distance
                    // to the polygon is its distance to the polygon's
                    // hole boundary
                    per_ring::apply(point, *it, shortest_seg, strategies);
                    return;
                }
            }
            set_segment_from_points::apply(point, point, shortest_seg); 
        }

        template 
        <
            typename Point, 
            typename InteriorRings, 
            typename Segment, 
            typename Strategies
        >
        static inline void apply(Point const& point, InteriorRings const& interior_rings,
                                 Segment& shortest_seg, Strategies const& strategies)
        {
            apply(point,
                  boost::begin(interior_rings),
                  boost::end(interior_rings),
                  shortest_seg,
                  strategies);
        }
    };


public:
    template 
    <
        typename Point, 
        typename Polygon, 
        typename Segment, 
        typename Strategies
    >
    static inline void apply(Point const& point,
                             Polygon const& polygon,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        using per_ring = point_to_range<Closure>;

        if (! within::covered_by_point_geometry(point, exterior_ring(polygon),
                                                strategies))
        {
            // the point is outside the exterior ring, so its distance
            // to the polygon is its distance to the polygon's exterior ring
            per_ring::apply(point, exterior_ring(polygon), shortest_seg, strategies);
            return;
        }

        // Check interior rings
        distance_to_interior_rings<Polygon>::apply(point,
                                                   interior_rings(polygon),
                                                   shortest_seg,
                                                   strategies);
    }
};


template
<
    typename MultiGeometry,
    bool CheckCoveredBy = std::is_same
        <
            typename tag<MultiGeometry>::type, multi_polygon_tag
        >::value
>
class point_to_multigeometry
{
private:
    using geometry_to_range = detail::closest_feature::geometry_to_range;

public:

    template 
    <
        typename Point,
        typename Segment,
        typename Strategies
    >
    static inline void apply(Point const& point,
                             MultiGeometry const& multigeometry,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        using selector_type = distance::iterator_selector<MultiGeometry const>;

        closest_points::creturn_t<Point, MultiGeometry, Strategies> cd;

        auto comparable_distance = strategy::distance::services::get_comparable
            <
                decltype(strategies.distance(point, multigeometry))
            >::apply(strategies.distance(point, multigeometry));

        typename selector_type::iterator_type it_min
            = geometry_to_range::apply(point,
                                       selector_type::begin(multigeometry),
                                       selector_type::end(multigeometry),
                                       comparable_distance,
                                       cd);
        
        dispatch::closest_points
            <
                Point,
                typename std::iterator_traits
                    <
                        typename selector_type::iterator_type
                    >::value_type
            >::apply(point, *it_min, shortest_seg, strategies);
    }
};


// this is called only for multipolygons, hence the change in the
// template parameter name MultiGeometry to MultiPolygon
template <typename MultiPolygon>
struct point_to_multigeometry<MultiPolygon, true>
{
    template 
    <
        typename Point,
        typename Segment,
        typename Strategies
    >
    static inline void apply(Point const& point,
                             MultiPolygon const& multipolygon,
                             Segment& shortest_seg,
                             Strategies const& strategies)
    {
        if (within::covered_by_point_geometry(point, multipolygon, strategies))
        {
            set_segment_from_points::apply(point, point, shortest_seg); 
            return;
        }

        return point_to_multigeometry
            <
                MultiPolygon, false
            >::apply(point, multipolygon, shortest_seg, strategies);
    }
};


}} // namespace detail::closest_points
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename P1, typename P2>
struct closest_points
    <
        P1, P2, point_tag, point_tag, false
    > : detail::closest_points::point_to_point
{};


template <typename Point, typename Linestring>
struct closest_points
    <
        Point, Linestring, point_tag, linestring_tag, false
    > : detail::closest_points::point_to_range<closed>
{};


template <typename Point, typename Ring>
struct closest_points
    <
        Point, Ring, point_tag, ring_tag, false
    > : detail::closest_points::point_to_ring
        <
            closure<Ring>::value
        >
{};


template <typename Point, typename Polygon>
struct closest_points
    <
        Point, Polygon, point_tag, polygon_tag, false
    > : detail::closest_points::point_to_polygon
        <
            closure<Polygon>::value
        >
{};


template <typename Point, typename Segment>
struct closest_points
    <
        Point, Segment, point_tag, segment_tag, false
    > : detail::closest_points::point_to_segment
{};

/*
template <typename Point, typename Box>
struct closest_points
    <
         Point, Box, point_tag, box_tag,
         strategy_tag_distance_point_box, false
    > : detail::closest_points::point_to_box<Point, Box>
{};
*/

template<typename Point, typename MultiPoint>
struct closest_points
    <
        Point, MultiPoint, point_tag, multi_point_tag, false
    > : detail::closest_points::point_to_multigeometry<MultiPoint>
{};


template<typename Point, typename MultiLinestring>
struct closest_points
    <
        Point, MultiLinestring, point_tag, multi_linestring_tag, false
    > : detail::closest_points::point_to_multigeometry<MultiLinestring>
{};


template<typename Point, typename MultiPolygon>
struct closest_points
    <
        Point, MultiPolygon, point_tag, multi_polygon_tag, false
    > : detail::closest_points::point_to_multigeometry<MultiPolygon>
{};


template <typename Point, typename Linear>
struct closest_points
    <
         Point, Linear, point_tag, linear_tag, false
    > : closest_points
        <
            Point, Linear,
            point_tag, typename tag<Linear>::type, false
        >
{};


template <typename Point, typename Areal>
struct closest_points
    <
         Point, Areal, point_tag, areal_tag, false
    > : closest_points
        <
            Point, Areal,
            point_tag, typename tag<Areal>::type, false
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_POINTS_POINT_TO_GEOMETRY_HPP

/* point_to_geometry.hpp
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
*/