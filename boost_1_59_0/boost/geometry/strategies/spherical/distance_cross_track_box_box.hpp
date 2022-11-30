// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_BOX_BOX_HPP


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
class cross_track_box_box_generic
{
public :

    template <typename Point, typename PPStrategy, typename PSStrategy>
    ReturnType static inline diagonal_case(Point topA,
                                           Point topB,
                                           Point bottomA,
                                           Point bottomB,
                                           bool north_shortest,
                                           bool non_overlap,
                                           PPStrategy pp_strategy,
                                           PSStrategy ps_strategy)
    {
        if (north_shortest && non_overlap)
        {
            return pp_strategy.apply(topA, bottomB);
        }
        if (north_shortest && !non_overlap)
        {
            return ps_strategy.apply(topA, topB, bottomB);
        }
        if (!north_shortest && non_overlap)
        {
            return pp_strategy.apply(bottomA, topB);
        }
        return ps_strategy.apply(bottomA, topB, bottomB);
    }


    template
    <
            typename Box1,
            typename Box2,
            typename PPStrategy,
            typename PSStrategy
    >
    ReturnType static inline apply (Box1 const& box1,
                                    Box2 const& box2,
                                    PPStrategy pp_strategy,
                                    PSStrategy ps_strategy)
    {

        // this method assumes that the coordinates of the point and
        // the box are normalized

        typedef typename point_type<Box1>::type box_point_type1;
        typedef typename point_type<Box2>::type box_point_type2;

        box_point_type1 bottom_left1, bottom_right1, top_left1, top_right1;
        geometry::detail::assign_box_corners(box1,
                                             bottom_left1, bottom_right1,
                                             top_left1, top_right1);

        box_point_type2 bottom_left2, bottom_right2, top_left2, top_right2;
        geometry::detail::assign_box_corners(box2,
                                             bottom_left2, bottom_right2,
                                             top_left2, top_right2);

        ReturnType lon_min1 = geometry::get_as_radian<0>(bottom_left1);
        ReturnType const lat_min1 = geometry::get_as_radian<1>(bottom_left1);
        ReturnType lon_max1 = geometry::get_as_radian<0>(top_right1);
        ReturnType const lat_max1 = geometry::get_as_radian<1>(top_right1);

        ReturnType lon_min2 = geometry::get_as_radian<0>(bottom_left2);
        ReturnType const lat_min2 = geometry::get_as_radian<1>(bottom_left2);
        ReturnType lon_max2 = geometry::get_as_radian<0>(top_right2);
        ReturnType const lat_max2 = geometry::get_as_radian<1>(top_right2);

        ReturnType const two_pi = math::two_pi<ReturnType>();

        // Test which sides of the boxes are closer and if boxes cross
        // antimeridian
        bool right_wrap;

        if (lon_min2 > 0 && lon_max2 < 0) // box2 crosses antimeridian
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK_BOX_BOX
            std::cout << "(box2 crosses antimeridian)";
#endif
            right_wrap = lon_min2 - lon_max1 < lon_min1 - lon_max2;
            lon_max2 += two_pi;
            if (lon_min1 > 0 && lon_max1 < 0) // both boxes crosses antimeridian
            {
                lon_max1 += two_pi;
            }
        }
        else if (lon_min1 > 0 && lon_max1 < 0) // only box1 crosses antimeridian
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK_BOX_BOX
            std::cout << "(box1 crosses antimeridian)";
#endif
            return apply(box2, box1, pp_strategy, ps_strategy);
        }
        else
        {
            right_wrap = lon_max1 <= lon_min2
                         ? lon_min2 - lon_max1 < two_pi - (lon_max2 - lon_min1)
                         : lon_min1 - lon_max2 > two_pi - (lon_max1 - lon_min2);

        }

        // Check1: if box2 crosses the band defined by the
        // minimum and maximum longitude of box1; if yes, determine
        // if the box2 is above, below or intersects/is inside box1 and compute
        // the distance (easy in this case)

        bool lon_min12 = lon_min1 <= lon_min2;
        bool right = lon_max1 <= lon_min2;
        bool left = lon_min1 >= lon_max2;
        bool lon_max12 = lon_max1 <= lon_max2;

        if ((lon_min12 && !right)
                || (!left && !lon_max12)
                || (!lon_min12 && lon_max12))
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK_BOX_BOX
            std::cout << "(up-down)\n";
#endif
            if (lat_min1 > lat_max2)
            {
                return geometry::strategy::distance::services::result_from_distance
                    <
                        PSStrategy, box_point_type1, box_point_type2
                    >::apply(ps_strategy, ps_strategy
                               .vertical_or_meridian(lat_min1, lat_max2));
            }
            else if (lat_max1 < lat_min2)
            {
                return geometry::strategy::distance::services::result_from_distance
                    <
                        PSStrategy, box_point_type1, box_point_type2
                    >::apply(ps_strategy, ps_strategy
                             .vertical_or_meridian(lat_min2, lat_max1));
            }
            else
            {
                //BOOST_GEOMETRY_ASSERT(plat >= lat_min && plat <= lat_max);
                return ReturnType(0);
            }
        }

        // Check2: if box2 is right/left of box1
        // the max lat of box2 should be less than the max lat of box1
        bool bottom_max;

        ReturnType top_common = (std::min)(lat_max1, lat_max2);
        ReturnType bottom_common = (std::max)(lat_min1, lat_min2);

        // true if the closest points are on northern hemisphere
        bool north_shortest = top_common + bottom_common > 0;
        // true if box bands do not overlap
        bool non_overlap = top_common < bottom_common;

        if (north_shortest)
        {
            bottom_max = lat_max1 >= lat_max2;
        }
        else
        {
            bottom_max = lat_min1 <= lat_min2;
        }

#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK_BOX_BOX
        std::cout << "(diagonal)";
#endif
        if (bottom_max && !right_wrap)
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK_BOX_BOX
            std::cout << "(bottom left)";
#endif
            return diagonal_case(top_right2, top_left1,
                                 bottom_right2, bottom_left1,
                                 north_shortest, non_overlap,
                                 pp_strategy, ps_strategy);
        }
        if (bottom_max && right_wrap)
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK_BOX_BOX
            std::cout << "(bottom right)";
#endif
            return diagonal_case(top_left2, top_right1,
                                 bottom_left2, bottom_right1,
                                 north_shortest, non_overlap,
                                 pp_strategy, ps_strategy);
        }
        if (!bottom_max && !right_wrap)
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK_BOX_BOX
            std::cout << "(top left)";
#endif
            return diagonal_case(top_left1, top_right2,
                                 bottom_left1, bottom_right2,
                                 north_shortest, non_overlap,
                                 pp_strategy, ps_strategy);
        }
        if (!bottom_max && right_wrap)
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK_BOX_BOX
            std::cout << "(top right)";
#endif
            return diagonal_case(top_right1, top_left2,
                                 bottom_right1, bottom_left2,
                                 north_shortest, non_overlap,
                                 pp_strategy, ps_strategy);
        }
        return ReturnType(0);
    }
};

} //namespace details

/*!
\brief Strategy functor for distance box to box calculation
\ingroup strategies
\details Class which calculates the distance of a box to a box, for
boxes on a sphere or globe
\tparam CalculationType \tparam_calculation
\tparam Strategy underlying point-segment distance strategy, defaults
to cross track
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
class cross_track_box_box
{
public:
    template <typename Box1, typename Box2>
    struct return_type
        : services::return_type<Strategy,
                                typename point_type<Box1>::type,
                                typename point_type<Box2>::type>
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

    inline cross_track_box_box()
    {}

    explicit inline cross_track_box_box(typename Strategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline cross_track_box_box(Strategy const& s)
        : m_strategy(s)
    {}


    // It might be useful in the future
    // to overload constructor with strategy info.
    // crosstrack(...) {}

    template <typename Box1, typename Box2>
    inline typename return_type<Box1, Box2>::type
    apply(Box1 const& box1, Box2 const& box2) const
    {
#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointDistanceStrategy
                    <
                        Strategy,
                        typename point_type<Box1>::type,
                        typename point_type<Box2>::type
                    >)
            );
#endif
        typedef typename return_type<Box1, Box2>::type return_type;
        return details::cross_track_box_box_generic
                                <return_type>::apply(box1, box2,
                                                     m_strategy,
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
struct tag<cross_track_box_box<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_box_box type;
};


template <typename CalculationType, typename Strategy, typename Box1, typename Box2>
struct return_type<cross_track_box_box<CalculationType, Strategy>, Box1, Box2>
    : cross_track_box_box
        <
            CalculationType, Strategy
        >::template return_type<Box1, Box2>
{};


template <typename CalculationType, typename Strategy>
struct comparable_type<cross_track_box_box<CalculationType, Strategy> >
{
    typedef cross_track_box_box
        <
            CalculationType, typename comparable_type<Strategy>::type
        > type;
};


template <typename CalculationType, typename Strategy>
struct get_comparable<cross_track_box_box<CalculationType, Strategy> >
{
    typedef cross_track_box_box<CalculationType, Strategy> this_strategy;
    typedef typename comparable_type<this_strategy>::type comparable_type;

public:
    static inline comparable_type apply(this_strategy const& strategy)
    {
        return comparable_type(strategy.radius());
    }
};


template <typename CalculationType, typename Strategy, typename Box1, typename Box2>
struct result_from_distance
    <
        cross_track_box_box<CalculationType, Strategy>, Box1, Box2
    >
{
private:
    typedef cross_track_box_box<CalculationType, Strategy> this_strategy;

    typedef typename this_strategy::template return_type
        <
            Box1, Box2
        >::type return_type;

public:
    template <typename T>
    static inline return_type apply(this_strategy const& strategy,
                                    T const& distance)
    {
        Strategy s(strategy.radius());

        return result_from_distance
            <
                Strategy,
                typename point_type<Box1>::type,
                typename point_type<Box2>::type
            >::apply(s, distance);
    }
};


// define cross_track_box_box<default_point_segment_strategy> as
// default box-box strategy for the spherical equatorial coordinate system
template <typename Box1, typename Box2, typename Strategy>
struct default_strategy
    <
        box_tag, box_tag, Box1, Box2,
        spherical_equatorial_tag, spherical_equatorial_tag,
        Strategy
    >
{
    typedef cross_track_box_box
        <
            void,
            std::conditional_t
                <
                    std::is_void<Strategy>::value,
                    typename default_strategy
                        <
                            point_tag, point_tag,
                            typename point_type<Box1>::type, typename point_type<Box2>::type,
                            spherical_equatorial_tag, spherical_equatorial_tag
                        >::type,
                    Strategy
                >
        > type;
};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_BOX_BOX_HPP

/* distance_cross_track_box_box.hpp
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
*/