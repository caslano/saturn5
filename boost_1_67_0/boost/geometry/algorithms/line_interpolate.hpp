// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018, 2019 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_LINE_INTERPOLATE_HPP

#include <iterator>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/line_interpolate.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace line_interpolate
{

struct convert_and_push_back
{
    template <typename Range, typename Point>
    inline void apply(Point const& p, Range& range)
    {
        typename boost::range_value<Range>::type p2;
        geometry::detail::conversion::convert_point_to_point(p, p2);
        range::push_back(range, p2);
    }
};

struct convert_and_assign
{
    template <typename Point1, typename Point2>
    inline void apply(Point1 const& p1, Point2& p2)
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
        typename Strategy
    >
    static inline void apply(Range const& range,
                             Distance const& max_distance,
                             PointLike & pointlike,
                             Strategy const& strategy)
    {
        Policy policy;

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
            policy.apply(*it, pointlike);
            return;
        }

        iterator_t prev = it++;
        Distance repeated_distance = max_distance;
        Distance prev_distance = 0;
        Distance current_distance = 0;
        point_t start_p = *prev;

        for ( ; it != end ; ++it)
        {
            Distance dist = strategy.get_distance_pp_strategy().apply(*prev, *it);
            current_distance = prev_distance + dist;

            while (current_distance >= repeated_distance)
            {
                point_t p;
                Distance diff_distance = current_distance - prev_distance;
                BOOST_ASSERT(diff_distance != Distance(0));
                strategy.apply(start_p, *it,
                               (repeated_distance - prev_distance)/diff_distance,
                               p,
                               diff_distance);
                policy.apply(p, pointlike);
                if (boost::is_same<PointLike, point_t>::value)
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
            policy.apply(*(end-1), pointlike);
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
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
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

struct line_interpolate
{
    template
    <
        typename Geometry,
        typename Distance,
        typename Pointlike,
        typename Strategy
    >
    static inline void apply(Geometry const& geometry,
                             Distance const& max_distance,
                             Pointlike & pointlike,
                             Strategy const& strategy)
    {
        dispatch::line_interpolate<Geometry, Pointlike>::apply(geometry,
                                                               max_distance,
                                                               pointlike,
                                                               strategy);
    }

    template <typename Geometry, typename Distance, typename Pointlike>
    static inline void apply(Geometry const& geometry,
                             Distance const& max_distance,
                             Pointlike & pointlike,
                             default_strategy)
    {        
        typedef typename strategy::line_interpolate::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type strategy_type;

        dispatch::line_interpolate<Geometry, Pointlike>::apply(geometry,
                                                               max_distance,
                                                               pointlike,
                                                               strategy_type());
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
        return resolve_strategy::line_interpolate::apply(geometry,
                                                         max_distance,
                                                         pointlike,
                                                         strategy);
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
          double const& max_distance,
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
\brief 	Returns one or more points interpolated along a LineString \brief_strategy
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
\brief 	Returns one or more points interpolated along a LineString.
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