// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2017, 2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_POINT_HPP

#include <algorithm>
#include <vector>

#include <boost/range/empty.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
#include <boost/geometry/algorithms/detail/relate/result.hpp>

#include <boost/geometry/policies/compare.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

template <typename Point1, typename Point2>
struct point_point
{
    static const bool interruption_enabled = false;

    template <typename Result, typename Strategy>
    static inline void apply(Point1 const& point1, Point2 const& point2,
                             Result & result,
                             Strategy const& strategy)
    {
        bool equal = detail::equals::equals_point_point(point1, point2, strategy);
        if ( equal )
        {
            relate::set<interior, interior, '0'>(result);
        }
        else
        {
            relate::set<interior, exterior, '0'>(result);
            relate::set<exterior, interior, '0'>(result);
        }

        relate::set<exterior, exterior, result_dimension<Point1>::value>(result);
    }
};

template <typename Point, typename MultiPoint, typename EqPPStrategy>
std::pair<bool, bool> point_multipoint_check(Point const& point,
                                             MultiPoint const& multi_point,
                                             EqPPStrategy const& strategy)
{
    bool found_inside = false;
    bool found_outside = false;

    // point_in_geometry could be used here but why iterate over MultiPoint twice?
    // we must search for a point in the exterior because all points in MultiPoint can be equal

    typedef typename boost::range_iterator<MultiPoint const>::type iterator;
    iterator it = boost::begin(multi_point);
    iterator last = boost::end(multi_point);
    for ( ; it != last ; ++it )
    {
        bool ii = detail::equals::equals_point_point(point, *it, strategy);

        if ( ii )
            found_inside = true;
        else
            found_outside = true;

        if ( found_inside && found_outside )
            break;
    }

    return std::make_pair(found_inside, found_outside);
}

template <typename Point, typename MultiPoint, bool Transpose = false>
struct point_multipoint
{
    static const bool interruption_enabled = false;

    template <typename Result, typename Strategy>
    static inline void apply(Point const& point, MultiPoint const& multi_point,
                             Result & result,
                             Strategy const& strategy)
    {
        if ( boost::empty(multi_point) )
        {
            // TODO: throw on empty input?
            relate::set<interior, exterior, '0', Transpose>(result);
            return;
        }

        std::pair<bool, bool> rel = point_multipoint_check(point, multi_point, strategy);

        if ( rel.first ) // some point of MP is equal to P
        {
            relate::set<interior, interior, '0', Transpose>(result);

            if ( rel.second ) // a point of MP was found outside P
            {
                relate::set<exterior, interior, '0', Transpose>(result);
            }
        }
        else
        {
            relate::set<interior, exterior, '0', Transpose>(result);
            relate::set<exterior, interior, '0', Transpose>(result);
        }

        relate::set<exterior, exterior, result_dimension<Point>::value, Transpose>(result);
    }
};

template <typename MultiPoint, typename Point>
struct multipoint_point
{
    static const bool interruption_enabled = false;

    template <typename Result, typename Strategy>
    static inline void apply(MultiPoint const& multi_point, Point const& point,
                             Result & result,
                             Strategy const& strategy)
    {
        point_multipoint<Point, MultiPoint, true>::apply(point, multi_point, result, strategy);
    }
};

template <typename MultiPoint1, typename MultiPoint2>
struct multipoint_multipoint
{
    static const bool interruption_enabled = true;

    template <typename Result, typename Strategy>
    static inline void apply(MultiPoint1 const& multi_point1, MultiPoint2 const& multi_point2,
                             Result & result,
                             Strategy const& /*strategy*/)
    {
        typedef typename Strategy::cs_tag cs_tag;

        {
            // TODO: throw on empty input?
            bool empty1 = boost::empty(multi_point1);
            bool empty2 = boost::empty(multi_point2);
            if ( empty1 && empty2 )
            {
                return;
            }
            else if ( empty1 )
            {
                relate::set<exterior, interior, '0'>(result);
                return;
            }
            else if ( empty2 )
            {
                relate::set<interior, exterior, '0'>(result);
                return;
            }
        }

        // The geometry containing smaller number of points will be analysed first
        if ( boost::size(multi_point1) < boost::size(multi_point2) )
        {
            search_both<false, cs_tag>(multi_point1, multi_point2, result);
        }
        else
        {
            search_both<true, cs_tag>(multi_point2, multi_point1, result);
        }

        relate::set<exterior, exterior, result_dimension<MultiPoint1>::value>(result);
    }

    template <bool Transpose, typename CSTag, typename MPt1, typename MPt2, typename Result>
    static inline void search_both(MPt1 const& first_sorted_mpt, MPt2 const& first_iterated_mpt,
                                   Result & result)
    {
        if ( relate::may_update<interior, interior, '0'>(result)
          || relate::may_update<interior, exterior, '0'>(result)
          || relate::may_update<exterior, interior, '0'>(result) )
        {
            // NlogN + MlogN
            bool is_disjoint = search<Transpose, CSTag>(first_sorted_mpt, first_iterated_mpt, result);

            if ( BOOST_GEOMETRY_CONDITION(is_disjoint || result.interrupt) )
                return;
        }

        if ( relate::may_update<interior, interior, '0'>(result)
          || relate::may_update<interior, exterior, '0'>(result)
          || relate::may_update<exterior, interior, '0'>(result) )
        {
            // MlogM + NlogM
            search<! Transpose, CSTag>(first_iterated_mpt, first_sorted_mpt, result);
        }
    }

    template <bool Transpose,
              typename CSTag,
              typename SortedMultiPoint,
              typename IteratedMultiPoint,
              typename Result>
    static inline bool search(SortedMultiPoint const& sorted_mpt,
                              IteratedMultiPoint const& iterated_mpt,
                              Result & result)
    {
        // sort points from the 1 MPt
        typedef typename geometry::point_type<SortedMultiPoint>::type point_type;
        typedef geometry::less<void, -1, CSTag> less_type;

        std::vector<point_type> points(boost::begin(sorted_mpt), boost::end(sorted_mpt));

        less_type const less = less_type();
        std::sort(points.begin(), points.end(), less);

        bool found_inside = false;
        bool found_outside = false;

        // for each point in the second MPt
        typedef typename boost::range_iterator<IteratedMultiPoint const>::type iterator;
        for ( iterator it = boost::begin(iterated_mpt) ;
              it != boost::end(iterated_mpt) ; ++it )
        {
            bool ii =
                std::binary_search(points.begin(), points.end(), *it, less);
            if ( ii )
                found_inside = true;
            else
                found_outside = true;

            if ( found_inside && found_outside )
                break;
        }

        if ( found_inside ) // some point of MP2 is equal to some of MP1
        {
// TODO: if I/I is set for one MPt, this won't be changed when the other one in analysed
//       so if e.g. only I/I must be analysed we musn't check the other MPt

            relate::set<interior, interior, '0', Transpose>(result);

            if ( found_outside ) // some point of MP2 was found outside of MP1
            {
                relate::set<exterior, interior, '0', Transpose>(result);
            }
        }
        else
        {
            relate::set<interior, exterior, '0', Transpose>(result);
            relate::set<exterior, interior, '0', Transpose>(result);
        }

        // if no point is intersecting the other MPt then we musn't analyse the reversed case
        return ! found_inside;
    }
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_POINT_POINT_HPP

/* point_point.hpp
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
*/