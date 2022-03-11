// Boost.Geometry

// Copyright (c) 2018 Yaghyavardhan Singh Khangarot, Hyderabad, India.
// Contributed and/or modified by Yaghyavardhan Singh Khangarot,
//   as part of Google Summer of Code 2018 program.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISCRETE_HAUSDORFF_DISTANCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISCRETE_HAUSDORFF_DISTANCE_HPP

#include <algorithm>

#ifdef BOOST_GEOMETRY_DEBUG_HAUSDORFF_DISTANCE
#include <iostream>
#endif

#include <iterator>
#include <utility>
#include <vector>
#include <limits>

#include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/distance_result.hpp>
#include <boost/geometry/util/range.hpp>

#ifdef BOOST_GEOMETRY_ENABLE_SIMILARITY_RTREE
#include <boost/geometry/index/rtree.hpp>
#endif // BOOST_GEOMETRY_ENABLE_SIMILARITY_RTREE

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace discrete_hausdorff_distance
{

struct point_range
{
    template <typename Point, typename Range, typename Strategy>
    static inline
    typename distance_result
        <
            typename point_type<Point>::type,
            typename point_type<Range>::type,
            Strategy
        >::type
    apply(Point const& pnt, Range const& rng, Strategy const& strategy)
    {
        typedef typename distance_result
            <
                typename point_type<Point>::type,
                typename point_type<Range>::type,
                Strategy
            >::type result_type;
        typedef typename boost::range_size<Range>::type size_type;

        size_type const n = boost::size(rng);
        result_type dis_min = 0;
        bool is_dis_min_set = false;

        for (size_type i = 0 ; i < n ; i++)
        {
            result_type dis_temp = strategy.apply(pnt, range::at(rng, i));
            if (! is_dis_min_set || dis_temp < dis_min)
            {
                dis_min = dis_temp;
                is_dis_min_set = true;
            }
        }
        return dis_min;
    }
};

struct range_range
{
    template <typename Range1, typename Range2, typename Strategy>
    static inline
    typename distance_result
        <
            typename point_type<Range1>::type,
            typename point_type<Range2>::type,
            Strategy
        >::type
    apply(Range1 const& r1, Range2 const& r2, Strategy const& strategy)
    {

        typedef typename distance_result
            <
                typename point_type<Range1>::type,
                typename point_type<Range2>::type,
                Strategy
            >::type result_type;

        typedef typename boost::range_size<Range1>::type size_type;

        boost::geometry::detail::throw_on_empty_input(r1);
        boost::geometry::detail::throw_on_empty_input(r2);

        size_type const n = boost::size(r1);
        result_type dis_max = 0;

#ifdef BOOST_GEOMETRY_ENABLE_SIMILARITY_RTREE
        namespace bgi = boost::geometry::index;
        typedef typename point_type<Range1>::type point_t;
        typedef bgi::rtree<point_t, bgi::linear<4> > rtree_type;
        rtree_type rtree(boost::begin(r2), boost::end(r2));
        point_t res;
#endif

        for (size_type i = 0 ; i < n ; i++)
        {
#ifdef BOOST_GEOMETRY_ENABLE_SIMILARITY_RTREE
            size_type found = rtree.query(bgi::nearest(range::at(r1, i), 1), &res);
            result_type dis_min = strategy.apply(range::at(r1,i), res);
#else
            result_type dis_min = point_range::apply(range::at(r1, i), r2, strategy);
#endif
            if (dis_min > dis_max )
            {
                dis_max = dis_min;
            }
        }
        return dis_max;
    }
};


struct range_multi_range
{
    template <typename Range, typename Multi_range, typename Strategy>
    static inline
    typename distance_result
        <
            typename point_type<Range>::type,
            typename point_type<Multi_range>::type,
            Strategy
        >::type
    apply(Range const& rng, Multi_range const& mrng, Strategy const& strategy)
    {
        typedef typename distance_result
            <
                typename point_type<Range>::type,
                typename point_type<Multi_range>::type,
                Strategy
            >::type result_type;
        typedef typename boost::range_size<Multi_range>::type size_type;

        boost::geometry::detail::throw_on_empty_input(rng);
        boost::geometry::detail::throw_on_empty_input(mrng);

        size_type b = boost::size(mrng);
        result_type haus_dis = 0;

        for (size_type j = 0 ; j < b ; j++)
        {
            result_type dis_max = range_range::apply(rng, range::at(mrng, j), strategy);
            if (dis_max > haus_dis)
            {
                haus_dis = dis_max;
            }
        }

        return haus_dis;
    }
};


struct multi_range_multi_range
{
    template <typename Multi_Range1, typename Multi_range2, typename Strategy>
    static inline
    typename distance_result
        <
            typename point_type<Multi_Range1>::type,
            typename point_type<Multi_range2>::type,
            Strategy
        >::type
    apply(Multi_Range1 const& mrng1, Multi_range2 const& mrng2, Strategy const& strategy)
    {
        typedef typename distance_result
            <
                typename point_type<Multi_Range1>::type,
                typename point_type<Multi_range2>::type,
                Strategy
            >::type result_type;
        typedef typename boost::range_size<Multi_Range1>::type size_type;

        boost::geometry::detail::throw_on_empty_input(mrng1);
        boost::geometry::detail::throw_on_empty_input(mrng2);
        
        size_type n = boost::size(mrng1);
        result_type haus_dis = 0;

        for (size_type i = 0 ; i < n ; i++)
        {
            result_type dis_max = range_multi_range::apply(range::at(mrng1, i), mrng2, strategy);
            if (dis_max > haus_dis)
            {
                haus_dis = dis_max;
            }
        }
        return haus_dis;
    }
};

}} // namespace detail::hausdorff_distance
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{
template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type
>
struct discrete_hausdorff_distance : not_implemented<Tag1, Tag2>
{};

// Specialization for point and multi_point
template <typename Point, typename MultiPoint>
struct discrete_hausdorff_distance<Point, MultiPoint, point_tag, multi_point_tag>
    : detail::discrete_hausdorff_distance::point_range
{};

// Specialization for linestrings
template <typename Linestring1, typename Linestring2>
struct discrete_hausdorff_distance<Linestring1, Linestring2, linestring_tag, linestring_tag>
    : detail::discrete_hausdorff_distance::range_range
{};

// Specialization for multi_point-multi_point
template <typename MultiPoint1, typename MultiPoint2>
struct discrete_hausdorff_distance<MultiPoint1, MultiPoint2, multi_point_tag, multi_point_tag>
    : detail::discrete_hausdorff_distance::range_range
{};

// Specialization for Linestring and MultiLinestring
template <typename Linestring, typename MultiLinestring>
struct discrete_hausdorff_distance<Linestring, MultiLinestring, linestring_tag, multi_linestring_tag>
    : detail::discrete_hausdorff_distance::range_multi_range
{};

// Specialization for MultiLinestring and MultiLinestring
template <typename MultiLinestring1, typename MultiLinestring2>
struct discrete_hausdorff_distance<MultiLinestring1, MultiLinestring2, multi_linestring_tag, multi_linestring_tag>
    : detail::discrete_hausdorff_distance::multi_range_multi_range
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

// Algorithm overload using explicitly passed Pt-Pt distance strategy

/*!
\brief Calculate discrete Hausdorff distance between two geometries (currently
    works for LineString-LineString, MultiPoint-MultiPoint, Point-MultiPoint,
    MultiLineString-MultiLineString) using specified strategy.
\ingroup discrete_hausdorff_distance
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy A type fulfilling a DistanceStrategy concept
\param geometry1 Input geometry
\param geometry2 Input geometry
\param strategy Distance strategy to be used to calculate Pt-Pt distance

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/discrete_hausdorff_distance.qbk]}

\qbk{
[heading Available Strategies]
\* [link geometry.reference.strategies.strategy_distance_pythagoras Pythagoras (cartesian)]
\* [link geometry.reference.strategies.strategy_distance_haversine Haversine (spherical)]
[/ \* more (currently extensions): Vincenty\, Andoyer (geographic) ]

[heading Example]
[discrete_hausdorff_distance_strategy]
[discrete_hausdorff_distance_strategy_output]
}
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline
typename distance_result
    <
        typename point_type<Geometry1>::type,
        typename point_type<Geometry2>::type,
        Strategy
    >::type
discrete_hausdorff_distance(Geometry1 const& geometry1,
                            Geometry2 const& geometry2,
                            Strategy const& strategy)
{
    return dispatch::discrete_hausdorff_distance
        <
            Geometry1, Geometry2
        >::apply(geometry1, geometry2, strategy);
}

/*!
\brief Calculate discrete Hausdorff distance between two geometries (currently
    works for LineString-LineString, MultiPoint-MultiPoint, Point-MultiPoint,
    MultiLineString-MultiLineString).
\ingroup discrete_hausdorff_distance
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 Input geometry
\param geometry2 Input geometry

\qbk{[include reference/algorithms/discrete_hausdorff_distance.qbk]}

\qbk{
[heading Example]
[discrete_hausdorff_distance]
[discrete_hausdorff_distance_output]
}
*/
template <typename Geometry1, typename Geometry2>
inline
typename distance_result
    <
        typename point_type<Geometry1>::type,
        typename point_type<Geometry2>::type
    >::type
discrete_hausdorff_distance(Geometry1 const& geometry1,
                            Geometry2 const& geometry2)
{
    typedef typename strategy::distance::services::default_strategy
        <
            point_tag, point_tag,
            typename point_type<Geometry1>::type,
            typename point_type<Geometry2>::type
        >::type strategy_type;

    return discrete_hausdorff_distance(geometry1, geometry2, strategy_type());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISCRETE_HAUSDORFF_DISTANCE_HPP

/* discrete_hausdorff_distance.hpp
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
*/