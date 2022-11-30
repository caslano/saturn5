// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

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

        typedef detail::relate::topology_check<Geometry, Strategy> tc_t;

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
                tc_t tc(geometry, strategy);
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