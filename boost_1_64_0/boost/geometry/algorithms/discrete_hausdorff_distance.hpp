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
fbLlK3M7cXwPWyGaOmcVG9orMfSzFE1dq8rB1ql5Vomm8l5lsBplsNdR4Os2K5kNrEHwzUVs3lBOt+eDpnLrh6bmUhDYev0dpmhqTgxD09cANH0PhKa/6wpNf9cVmr4GgD2pv8MUTb3nJBFN/Q3YdWhqDqZAjp6in5/H7LvKlinlyFQ8s9HU2HPBktU+nw+2Qc35QoMVo6n1UGIoV2ooVw62UT8vQFPff1ZlsBplEDMa/G1L0d/LCPaMusezOZvjNVM2LzQ1l+xoKi6+BgtEU3M+GE3FMxRsE/30ONZkO1uYMnxfV7jBItH0tcpgMWCbVW7jwFJVjhIMlmSwZLBnlaWCPafOROlgWyzO392XiabykG2wXLA01Zd8sOfV3C0E26piVgy2jX72fGH8frYSg5WiqX2inIz3nnSL83dZVoO9QD+Pp0WFs1kP37YX6ee+LQOeYPNWlrA5fD5bIBn35SV1Px0MlqHWUSiausaFGcqFo6m1Eomm8hdtaC8GTc2lODT1t1ISlOH7d5PAtqv3xSYrk/GRpRosXZlcq8gylcn8JMtGU99NmKsMx5CvTHJLVqgMz9DFYDvUeihBU/tLqcHKDVaJpnJUZbAasJ36fcbvgKk9xIqm5pkNTZ0jvQxmR1Pz0xdN7SGBaCouwYZyoWhqzoeh6fVniEskml5/hrHHGCzOEJcEw/iSDHFJNpRLrTMuMTPSwV629Oon64Es02DZZDawt9wuNK61gMACKLfLsixW1i1ZEZkNLCJpYihbqSon7ZGVK7s9hnuiKsFesSxy7C9sVcokD2Q1yiQPZJYjdddpBdN12pTJGMi8lMlr5WR2ZfI6F5mvMrk+kAUaLFiZ5IEs1GBhyuS+iizcUC5SmezJZNGG8cUokzMmWZzBEgw5SjLkKFmZ3KOTpRryl65M3pdAlmkol22wXDT9fU/K5H6MrNBgxcrk/ZFkJWQ2sId+/OEntgplJ9/v34atxjB3LQXOhp/LsoJlqc9C2cBe1d/NpExyS2ZXJrkl81WG7QUa6gxW5vQZfkM/w9DUd32EK5PrNFmkMprXYtFkNrBFBzfPY4tXJt/pS5as6pTnS2SpyvC8lA6227LMMQfZMg2WjabObrkGy1cmYycrVCaxJis2WInBSg1jKDdYpaHOKmVO7wUA26PPYO+CqXOBFU1/jwuaeo3IC03dr9jR1D2eL5q+t0dTz5qD0fS9vcHC0NQzq3A0dX6JRFN/5yCazCZW+7f62OIN40tEU8/I1oFlq+cvKWgqR2kGyzDUmWUol2OwPDQ1zwrQ1DwrMvTllKG9s4ZyZYa+VKCpM/QVQ3vVaGpO3ERT+XM9Wre5K8PP+HmgqXXkjaZeK/dBU3Pez1BnkMFCDGMYZmhvjGF8EYb2ogx1zjJYrKG9eDT9NxecTP3NBTS9/tD0+jOMLwNNPdfPUnYybMpXbDlo6v1neYa4FBisCE3tS6cMdtYQ6zKDVdRpi6OugO21LJ4p758gq1YmsSa7iaa+e8P1GO3JYMsWdzvM5kWG5eS1cjK7MrmmkvnWaf4JgWD71PcrBiuTeUYWqkzmGVmYMhk7WbjBIg11Rhv6GWPoZ5yhzgRDnUmGfiYbyqUa+pJu6Eumob1sQ3u5hvbylcncJSs01FmsTF5XIyvRRvsEW+n/+Lr7oOjeOQzgJ0IIayaExYNFCCGEEEJGCCEswiIswiIswiKEEEIIIYQQQgghhLAIISxCCIuQl0uc73PtNdP1x2/mN/N5vvfbud/O6dxnTR32xeIZBOzAxB2Jxb4HdiwW96KwZKPRYl6CtcAyZLd8/isvk1pW4mIOgeXE4v0QWCeZtme3sV4yvX79pg6DppzDYjG/wPI=
*/