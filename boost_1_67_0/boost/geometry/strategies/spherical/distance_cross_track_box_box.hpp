// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_BOX_BOX_HPP

#include <boost/config.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>

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

    typedef typename boost::mpl::if_
        <
            boost::is_same
                <
                    pp_comparable_strategy,
                    Strategy
                >,
            typename strategy::distance::services::comparable_type
                <
                    typename distance_ps_strategy::type
                >::type,
            typename distance_ps_strategy::type
        >::type ps_strategy_type;

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
            typename boost::mpl::if_
                <
                    boost::is_void<Strategy>,
                    typename default_strategy
                        <
                            point_tag, point_tag,
                            typename point_type<Box1>::type, typename point_type<Box2>::type,
                            spherical_equatorial_tag, spherical_equatorial_tag
                        >::type,
                    Strategy
                >::type
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