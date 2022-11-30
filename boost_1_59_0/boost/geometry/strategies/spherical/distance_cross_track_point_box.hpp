// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_POINT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_POINT_BOX_HPP


#include <type_traits>

#include <boost/config.hpp>
#include <boost/concept_check.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

namespace details
{

template <typename ReturnType>
class cross_track_point_box_generic
{
public :

    template
    <
            typename Point,
            typename Box,
            typename Strategy
    >
    ReturnType static inline apply (Point const& point,
                                    Box const& box,
                                    Strategy ps_strategy)
    {
        // this method assumes that the coordinates of the point and
        // the box are normalized

        typedef typename point_type<Box>::type box_point_type;

        box_point_type bottom_left, bottom_right, top_left, top_right;
        geometry::detail::assign_box_corners(box,
                                             bottom_left, bottom_right,
                                             top_left, top_right);

        ReturnType const plon = geometry::get_as_radian<0>(point);
        ReturnType const plat = geometry::get_as_radian<1>(point);

        ReturnType const lon_min = geometry::get_as_radian<0>(bottom_left);
        ReturnType const lat_min = geometry::get_as_radian<1>(bottom_left);
        ReturnType const lon_max = geometry::get_as_radian<0>(top_right);
        ReturnType const lat_max = geometry::get_as_radian<1>(top_right);

        ReturnType const pi = math::pi<ReturnType>();
        ReturnType const two_pi = math::two_pi<ReturnType>();

        typedef typename point_type<Box>::type box_point_type;

        // First check if the point is within the band defined by the
        // minimum and maximum longitude of the box; if yes, determine
        // if the point is above, below or inside the box and compute
        // the distance (easy in this case)
        //
        // Notice that the point may not be inside the longitude range
        // of the box, but the shifted point may be inside the
        // longitude range of the box; in this case the point is still
        // considered as inside the longitude range band of the box
        if ((plon >= lon_min && plon <= lon_max) || plon + two_pi <= lon_max)
        {
            if (plat > lat_max)
            {
                return geometry::strategy::distance::services::result_from_distance
                        <
                            Strategy, Point, box_point_type
                        >::apply(ps_strategy, ps_strategy
                                 .vertical_or_meridian(plat, lat_max));
            }
            else if (plat < lat_min)
            {
                return geometry::strategy::distance::services::result_from_distance
                        <
                            Strategy, Point, box_point_type
                        >::apply(ps_strategy, ps_strategy
                                 .vertical_or_meridian(lat_min, plat));
            }
            else
            {
                BOOST_GEOMETRY_ASSERT(plat >= lat_min && plat <= lat_max);
                return ReturnType(0);
            }
        }

        // Otherwise determine which among the two medirian segments of the
        // box the point is closest to, and compute the distance of
        // the point to this closest segment

        // Below lon_midway is the longitude of the meridian that:
        // (1) is midway between the meridians of the left and right
        //     meridians of the box, and
        // (2) does not intersect the box
        ReturnType const two = 2.0;
        bool use_left_segment;
        if (lon_max > pi)
        {
            // the box crosses the antimeridian

            // midway longitude = lon_min - (lon_min + (lon_max - 2 * pi)) / 2;
            ReturnType const lon_midway = (lon_min - lon_max) / two + pi;
            BOOST_GEOMETRY_ASSERT(lon_midway >= -pi && lon_midway <= pi);

            use_left_segment = plon > lon_midway;
        }
        else
        {
            // the box does not cross the antimeridian

            ReturnType const lon_sum = lon_min + lon_max;
            if (math::equals(lon_sum, ReturnType(0)))
            {
                // special case: the box is symmetric with respect to
                // the prime meridian; the midway meridian is the antimeridian

                use_left_segment = plon < lon_min;
            }
            else
            {
                // midway long. = lon_min - (2 * pi - (lon_max - lon_min)) / 2;
                ReturnType lon_midway = (lon_min + lon_max) / two - pi;

                // normalize the midway longitude
                if (lon_midway > pi)
                {
                    lon_midway -= two_pi;
                }
                else if (lon_midway < -pi)
                {
                    lon_midway += two_pi;
                }
                BOOST_GEOMETRY_ASSERT(lon_midway >= -pi && lon_midway <= pi);

                // if lon_sum is positive the midway meridian is left
                // of the box, or right of the box otherwise
                use_left_segment = lon_sum > 0
                        ? (plon < lon_min && plon >= lon_midway)
                        : (plon <= lon_max || plon > lon_midway);
            }
        }

        return use_left_segment
                ? ps_strategy.apply(point, bottom_left, top_left)
                : ps_strategy.apply(point, bottom_right, top_right);
    }
};

}  //namespace details

/*!
\brief Strategy functor for distance point to box calculation
\ingroup strategies
\details Class which calculates the distance of a point to a box, for
points and boxes on a sphere or globe
\tparam CalculationType \tparam_calculation
\tparam Strategy underlying point-point distance strategy
\qbk{
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}
*/
template
<
    typename CalculationType = void,
    typename Strategy = haversine<double, CalculationType>
>
class cross_track_point_box
{
public:
    template <typename Point, typename Box>
    struct return_type
        : services::return_type<Strategy, Point, typename point_type<Box>::type>
    {};

    typedef typename Strategy::radius_type radius_type;

    // strategy getters

    // point-segment strategy getters
    struct distance_ps_strategy
    {
        typedef cross_track<CalculationType, Strategy> type;
    };

    typedef typename strategy::distance::services::comparable_type
        <
            Strategy
        >::type pp_comparable_strategy;

    typedef std::conditional_t
        <
            std::is_same
                <
                    pp_comparable_strategy,
                    Strategy
                >::value,
            typename strategy::distance::services::comparable_type
                <
                    typename distance_ps_strategy::type
                >::type,
            typename distance_ps_strategy::type
        > ps_strategy_type;

    // constructors

    inline cross_track_point_box()
    {}

    explicit inline cross_track_point_box(typename Strategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline cross_track_point_box(Strategy const& s)
        : m_strategy(s)
    {}


    // methods

    // It might be useful in the future
    // to overload constructor with strategy info.
    // crosstrack(...) {}

    template <typename Point, typename Box>
    inline typename return_type<Point, Box>::type
    apply(Point const& point, Box const& box) const
    {
#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointDistanceStrategy
                    <
                        Strategy, Point, typename point_type<Box>::type
                    >)
            );
#endif
        typedef typename return_type<Point, Box>::type return_type;
        return details::cross_track_point_box_generic
                    <return_type>::apply(point, box,
                                         ps_strategy_type(m_strategy));
    }

    inline typename Strategy::radius_type radius() const
    {
        return m_strategy.radius();
    }

private:
    Strategy m_strategy;
};



#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType, typename Strategy>
struct tag<cross_track_point_box<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename CalculationType, typename Strategy, typename P, typename Box>
struct return_type<cross_track_point_box<CalculationType, Strategy>, P, Box>
    : cross_track_point_box
        <
            CalculationType, Strategy
        >::template return_type<P, Box>
{};


template <typename CalculationType, typename Strategy>
struct comparable_type<cross_track_point_box<CalculationType, Strategy> >
{
    typedef cross_track_point_box
        <
            CalculationType, typename comparable_type<Strategy>::type
        > type;
};


template <typename CalculationType, typename Strategy>
struct get_comparable<cross_track_point_box<CalculationType, Strategy> >
{
    typedef cross_track_point_box<CalculationType, Strategy> this_strategy;
    typedef typename comparable_type<this_strategy>::type comparable_type;

public:
    static inline comparable_type apply(this_strategy const& strategy)
    {
        return comparable_type(strategy.radius());
    }
};


template <typename CalculationType, typename Strategy, typename P, typename Box>
struct result_from_distance
    <
        cross_track_point_box<CalculationType, Strategy>, P, Box
    >
{
private:
    typedef cross_track_point_box<CalculationType, Strategy> this_strategy;

    typedef typename this_strategy::template return_type
        <
            P, Box
        >::type return_type;

public:
    template <typename T>
    static inline return_type apply(this_strategy const& strategy,
                                    T const& distance)
    {
        Strategy s(strategy.radius());

        return result_from_distance
            <
                Strategy, P, typename point_type<Box>::type
            >::apply(s, distance);
    }
};


// define cross_track_point_box<default_point_segment_strategy> as
// default point-box strategy for the spherical equatorial coordinate system
template <typename Point, typename Box, typename Strategy>
struct default_strategy
    <
        point_tag, box_tag, Point, Box,
        spherical_equatorial_tag, spherical_equatorial_tag,
        Strategy
    >
{
    typedef cross_track_point_box
        <
            void,
            std::conditional_t
                <
                    std::is_void<Strategy>::value,
                    typename default_strategy
                        <
                            point_tag, point_tag,
                            Point, typename point_type<Box>::type,
                            spherical_equatorial_tag, spherical_equatorial_tag
                        >::type,
                    Strategy
                >
        > type;
};


template <typename Box, typename Point, typename Strategy>
struct default_strategy
    <
        box_tag, point_tag, Box, Point,
        spherical_equatorial_tag, spherical_equatorial_tag,
        Strategy
    >
{
    typedef typename default_strategy
        <
            point_tag, box_tag, Point, Box,
            spherical_equatorial_tag, spherical_equatorial_tag,
            Strategy
        >::type type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

/* distance_cross_track_point_box.hpp
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
*/