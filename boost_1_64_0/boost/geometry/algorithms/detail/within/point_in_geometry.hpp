// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP


#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/concepts/within_concept.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/relate.hpp>

#include <boost/geometry/util/range.hpp>
#include <boost/geometry/views/detail/normalized_view.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within {

template <typename Point1, typename Point2, typename Strategy>
inline bool equals_point_point(Point1 const& p1, Point2 const& p2, Strategy const& strategy)
{
    return equals::equals_point_point(p1, p2, strategy.get_equals_point_point_strategy());
}

// TODO: is this needed?
inline int check_result_type(int result)
{
    return result;
}

template <typename T>
inline T check_result_type(T result)
{
    BOOST_GEOMETRY_ASSERT(false);
    return result;
}

template <typename Point, typename Range, typename Strategy> inline
int point_in_range(Point const& point, Range const& range, Strategy const& strategy)
{
    boost::ignore_unused(strategy);

    typedef typename boost::range_iterator<Range const>::type iterator_type;
    typename Strategy::state_type state;
    iterator_type it = boost::begin(range);
    iterator_type end = boost::end(range);

    for ( iterator_type previous = it++ ; it != end ; ++previous, ++it )
    {
        if ( ! strategy.apply(point, *previous, *it, state) )
        {
            break;
        }
    }

    return check_result_type(strategy.result(state));
}

template <typename Geometry, typename Point, typename Range>
inline int point_in_range(Point const& point, Range const& range)
{
    typedef typename strategy::point_in_geometry::services::default_strategy
        <
            Point, Geometry
        >::type strategy_type;

    return point_in_range(point, range, strategy_type());
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
        boost::ignore_unused(strategy);
        return strategy.apply(point1, point2) ? 1 : -1;
    }
};

template <typename Segment>
struct point_in_geometry<Segment, segment_tag>
{
    template <typename Point, typename Strategy> static inline
    int apply(Point const& point, Segment const& segment, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);

        typedef typename geometry::point_type<Segment>::type point_type;
        point_type p0, p1;
// TODO: don't copy points
        detail::assign_point_from_index<0>(segment, p0);
        detail::assign_point_from_index<1>(segment, p1);

        typename Strategy::state_type state;
        strategy.apply(point, p0, p1, state);
        int r = detail::within::check_result_type(strategy.result(state));

        if ( r != 0 )
            return -1; // exterior

        // if the point is equal to the one of the terminal points
        if ( detail::within::equals_point_point(point, p0, strategy)
          || detail::within::equals_point_point(point, p1, strategy) )
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
            if ( detail::within::point_in_range(point, linestring, strategy) != 0 )
                return -1; // exterior

            // if the linestring doesn't have a boundary
            if (detail::within::equals_point_point(range::front(linestring), range::back(linestring), strategy))
                return 1; // interior
            // else if the point is equal to the one of the terminal points
            else if (detail::within::equals_point_point(point, range::front(linestring), strategy)
                || detail::within::equals_point_point(point, range::back(linestring), strategy))
                return 0; // boundary
            else
                return 1; // interior
        }
// TODO: for now degenerated linestrings are ignored
//       throw an exception here?
        /*else if ( count == 1 )
        {
            if ( detail::equals::equals_point_point(point, range::front(linestring)) )
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

        detail::normalized_view<Ring const> view(ring);
        return detail::within::point_in_range(point, view, strategy);
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
            if ( detail::within::equals_point_point(front, back, strategy) )
                continue;

            // is point on boundary
            if ( detail::within::equals_point_point(point, front, strategy)
              || detail::within::equals_point_point(point, back, strategy) )
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

template <typename Point, typename Geometry>
inline int point_in_geometry(Point const& point, Geometry const& geometry)
{
    typedef typename strategy::point_in_geometry::services::default_strategy
        <
            Point, Geometry
        >::type strategy_type;

    return point_in_geometry(point, geometry, strategy_type());
}

template <typename Point, typename Geometry, typename Strategy>
inline bool within_point_geometry(Point const& point, Geometry const& geometry, Strategy const& strategy)
{
    return point_in_geometry(point, geometry, strategy) > 0;
}

template <typename Point, typename Geometry>
inline bool within_point_geometry(Point const& point, Geometry const& geometry)
{
    return point_in_geometry(point, geometry) > 0;
}

template <typename Point, typename Geometry, typename Strategy>
inline bool covered_by_point_geometry(Point const& point, Geometry const& geometry, Strategy const& strategy)
{
    return point_in_geometry(point, geometry, strategy) >= 0;
}

template <typename Point, typename Geometry>
inline bool covered_by_point_geometry(Point const& point, Geometry const& geometry)
{
    return point_in_geometry(point, geometry) >= 0;
}

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_POINT_IN_GEOMETRY_HPP

/* point_in_geometry.hpp
Uya13+xRD6XrMZFH+go/Y3zZ2eWRwckmf8WmWW+ynD8IgleSgEvxiPDZphb2O514JHDbLyQC1L38ckn/MtMHDgNmTlAaV6GaxlstLzwTh5k/HS1ou+2XKEtjwlf3USdlCZ3ch986iuSFCBeFAE9LnfeqcUcfv4G02lzp4XmHYpQqmgJmxHsR+mGKdEA4MdYDFqQ3eQfLIfa3OeyS7N7mhnSH2pBKlO6f+NJlCudTeN03jrCeNfptxDbnlCIC84UW3RyoB8/LHlt685DLqpgzs1IlNw4x76SnUzFGvRQ3e6dEKyZsTFKNOjFV9U6JdqS5AowvnZuqJ2Dcx/EtxqmK9QVjpFJ662whCzbxuCKVeKdTsS/Hbje/hmncmF8pZHK5Km6ZRaAmK74VCUCY43WE8bQVcRMiwtiZVxRGTkX7GUnrJnGJvAyRoNINHb1PaK0+nPDNET3Xblteltr/HHHaeoE7zG1/TrVuuRhzsMcHGGg9R/srnoj0SK72Vzw96/WOHvjx1XIGtgsdiEI5UFjyHSgZhe7kyPgGypVCpzttkozOIM4q1VR1lQZXA0ttm5BZ82ciJmC0AR9lAFnjQ4N8vZRplm4NGDj/qvYFKpoiZ+r2Jdf5K/bPa4HYom20sU5m5D3R/lDI75+JqI5n/Ea1w5bqbbR5KbZMVJaGQachXUtxr0R9BP1igE7tvUDHDYAL5G7+ukyLsJDLbku3tt/yVjLJcnge+f02bVaoYybQ3hFi0hJ7YesYyve++t0S9Vrp5jvZjH/SZ6KzDjvT97C9UWi6q58/naukc/dccFTO5hdus268OFL0FesHp6AP/j7461b/V7P+Rnz0RKeWGI+VSfxZJsSMuf0PNovybV+5oTYPvKC2o8/Tg9WBZm9kPE+Mjois6J097C3s00oyQyz8cKxeVqIOg6xKK1k5cxWLtf13qiy/rgNsOOYY8nIy2TH1YDNV0jJjbt+OmPHIsSgzfPAzCD8X4YWZ4a52hA9EeH7kgvTwI88SFroHV+wT2zswObO8Iowlk5EKxbgZKPKohzlJaSmwRdhprrjZnqSu35Q5SQ0eZfn844345UjsXz4sV9RElrlS9+b1m601jbkgc8VQ/pk+YEwaJT7F/31+aU/GH4ZY+HypVLtucoFwfGfhTqfLwURd7/CuJ+VQ6pCcTDZpaTsaNWE8z0y4IPYV4QVepXA04cOiXyCZzigmLlGOZCd7BXmRTWVPzxuMfd3ruHEmUN/iElZZ+DWn9k5kfhinWd5SxBhFxdgz6I1IOuhDSGVsFyslWxCnk4A6ToPCZazVleaCbxK7Y4ryrbgOUVzIRoIgZu9TJ5Mv0ZziAmfmLfREVC0u67l2sRC0g8X8+1w0Zroe13049Hzpw2rjsF/Mspr7z0bAtFtHtooiLTFbQoa51ppteUOB+HHukYakGdX40ka5xP6tbLFIKVOXH3PzounJlDhjrVNxT89AGHfzs7RPmSKIveQTUdR/p0Z7bIMs7wefUOkmOpXp0QYR23Lm6327So9wbm1UFhEYa9TZ+rFjVfGuVPFftou/R6frcNgsVJUSYpu6dBbLMpn8ep1cyQHjykCn79qaJZmtOV9nq9PZ7nmbbPdlZuvcKJvmS5ll6dtkWZaZpUVlGUZ9Be6DRAqPLW+SiOXKT99hhnxno5bC7CK2W8lN07+HGv/xv9jhub5bnhJxwSYM6zH9xZi8q2CP22HcWnvnbhqT35B8keaqc8XzSn/5HiDfA+V7qHwXyfco+S6W77Pl+xz5Ple+PyzfJfJ9nnyfL9+l8n2hfI+X7wnyPUm+PyPf0+X7K/L9VfmeKd9fk+9Z8j1bvi+T77n8hogi7P9v73A7nsE=
*/