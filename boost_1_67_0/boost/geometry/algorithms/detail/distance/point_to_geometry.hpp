// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2019.
// Modifications copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_POINT_TO_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_POINT_TO_GEOMETRY_HPP

#include <iterator>

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>

#include <boost/geometry/algorithms/detail/closest_feature/geometry_to_range.hpp>
#include <boost/geometry/algorithms/detail/closest_feature/point_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/iterator_selector.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename P1, typename P2, typename Strategy>
struct point_to_point
{
    static inline
    typename strategy::distance::services::return_type<Strategy, P1, P2>::type
    apply(P1 const& p1, P2 const& p2, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(p1, p2);
    }
};


template
<
    typename Point,
    typename Range,
    closure_selector Closure,
    typename Strategy
>
class point_to_range
{
private:
    typedef typename strategy::distance::services::comparable_type
        <
            Strategy
        >::type comparable_strategy;

    typedef detail::closest_feature::point_to_point_range
        <
            Point, Range, Closure, comparable_strategy
        > point_to_point_range;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            Point,
            typename boost::range_value<Range>::type
        >::type return_type;

    static inline return_type apply(Point const& point, Range const& range,
                                    Strategy const& strategy)
    {
        return_type const zero = return_type(0);

        if (boost::size(range) == 0)
        {
            return zero;
        }

        namespace sds = strategy::distance::services;

        typename sds::return_type
            <
                comparable_strategy,
                Point,
                typename point_type<Range>::type
            >::type cd_min;

        std::pair
            <
                typename boost::range_iterator<Range const>::type,
                typename boost::range_iterator<Range const>::type
            > it_pair
            = point_to_point_range::apply(point,
                                          boost::begin(range),
                                          boost::end(range),
                                          sds::get_comparable
                                              <
                                                  Strategy
                                              >::apply(strategy),
                                          cd_min);

        return
            is_comparable<Strategy>::value
            ?
            cd_min
            :
            strategy.apply(point, *it_pair.first, *it_pair.second);
    }
};


template
<
    typename Point,
    typename Ring,
    closure_selector Closure,
    typename Strategy
>
struct point_to_ring
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Ring>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    Ring const& ring,
                                    Strategy const& strategy)
    {
        // TODO: pass strategy
        if (within::within_point_geometry(point, ring,
                                          strategy.get_point_in_geometry_strategy()))
        {
            return return_type(0);
        }

        return point_to_range
            <
                Point, Ring, closure<Ring>::value, Strategy
            >::apply(point, ring, strategy);
    }
};


template
<
    typename Point,
    typename Polygon,
    closure_selector Closure,
    typename Strategy
>
class point_to_polygon
{
public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Polygon>::type
        >::type return_type;

private:
    typedef point_to_range
        <
            Point, typename ring_type<Polygon>::type, Closure, Strategy
        > per_ring;

    struct distance_to_interior_rings
    {
        template <typename InteriorRingIterator>
        static inline return_type apply(Point const& point,
                                        InteriorRingIterator first,
                                        InteriorRingIterator last,
                                        Strategy const& strategy)
        {
            for (InteriorRingIterator it = first; it != last; ++it)
            {
                // TODO: pass strategy
                if (within::within_point_geometry(point, *it,
                                                  strategy.get_point_in_geometry_strategy()))
                {
                    // the point is inside a polygon hole, so its distance
                    // to the polygon its distance to the polygon's
                    // hole boundary
                    return per_ring::apply(point, *it, strategy);
                }
            }
            return 0;
        }

        template <typename InteriorRings>
        static inline return_type apply(Point const& point,
                                        InteriorRings const& interior_rings,
                                        Strategy const& strategy)
        {
            return apply(point,
                         boost::begin(interior_rings),
                         boost::end(interior_rings),
                         strategy);
        }
    };


public:
    static inline return_type apply(Point const& point,
                                    Polygon const& polygon,
                                    Strategy const& strategy)
    {
        // TODO: pass strategy
        if (! within::covered_by_point_geometry(point, exterior_ring(polygon),
                                                strategy.get_point_in_geometry_strategy()))
        {
            // the point is outside the exterior ring, so its distance
            // to the polygon is its distance to the polygon's exterior ring
            return per_ring::apply(point, exterior_ring(polygon), strategy);
        }

        // Check interior rings
        return distance_to_interior_rings::apply(point,
                                                 interior_rings(polygon),
                                                 strategy);
    }
};


template
<
    typename Point,
    typename MultiGeometry,
    typename Strategy,
    bool CheckCoveredBy = boost::is_same
        <
            typename tag<MultiGeometry>::type, multi_polygon_tag
        >::value
>
class point_to_multigeometry
{
private:
    typedef detail::closest_feature::geometry_to_range geometry_to_range;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            Point,
            typename point_type<MultiGeometry>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    MultiGeometry const& multigeometry,
                                    Strategy const& strategy)
    {
        typedef iterator_selector<MultiGeometry const> selector_type;

        namespace sds = strategy::distance::services;

        typename sds::return_type
            <
                typename sds::comparable_type<Strategy>::type,
                Point,
                typename point_type<MultiGeometry>::type
            >::type cd;

        typename selector_type::iterator_type it_min
            = geometry_to_range::apply(point,
                                       selector_type::begin(multigeometry),
                                       selector_type::end(multigeometry),
                                       sds::get_comparable
                                           <
                                               Strategy
                                           >::apply(strategy),
                                       cd);

        return
            is_comparable<Strategy>::value
            ?
            cd
            :
            dispatch::distance
                <
                    Point,
                    typename std::iterator_traits
                        <
                            typename selector_type::iterator_type
                        >::value_type,
                    Strategy
                >::apply(point, *it_min, strategy);
    }
};


// this is called only for multipolygons, hence the change in the
// template parameter name MultiGeometry to MultiPolygon
template <typename Point, typename MultiPolygon, typename Strategy>
struct point_to_multigeometry<Point, MultiPolygon, Strategy, true>
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            Point,
            typename point_type<MultiPolygon>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    MultiPolygon const& multipolygon,
                                    Strategy const& strategy)
    {
        // TODO: pass strategy
        if (within::covered_by_point_geometry(point, multipolygon,
                                              strategy.get_point_in_geometry_strategy()))
        {
            return 0;
        }

        return point_to_multigeometry
            <
                Point, MultiPolygon, Strategy, false
            >::apply(point, multipolygon, strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Point-point
template <typename P1, typename P2, typename Strategy>
struct distance
    <
        P1, P2, Strategy, point_tag, point_tag,
        strategy_tag_distance_point_point, false
    > : detail::distance::point_to_point<P1, P2, Strategy>
{};


// Point-line version 2, where point-segment strategy is specified
template <typename Point, typename Linestring, typename Strategy>
struct distance
    <
        Point, Linestring, Strategy, point_tag, linestring_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::point_to_range<Point, Linestring, closed, Strategy>
{};


// Point-ring , where point-segment strategy is specified
template <typename Point, typename Ring, typename Strategy>
struct distance
    <
        Point, Ring, Strategy, point_tag, ring_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::point_to_ring
        <
            Point, Ring, closure<Ring>::value, Strategy
        >
{};


// Point-polygon , where point-segment strategy is specified
template <typename Point, typename Polygon, typename Strategy>
struct distance
    <
        Point, Polygon, Strategy, point_tag, polygon_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::point_to_polygon
        <
            Point, Polygon, closure<Polygon>::value, Strategy
        >
{};


// Point-segment version 2, with point-segment strategy
template <typename Point, typename Segment, typename Strategy>
struct distance
    <
        Point, Segment, Strategy, point_tag, segment_tag,
        strategy_tag_distance_point_segment, false
    >
{
    static inline typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Segment>::type
        >::type apply(Point const& point,
                      Segment const& segment,
                      Strategy const& strategy)
    {
        typename point_type<Segment>::type p[2];
        geometry::detail::assign_point_from_index<0>(segment, p[0]);
        geometry::detail::assign_point_from_index<1>(segment, p[1]);

        boost::ignore_unused(strategy);
        return strategy.apply(point, p[0], p[1]);
    }
};


template <typename Point, typename Box, typename Strategy>
struct distance
    <
         Point, Box, Strategy, point_tag, box_tag,
         strategy_tag_distance_point_box, false
    >
{
    static inline typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Box>::type
        >::type
    apply(Point const& point, Box const& box, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(point, box);
    }
};


template<typename Point, typename MultiPoint, typename Strategy>
struct distance
    <
        Point, MultiPoint, Strategy, point_tag, multi_point_tag,
        strategy_tag_distance_point_point, false
    > : detail::distance::point_to_multigeometry
        <
            Point, MultiPoint, Strategy
        >
{};


template<typename Point, typename MultiLinestring, typename Strategy>
struct distance
    <
        Point, MultiLinestring, Strategy, point_tag, multi_linestring_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::point_to_multigeometry
        <
            Point, MultiLinestring, Strategy
        >
{};


template<typename Point, typename MultiPolygon, typename Strategy>
struct distance
    <
        Point, MultiPolygon, Strategy, point_tag, multi_polygon_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::point_to_multigeometry
        <
            Point, MultiPolygon, Strategy
        >
{};


template <typename Point, typename Linear, typename Strategy>
struct distance
    <
         Point, Linear, Strategy, point_tag, linear_tag,
         strategy_tag_distance_point_segment, false
    > : distance
        <
            Point, Linear, Strategy,
            point_tag, typename tag<Linear>::type,
            strategy_tag_distance_point_segment, false
        >
{};


template <typename Point, typename Areal, typename Strategy>
struct distance
    <
         Point, Areal, Strategy, point_tag, areal_tag,
         strategy_tag_distance_point_segment, false
    > : distance
        <
            Point, Areal, Strategy,
            point_tag, typename tag<Areal>::type,
            strategy_tag_distance_point_segment, false
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_POINT_TO_GEOMETRY_HPP

/* point_to_geometry.hpp
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
*/