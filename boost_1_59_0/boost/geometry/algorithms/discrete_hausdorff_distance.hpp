// Boost.Geometry

// Copyright (c) 2018 Yaghyavardhan Singh Khangarot, Hyderabad, India.
// Contributed and/or modified by Yaghyavardhan Singh Khangarot,
//   as part of Google Summer of Code 2018 program.

// This file was modified by Oracle on 2018-2021.
// Modifications copyright (c) 2018-2021, Oracle and/or its affiliates.
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

#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>
#include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/discrete_distance/cartesian.hpp>
#include <boost/geometry/strategies/discrete_distance/geographic.hpp>
#include <boost/geometry/strategies/discrete_distance/spherical.hpp>
#include <boost/geometry/strategies/distance_result.hpp>
#include <boost/geometry/util/range.hpp>

// Note that in order for this to work umbrella strategy has to contain
// index strategies.
#ifdef BOOST_GEOMETRY_ENABLE_SIMILARITY_RTREE
#include <boost/geometry/index/rtree.hpp>
#endif // BOOST_GEOMETRY_ENABLE_SIMILARITY_RTREE

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace discrete_hausdorff_distance
{

// TODO: The implementation should calculate comparable distances

struct point_range
{
    template <typename Point, typename Range, typename Strategies>
    static inline auto apply(Point const& pnt, Range const& rng,
                             Strategies const& strategies)
    {
        typedef typename distance_result
            <
                Point,
                typename point_type<Range>::type,
                Strategies
            >::type result_type;

        typedef typename boost::range_size<Range>::type size_type;

        boost::geometry::detail::throw_on_empty_input(rng);

        auto const strategy = strategies.distance(dummy_point(), dummy_point());

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
    template <typename Range1, typename Range2, typename Strategies>
    static inline auto apply(Range1 const& r1, Range2 const& r2,
                             Strategies const& strategies)
    {
        typedef typename distance_result
            <
                typename point_type<Range1>::type,
                typename point_type<Range2>::type,
                Strategies
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
            result_type dis_min = point_range::apply(range::at(r1, i), r2, strategies);
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
    template <typename Range, typename Multi_range, typename Strategies>
    static inline auto apply(Range const& rng, Multi_range const& mrng,
                             Strategies const& strategies)
    {
        typedef typename distance_result
            <
                typename point_type<Range>::type,
                typename point_type<Multi_range>::type,
                Strategies
            >::type result_type;
        typedef typename boost::range_size<Multi_range>::type size_type;

        boost::geometry::detail::throw_on_empty_input(rng);
        boost::geometry::detail::throw_on_empty_input(mrng);

        size_type b = boost::size(mrng);
        result_type haus_dis = 0;

        for (size_type j = 0 ; j < b ; j++)
        {
            result_type dis_max = range_range::apply(rng, range::at(mrng, j), strategies);
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
    template <typename Multi_Range1, typename Multi_range2, typename Strategies>
    static inline auto apply(Multi_Range1 const& mrng1, Multi_range2 const& mrng2,
                             Strategies const& strategies)
    {
        typedef typename distance_result
            <
                typename point_type<Multi_Range1>::type,
                typename point_type<Multi_range2>::type,
                Strategies
            >::type result_type;
        typedef typename boost::range_size<Multi_Range1>::type size_type;

        boost::geometry::detail::throw_on_empty_input(mrng1);
        boost::geometry::detail::throw_on_empty_input(mrng2);
        
        size_type n = boost::size(mrng1);
        result_type haus_dis = 0;

        for (size_type i = 0 ; i < n ; i++)
        {
            result_type dis_max = range_multi_range::apply(range::at(mrng1, i), mrng2, strategies);
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


namespace resolve_strategy {

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct discrete_hausdorff_distance
{
    template <typename Geometry1, typename Geometry2>
    static inline auto apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Strategies const& strategies)
    {
        return dispatch::discrete_hausdorff_distance
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategies);
    }
};

template <typename Strategy>
struct discrete_hausdorff_distance<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline auto apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using strategies::discrete_distance::services::strategy_converter;
        return dispatch::discrete_hausdorff_distance
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct discrete_hausdorff_distance<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline auto apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             default_strategy const&)
    {
        typedef typename strategies::discrete_distance::services::default_strategy
            <
                Geometry1, Geometry2
            >::type strategies_type;

        return dispatch::discrete_hausdorff_distance
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategies_type());
    }
};

} // namespace resolve_strategy


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
inline auto discrete_hausdorff_distance(Geometry1 const& geometry1,
                                        Geometry2 const& geometry2,
                                        Strategy const& strategy)
{
    return resolve_strategy::discrete_hausdorff_distance
        <
            Strategy
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
inline auto discrete_hausdorff_distance(Geometry1 const& geometry1,
                                        Geometry2 const& geometry2)
{
    return resolve_strategy::discrete_hausdorff_distance
        <
            default_strategy
        >::apply(geometry1, geometry2, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISCRETE_HAUSDORFF_DISTANCE_HPP

/* discrete_hausdorff_distance.hpp
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
*/