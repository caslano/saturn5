// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018.
// Modifications copyright (c) 2013-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_GEOMETRY_HPP

#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
//#include <boost/geometry/algorithms/within.hpp>
//#include <boost/geometry/algorithms/covered_by.hpp>

#include <boost/geometry/algorithms/detail/relate/result.hpp>
#include <boost/geometry/algorithms/detail/relate/topology_check.hpp>

#include <boost/geometry/util/condition.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

// non-point geometry
template <typename Point, typename Geometry, bool Transpose = false>
struct point_geometry
{
    // TODO: interrupt only if the topology check is complex

    static const bool interruption_enabled = true;

    template <typename Result, typename Strategy>
    static inline void apply(Point const& point, Geometry const& geometry, Result & result, Strategy const& strategy)
    {
        int pig = detail::within::point_in_geometry(point, geometry, strategy);

        if ( pig > 0 ) // within
        {
            relate::set<interior, interior, '0', Transpose>(result);
        }
        else if ( pig == 0 )
        {
            relate::set<interior, boundary, '0', Transpose>(result);
        }
        else // pig < 0 - not within
        {
            relate::set<interior, exterior, '0', Transpose>(result);
        }

        relate::set<exterior, exterior, result_dimension<Point>::value, Transpose>(result);

        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            return;

        typedef detail::relate::topology_check
            <
                Geometry,
                typename Strategy::equals_point_point_strategy_type
            > tc_t;
        if ( relate::may_update<exterior, interior, tc_t::interior, Transpose>(result)
          || relate::may_update<exterior, boundary, tc_t::boundary, Transpose>(result) )
        {
            // the point is on the boundary
            if ( pig == 0 )
            {
                // NOTE: even for MLs, if there is at least one boundary point,
                // somewhere there must be another one
                relate::set<exterior, interior, tc_t::interior, Transpose>(result);
                relate::set<exterior, boundary, tc_t::boundary, Transpose>(result);
            }
            else
            {
                // check if there is a boundary in Geometry
                tc_t tc(geometry);
                if ( tc.has_interior() )
                    relate::set<exterior, interior, tc_t::interior, Transpose>(result);
                if ( tc.has_boundary() )
                    relate::set<exterior, boundary, tc_t::boundary, Transpose>(result);
            }
        }
    }
};

// transposed result of point_geometry
template <typename Geometry, typename Point>
struct geometry_point
{
    // TODO: interrupt only if the topology check is complex

    static const bool interruption_enabled = true;

    template <typename Result, typename Strategy>
    static inline void apply(Geometry const& geometry, Point const& point, Result & result, Strategy const& strategy)
    {
        point_geometry<Point, Geometry, true>::apply(point, geometry, result, strategy);
    }
};

// TODO: rewrite the folowing:

//// NOTE: Those tests should be consistent with within(Point, Box) and covered_by(Point, Box)
//// There is no EPS used in those functions, values are compared using < or <=
//// so comparing MIN and MAX in the same way should be fine
//
//template <typename Box, std::size_t I = 0, std::size_t D = geometry::dimension<Box>::value>
//struct box_has_interior
//{
//    static inline bool apply(Box const& box)
//    {
//        return geometry::get<min_corner, I>(box) < geometry::get<max_corner, I>(box)
//            && box_has_interior<Box, I + 1, D>::apply(box);
//    }
//};
//
//template <typename Box, std::size_t D>
//struct box_has_interior<Box, D, D>
//{
//    static inline bool apply(Box const&) { return true; }
//};
//
//// NOTE: especially important here (see the NOTE above).
//
//template <typename Box, std::size_t I = 0, std::size_t D = geometry::dimension<Box>::value>
//struct box_has_equal_min_max
//{
//    static inline bool apply(Box const& box)
//    {
//        return geometry::get<min_corner, I>(box) == geometry::get<max_corner, I>(box)
//            && box_has_equal_min_max<Box, I + 1, D>::apply(box);
//    }
//};
//
//template <typename Box, std::size_t D>
//struct box_has_equal_min_max<Box, D, D>
//{
//    static inline bool apply(Box const&) { return true; }
//};
//
//template <typename Point, typename Box>
//struct point_box
//{
//    static inline result apply(Point const& point, Box const& box)
//    {
//        result res;
//
//        if ( geometry::within(point, box) ) // this also means that the box has interior
//        {
//            return result("0FFFFFTTT");
//        }
//        else if ( geometry::covered_by(point, box) ) // point is on the boundary
//        {
//            //if ( box_has_interior<Box>::apply(box) )
//            //{
//            //    return result("F0FFFFTTT");
//            //}
//            //else if ( box_has_equal_min_max<Box>::apply(box) ) // no boundary outside point
//            //{
//            //    return result("F0FFFFFFT");
//            //}
//            //else // no interior outside point
//            //{
//            //    return result("F0FFFFFTT");
//            //}
//            return result("F0FFFF**T");
//        }
//        else 
//        {
//            /*if ( box_has_interior<Box>::apply(box) )
//            {
//                return result("FF0FFFTTT");
//            }
//            else
//            {
//                return result("FF0FFFFTT");
//            }*/
//            return result("FF0FFF*TT");
//        }
//
//        return res;
//    }
//};
//
//template <typename Box, typename Point>
//struct box_point
//{
//    static inline result apply(Box const& box, Point const& point)
//    {
//        if ( geometry::within(point, box) )
//            return result("0FTFFTFFT");
//        else if ( geometry::covered_by(point, box) )
//            return result("FF*0F*FFT");
//        else 
//            return result("FF*FFT0FT");
//    }
//};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_GEOMETRY_HPP

/* point_geometry.hpp
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
*/