// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP


#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/concepts/within_concept.hpp>

#include <boost/geometry/util/range.hpp>
#include <boost/geometry/views/detail/closed_clockwise_view.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within {


template <typename Point, typename Range, typename Strategy> inline
int point_in_range(Point const& point, Range const& range, Strategy const& strategy)
{
    typename Strategy::state_type state;

    typedef typename boost::range_iterator<Range const>::type iterator_type;
    iterator_type it = boost::begin(range);
    iterator_type end = boost::end(range);

    for ( iterator_type previous = it++ ; it != end ; ++previous, ++it )
    {
        if ( ! strategy.apply(point, *previous, *it, state) )
        {
            break;
        }
    }

    return strategy.result(state);
}

}} // namespace detail::within

namespace detail_dispatch { namespace within {

// checks the relation between a point P and geometry G
// returns 1 if P is in the interior of G
// returns 0 if P is on the boundry of G
// returns -1 if P is in the exterior of G

template <typename Geometry,
          typename Tag = typename geometry::tag<Geometry>::type>
struct point_in_geometry
    : not_implemented<Tag>
{};

template <typename Point2>
struct point_in_geometry<Point2, point_tag>
{
    template <typename Point1, typename Strategy> static inline
    int apply(Point1 const& point1, Point2 const& point2, Strategy const& strategy)
    {
        typedef decltype(strategy.relate(point1, point2)) strategy_type;
        return strategy_type::apply(point1, point2) ? 1 : -1;
    }
};

template <typename Segment>
struct point_in_geometry<Segment, segment_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Segment const& segment, Strategy const& strategy)
    {
        typedef typename geometry::point_type<Segment>::type point_type;
        point_type p0, p1;
// TODO: don't copy points
        detail::assign_point_from_index<0>(segment, p0);
        detail::assign_point_from_index<1>(segment, p1);

        auto const s = strategy.relate(point, segment);
        typename decltype(s)::state_type state;
        s.apply(point, p0, p1, state);
        int r = s.result(state);

        if ( r != 0 )
            return -1; // exterior

        // if the point is equal to the one of the terminal points
        if ( detail::equals::equals_point_point(point, p0, strategy)
          || detail::equals::equals_point_point(point, p1, strategy) )
            return 0; // boundary
        else
            return 1; // interior
    }
};


template <typename Linestring>
struct point_in_geometry<Linestring, linestring_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Linestring const& linestring, Strategy const& strategy)
    {
        std::size_t count = boost::size(linestring);
        if ( count > 1 )
        {
            if ( detail::within::point_in_range(point, linestring,
                                    strategy.relate(point, linestring)) != 0 )
            {
                return -1; // exterior
            }

            typedef typename boost::range_value<Linestring>::type point_type;
            point_type const& front = range::front(linestring);
            point_type const& back = range::back(linestring);

            // if the linestring doesn't have a boundary
            if ( detail::equals::equals_point_point(front, back, strategy) )
            {
                return 1; // interior
            }
            // else if the point is equal to the one of the terminal points
            else if ( detail::equals::equals_point_point(point, front, strategy)
                   || detail::equals::equals_point_point(point, back, strategy) )
            {
                return 0; // boundary
            }
            else
            {
                return 1; // interior
            }
        }
// TODO: for now degenerated linestrings are ignored
//       throw an exception here?
        /*else if ( count == 1 )
        {
            if ( detail::equals::equals_point_point(point, front, strategy) )
                return 1;
        }*/

        return -1; // exterior
    }
};

template <typename Ring>
struct point_in_geometry<Ring, ring_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Ring const& ring, Strategy const& strategy)
    {
        if ( boost::size(ring) < core_detail::closure::minimum_ring_size
                                    <
                                        geometry::closure<Ring>::value
                                    >::value )
        {
            return -1;
        }

        detail::closed_clockwise_view<Ring const> view(ring);
        return detail::within::point_in_range(point, view,
                                              strategy.relate(point, ring));
    }
};

// Polygon: in exterior ring, and if so, not within interior ring(s)
template <typename Polygon>
struct point_in_geometry<Polygon, polygon_tag>
{
    template <typename Point, typename Strategy>
    static inline int apply(Point const& point, Polygon const& polygon,
                            Strategy const& strategy)
    {
        int const code = point_in_geometry
            <
                typename ring_type<Polygon>::type
            >::apply(point, exterior_ring(polygon), strategy);

        if (code == 1)
        {
            typename interior_return_type<Polygon const>::type
                rings = interior_rings(polygon);
            
            for (typename detail::interior_iterator<Polygon const>::type
                 it = boost::begin(rings);
                 it != boost::end(rings);
                 ++it)
            {
                int const interior_code = point_in_geometry
                    <
                        typename ring_type<Polygon>::type
                    >::apply(point, *it, strategy);

                if (interior_code != -1)
                {
                    // If 0, return 0 (touch)
                    // If 1 (inside hole) return -1 (outside polygon)
                    // If -1 (outside hole) check other holes if any
                    return -interior_code;
                }
            }
        }
        return code;
    }
};

template <typename Geometry>
struct point_in_geometry<Geometry, multi_point_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Geometry const& geometry, Strategy const& strategy)
    {
        typedef typename boost::range_value<Geometry>::type point_type;
        typedef typename boost::range_const_iterator<Geometry>::type iterator;
        for ( iterator it = boost::begin(geometry) ; it != boost::end(geometry) ; ++it )
        {
            int pip = point_in_geometry<point_type>::apply(point, *it, strategy);

            //BOOST_GEOMETRY_ASSERT(pip != 0);
            if ( pip > 0 ) // inside
                return 1;
        }

        return -1; // outside
    }
};

template <typename Geometry>
struct point_in_geometry<Geometry, multi_linestring_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Geometry const& geometry, Strategy const& strategy)
    {
        int pip = -1; // outside

        typedef typename boost::range_value<Geometry>::type linestring_type;
        typedef typename boost::range_value<linestring_type>::type point_type;
        typedef typename boost::range_iterator<Geometry const>::type iterator;
        iterator it = boost::begin(geometry);
        for ( ; it != boost::end(geometry) ; ++it )
        {
            pip = point_in_geometry<linestring_type>::apply(point, *it, strategy);

            // inside or on the boundary
            if ( pip >= 0 )
            {
                ++it;
                break;
            }
        }

        // outside
        if ( pip < 0 )
            return -1;

        // TODO: the following isn't needed for covered_by()

        unsigned boundaries = pip == 0 ? 1 : 0;

        for ( ; it != boost::end(geometry) ; ++it )
        {
            if ( boost::size(*it) < 2 )
                continue;

            point_type const& front = range::front(*it);
            point_type const& back = range::back(*it);

            // is closed_ring - no boundary
            if ( detail::equals::equals_point_point(front, back, strategy) )
                continue;

            // is point on boundary
            if ( detail::equals::equals_point_point(point, front, strategy)
              || detail::equals::equals_point_point(point, back, strategy) )
            {
                ++boundaries;
            }
        }

        // if the number of boundaries is odd, the point is on the boundary
        return boundaries % 2 ? 0 : 1;
    }
};

template <typename Geometry>
struct point_in_geometry<Geometry, multi_polygon_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Geometry const& geometry, Strategy const& strategy)
    {
        // For invalid multipolygons
        //int res = -1; // outside

        typedef typename boost::range_value<Geometry>::type polygon_type;
        typedef typename boost::range_const_iterator<Geometry>::type iterator;
        for ( iterator it = boost::begin(geometry) ; it != boost::end(geometry) ; ++it )
        {
            int pip = point_in_geometry<polygon_type>::apply(point, *it, strategy);

            // inside or on the boundary
            if ( pip >= 0 )
                return pip;

            // For invalid multi-polygons
            //if ( 1 == pip ) // inside polygon
            //    return 1;
            //else if ( res < pip ) // point must be inside at least one polygon
            //    res = pip;
        }

        return -1; // for valid multipolygons
        //return res; // for invalid multipolygons
    }
};

}} // namespace detail_dispatch::within

namespace detail { namespace within {

// 1 - in the interior
// 0 - in the boundry
// -1 - in the exterior
template <typename Point, typename Geometry, typename Strategy>
inline int point_in_geometry(Point const& point, Geometry const& geometry, Strategy const& strategy)
{
    concepts::within::check<Point, Geometry, Strategy>();

    return detail_dispatch::within::point_in_geometry<Geometry>::apply(point, geometry, strategy);
}

template <typename Point, typename Geometry, typename Strategy>
inline bool within_point_geometry(Point const& point, Geometry const& geometry, Strategy const& strategy)
{
    return point_in_geometry(point, geometry, strategy) > 0;
}

template <typename Point, typename Geometry, typename Strategy>
inline bool covered_by_point_geometry(Point const& point, Geometry const& geometry, Strategy const& strategy)
{
    return point_in_geometry(point, geometry, strategy) >= 0;
}

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP

/* point_in_geometry.hpp
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
*/