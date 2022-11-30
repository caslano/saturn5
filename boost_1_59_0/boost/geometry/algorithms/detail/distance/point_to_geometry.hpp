// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

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
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/relate/services.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template
<
    typename P1, typename P2, typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct point_to_point
{
    static inline
    auto apply(P1 const& p1, P2 const& p2, Strategies const& strategies)
    {
        boost::ignore_unused(strategies);
        return strategies.distance(p1, p2).apply(p1, p2);
    }
};

// TEMP?
// called by geometry_to_range
template <typename P1, typename P2, typename Strategy>
struct point_to_point<P1, P2, Strategy, false>
{
    static inline
    auto apply(P1 const& p1, P2 const& p2, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(p1, p2);
    }
};


template
<
    typename Point, typename Segment, typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct point_to_segment
{
    static inline auto apply(Point const& point, Segment const& segment,
                             Strategies const& strategies)
    {
        typename point_type<Segment>::type p[2];
        geometry::detail::assign_point_from_index<0>(segment, p[0]);
        geometry::detail::assign_point_from_index<1>(segment, p[1]);

        boost::ignore_unused(strategies);
        return strategies.distance(point, segment).apply(point, p[0], p[1]);
    }
};

// TEMP?
// called by geometry_to_range
template <typename Point, typename Segment, typename Strategy>
struct point_to_segment<Point, Segment, Strategy, false>
{
    static inline auto apply(Point const& point, Segment const& segment,
                             Strategy const& strategy)
    {
        typename point_type<Segment>::type p[2];
        geometry::detail::assign_point_from_index<0>(segment, p[0]);
        geometry::detail::assign_point_from_index<1>(segment, p[1]);

        boost::ignore_unused(strategy);
        return strategy.apply(point, p[0], p[1]);
    }
};


template
<
    typename Point, typename Box, typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct point_to_box
{
    static inline auto apply(Point const& point, Box const& box,
                             Strategies const& strategies)
    {
        boost::ignore_unused(strategies);
        return strategies.distance(point, box).apply(point, box);
    }
};

// TEMP?
// called by geometry_to_range
template <typename Point, typename Box, typename Strategy>
struct point_to_box<Point, Box, Strategy, false>
{
    static inline auto apply(Point const& point, Box const& box,
                             Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(point, box);
    }
};


template
<
    typename Point,
    typename Range,
    closure_selector Closure,
    typename Strategies
>
class point_to_range
{
private:
    typedef distance::strategy_t<Point, Range, Strategies> strategy_type;

    typedef detail::closest_feature::point_to_point_range
        <
            Point, Range, Closure
        > point_to_point_range;

public:
    typedef distance::return_t<Point, Range, Strategies> return_type;

    static inline return_type apply(Point const& point, Range const& range,
                                    Strategies const& strategies)
    {
        if (boost::size(range) == 0)
        {
            return return_type(0);
        }

        distance::creturn_t<Point, Range, Strategies> cd_min;

        std::pair
            <
                typename boost::range_iterator<Range const>::type,
                typename boost::range_iterator<Range const>::type
            > it_pair
            = point_to_point_range::apply(point,
                                          boost::begin(range),
                                          boost::end(range),
                                          strategy::distance::services::get_comparable
                                              <
                                                  strategy_type
                                              >::apply(strategies.distance(point, range)),
                                          cd_min);

        return
            is_comparable<strategy_type>::value
            ?
            cd_min
            :
            strategies.distance(point, range).apply(point, *it_pair.first, *it_pair.second);
    }
};


template
<
    typename Point,
    typename Ring,
    closure_selector Closure,
    typename Strategies
>
struct point_to_ring
{
    typedef distance::return_t<Point, Ring, Strategies> return_type;

    static inline return_type apply(Point const& point,
                                    Ring const& ring,
                                    Strategies const& strategies)
    {
        if (within::within_point_geometry(point, ring, strategies))
        {
            return return_type(0);
        }

        return point_to_range
            <
                Point, Ring, closure<Ring>::value, Strategies
            >::apply(point, ring, strategies);
    }
};


template
<
    typename Point,
    typename Polygon,
    closure_selector Closure,
    typename Strategies
>
class point_to_polygon
{
public:
    typedef distance::return_t<Point, Polygon, Strategies> return_type;

private:
    typedef point_to_range
        <
            Point, typename ring_type<Polygon>::type, Closure, Strategies
        > per_ring;

    struct distance_to_interior_rings
    {
        template <typename InteriorRingIterator>
        static inline return_type apply(Point const& point,
                                        InteriorRingIterator first,
                                        InteriorRingIterator last,
                                        Strategies const& strategies)
        {
            for (InteriorRingIterator it = first; it != last; ++it)
            {
                if (within::within_point_geometry(point, *it, strategies))
                {
                    // the point is inside a polygon hole, so its distance
                    // to the polygon its distance to the polygon's
                    // hole boundary
                    return per_ring::apply(point, *it, strategies);
                }
            }
            return return_type(0);
        }

        template <typename InteriorRings>
        static inline return_type apply(Point const& point, InteriorRings const& interior_rings,
                                        Strategies const& strategies)
        {
            return apply(point,
                         boost::begin(interior_rings),
                         boost::end(interior_rings),
                         strategies);
        }
    };


public:
    static inline return_type apply(Point const& point,
                                    Polygon const& polygon,
                                    Strategies const& strategies)
    {
        if (! within::covered_by_point_geometry(point, exterior_ring(polygon),
                                                strategies))
        {
            // the point is outside the exterior ring, so its distance
            // to the polygon is its distance to the polygon's exterior ring
            return per_ring::apply(point, exterior_ring(polygon), strategies);
        }

        // Check interior rings
        return distance_to_interior_rings::apply(point,
                                                 interior_rings(polygon),
                                                 strategies);
    }
};


template
<
    typename Point,
    typename MultiGeometry,
    typename Strategies,
    bool CheckCoveredBy = std::is_same
        <
            typename tag<MultiGeometry>::type, multi_polygon_tag
        >::value
>
class point_to_multigeometry
{
private:
    typedef detail::closest_feature::geometry_to_range geometry_to_range;

    typedef distance::strategy_t<Point, MultiGeometry, Strategies> strategy_type;

public:
    typedef distance::return_t<Point, MultiGeometry, Strategies> return_type;

    static inline return_type apply(Point const& point,
                                    MultiGeometry const& multigeometry,
                                    Strategies const& strategies)
    {
        typedef iterator_selector<MultiGeometry const> selector_type;

        distance::creturn_t<Point, MultiGeometry, Strategies> cd;

        typename selector_type::iterator_type it_min
            = geometry_to_range::apply(point,
                                       selector_type::begin(multigeometry),
                                       selector_type::end(multigeometry),
                                       strategy::distance::services::get_comparable
                                           <
                                               strategy_type
                                           >::apply(strategies.distance(point, multigeometry)),
                                       cd);

        // TODO - It would be possible to use a tool similar to result_from_distance
        //        but working in the opposite way, i.e. calculating the distance
        //        value from comparable distance value. This way the additional distance
        //        call would not be needed.
        return
            is_comparable<strategy_type>::value
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
                    Strategies
                >::apply(point, *it_min, strategies);
    }
};


// this is called only for multipolygons, hence the change in the
// template parameter name MultiGeometry to MultiPolygon
template <typename Point, typename MultiPolygon, typename Strategies>
struct point_to_multigeometry<Point, MultiPolygon, Strategies, true>
{
    typedef distance::return_t<Point, MultiPolygon, Strategies> return_type;

    static inline return_type apply(Point const& point,
                                    MultiPolygon const& multipolygon,
                                    Strategies const& strategies)
    {
        if (within::covered_by_point_geometry(point, multipolygon, strategies))
        {
            return return_type(0);
        }

        return point_to_multigeometry
            <
                Point, MultiPolygon, Strategies, false
            >::apply(point, multipolygon, strategies);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename P1, typename P2, typename Strategy>
struct distance
    <
        P1, P2, Strategy, point_tag, point_tag,
        strategy_tag_distance_point_point, false
    > : detail::distance::point_to_point<P1, P2, Strategy>
{};


template <typename Point, typename Linestring, typename Strategy>
struct distance
    <
        Point, Linestring, Strategy, point_tag, linestring_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::point_to_range<Point, Linestring, closed, Strategy>
{};


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


template <typename Point, typename Segment, typename Strategy>
struct distance
    <
        Point, Segment, Strategy, point_tag, segment_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::point_to_segment<Point, Segment, Strategy>
{};


template <typename Point, typename Box, typename Strategy>
struct distance
    <
         Point, Box, Strategy, point_tag, box_tag,
         strategy_tag_distance_point_box, false
    > : detail::distance::point_to_box<Point, Box, Strategy>
{};


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