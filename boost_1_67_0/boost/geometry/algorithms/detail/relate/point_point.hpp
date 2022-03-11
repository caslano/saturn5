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