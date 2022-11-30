// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_LINE_INTERPOLATE_HPP

#include <iterator>
#include <type_traits>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/line_interpolate/cartesian.hpp>
#include <boost/geometry/strategies/line_interpolate/geographic.hpp>
#include <boost/geometry/strategies/line_interpolate/spherical.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace line_interpolate
{

struct convert_and_push_back
{
    template <typename Range, typename Point>
    static inline void apply(Point const& p, Range& range)
    {
        typename boost::range_value<Range>::type p2;
        geometry::detail::conversion::convert_point_to_point(p, p2);
        range::push_back(range, p2);
    }
};

struct convert_and_assign
{
    template <typename Point1, typename Point2>
    static inline void apply(Point1 const& p1, Point2& p2)
    {
        geometry::detail::conversion::convert_point_to_point(p1, p2);
    }

};


/*!
\brief Internal, calculates interpolation point of a linestring using iterator pairs and
    specified strategy
*/
template <typename Policy>
struct interpolate_range
{
    template
    <
        typename Range,
        typename Distance,
        typename PointLike,
        typename Strategies
    >
    static inline void apply(Range const& range,
                             Distance const& max_distance,
                             PointLike & pointlike,
                             Strategies const& strategies)
    {
        typedef typename boost::range_iterator<Range const>::type iterator_t;
        typedef typename boost::range_value<Range const>::type point_t;

        iterator_t it = boost::begin(range);
        iterator_t end = boost::end(range);

        if (it == end) // empty(range)
        {
            BOOST_THROW_EXCEPTION(empty_input_exception());
            return;
        }
        if (max_distance <= 0) //non positive distance
        {
            Policy::apply(*it, pointlike);
            return;
        }

        auto const pp_strategy = strategies.distance(dummy_point(), dummy_point());
        auto const strategy = strategies.line_interpolate(range);

        typedef decltype(pp_strategy.apply(
                    std::declval<point_t>(), std::declval<point_t>())) distance_type;

        iterator_t prev = it++;
        distance_type repeated_distance = max_distance;
        distance_type prev_distance = 0;
        distance_type current_distance = 0;
        point_t start_p = *prev;

        for ( ; it != end ; ++it)
        {
            distance_type dist = pp_strategy.apply(*prev, *it);
            current_distance = prev_distance + dist;

            while (current_distance >= repeated_distance)
            {
                point_t p;
                distance_type diff_distance = current_distance - prev_distance;
                BOOST_ASSERT(diff_distance != distance_type(0));
                strategy.apply(start_p, *it,
                               (repeated_distance - prev_distance)/diff_distance,
                               p,
                               diff_distance);
                Policy::apply(p, pointlike);
                if (std::is_same<PointLike, point_t>::value)
                {
                    return;
                }
                start_p = p;
                prev_distance = repeated_distance;
                repeated_distance += max_distance;
            }
            prev_distance = current_distance;
            prev = it;
            start_p = *prev;
        }

        // case when max_distance is larger than linestring's length
        // return the last point in range (range is not empty)
        if (repeated_distance == max_distance)
        {
            Policy::apply(*(end-1), pointlike);
        }
    }
};

template <typename Policy>
struct interpolate_segment
{
    template <typename Segment, typename Distance, typename Pointlike, typename Strategy>
    static inline void apply(Segment const& segment,
                             Distance const& max_distance,
                             Pointlike & point,
                             Strategy const& strategy)
    {
        interpolate_range<Policy>().apply(segment_view<Segment>(segment),
                                          max_distance, point, strategy);
    }
};

}} // namespace detail::line_interpolate
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Pointlike,
    typename Tag1 = typename tag<Geometry>::type,
    typename Tag2 = typename tag<Pointlike>::type
>
struct line_interpolate
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry, Pointlike);
};


template <typename Geometry, typename Pointlike>
struct line_interpolate<Geometry, Pointlike, linestring_tag, point_tag>
    : detail::line_interpolate::interpolate_range
        <
            detail::line_interpolate::convert_and_assign
        >
{};

template <typename Geometry, typename Pointlike>
struct line_interpolate<Geometry, Pointlike, linestring_tag, multi_point_tag>
    : detail::line_interpolate::interpolate_range
        <
            detail::line_interpolate::convert_and_push_back
        >
{};

template <typename Geometry, typename Pointlike>
struct line_interpolate<Geometry, Pointlike, segment_tag, point_tag>
    : detail::line_interpolate::interpolate_segment
        <
            detail::line_interpolate::convert_and_assign
        >
{};

template <typename Geometry, typename Pointlike>
struct line_interpolate<Geometry, Pointlike, segment_tag, multi_point_tag>
    : detail::line_interpolate::interpolate_segment
        <
            detail::line_interpolate::convert_and_push_back
        >
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct line_interpolate
{
    template <typename Geometry, typename Distance, typename Pointlike>
    static inline void apply(Geometry const& geometry,
                             Distance const& max_distance,
                             Pointlike & pointlike,
                             Strategies const& strategies)
    {
        dispatch::line_interpolate
            <
                Geometry, Pointlike
            >::apply(geometry, max_distance, pointlike, strategies);
    }
};

template <typename Strategy>
struct line_interpolate<Strategy, false>
{
    template <typename Geometry, typename Distance, typename Pointlike>
    static inline void apply(Geometry const& geometry,
                             Distance const& max_distance,
                             Pointlike & pointlike,
                             Strategy const& strategy)
    {        
        using strategies::line_interpolate::services::strategy_converter;

        dispatch::line_interpolate
            <
                Geometry, Pointlike
            >::apply(geometry, max_distance, pointlike,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct line_interpolate<default_strategy, false>
{
    template <typename Geometry, typename Distance, typename Pointlike>
    static inline void apply(Geometry const& geometry,
                             Distance const& max_distance,
                             Pointlike & pointlike,
                             default_strategy)
    {        
        typedef typename strategies::line_interpolate::services::default_strategy
            <
                Geometry
            >::type strategy_type;

        dispatch::line_interpolate
            <
                Geometry, Pointlike
            >::apply(geometry, max_distance, pointlike, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry>
struct line_interpolate
{
    template <typename Distance, typename Pointlike, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Distance const& max_distance,
                             Pointlike & pointlike,
                             Strategy const& strategy)
    {
        return resolve_strategy::line_interpolate
                <
                    Strategy
                >::apply(geometry, max_distance, pointlike, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct line_interpolate<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Pointlike, typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Pointlike const& m_pointlike;
        Strategy const& m_strategy;

        visitor(Pointlike const& pointlike, Strategy const& strategy)
            : m_pointlike(pointlike)
            , m_strategy(strategy)
        {}

        template <typename Geometry, typename Distance>
        void operator()(Geometry const& geometry, Distance const& max_distance) const
        {
            line_interpolate<Geometry>::apply(geometry, max_distance,
                                              m_pointlike, m_strategy);
        }
    };

    template <typename Distance, typename Pointlike, typename Strategy>
    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          Distance const& max_distance,
          Pointlike & pointlike,
          Strategy const& strategy)
    {
        boost::apply_visitor(
            visitor<Pointlike, Strategy>(pointlike, strategy),
            geometry,
            max_distance
        );
    }
};

} // namespace resolve_variant

/*!
\brief     Returns one or more points interpolated along a LineString \brief_strategy
\ingroup line_interpolate
\tparam Geometry Any type fulfilling a LineString concept
\tparam Distance A numerical distance measure
\tparam Pointlike Any type fulfilling Point or Multipoint concept
\tparam Strategy A type fulfilling a LineInterpolatePointStrategy concept
\param geometry Input geometry
\param max_distance Distance threshold (in units depending on coordinate system)
representing the spacing between the points
\param pointlike Output: either a Point (exactly one point will be constructed) or
a MultiPoint (depending on the max_distance one or more points will be constructed)
\param strategy line_interpolate strategy to be used for interpolation of
points

\qbk{[include reference/algorithms/line_interpolate.qbk]}

\qbk{distinguish,with strategy}

\qbk{
[heading Available Strategies]
\* [link geometry.reference.strategies.strategy_line_interpolate_cartesian Cartesian]
\* [link geometry.reference.strategies.strategy_line_interpolate_spherical Spherical]
\* [link geometry.reference.strategies.strategy_line_interpolate_geographic Geographic]

[heading Example]
[line_interpolate_strategy]
[line_interpolate_strategy_output]

[heading See also]
\* [link geometry.reference.algorithms.densify densify]
}
 */
template
<
    typename Geometry,
    typename Distance,
    typename Pointlike,
    typename Strategy
>
inline void line_interpolate(Geometry const& geometry,
                             Distance const& max_distance,
                             Pointlike & pointlike,
                             Strategy const& strategy)
{
    concepts::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    return resolve_variant::line_interpolate<Geometry>
                          ::apply(geometry, max_distance, pointlike, strategy);
}


/*!
\brief     Returns one or more points interpolated along a LineString.
\ingroup line_interpolate
\tparam Geometry Any type fulfilling a LineString concept
\tparam Distance A numerical distance measure
\tparam Pointlike Any type fulfilling Point or Multipoint concept
\param geometry Input geometry
\param max_distance Distance threshold (in units depending on coordinate system)
representing the spacing between the points
\param pointlike Output: either a Point (exactly one point will be constructed) or
a MultiPoint (depending on the max_distance one or more points will be constructed)

\qbk{[include reference/algorithms/line_interpolate.qbk]

[heading Example]
[line_interpolate]
[line_interpolate_output]

[heading See also]
\* [link geometry.reference.algorithms.densify densify]
}
 */
template<typename Geometry, typename Distance, typename Pointlike>
inline void line_interpolate(Geometry const& geometry,
                             Distance const& max_distance,
                             Pointlike & pointlike)
{
    concepts::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    return resolve_variant::line_interpolate<Geometry>
                          ::apply(geometry, max_distance, pointlike, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
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
*/