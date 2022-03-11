// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_BOX_BOX_HPP

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
#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_box_box.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{


/*!
\brief Strategy functor for distance point to box calculation
\ingroup strategies
\details Class which calculates the distance of a point to a box, for
points and boxes on a sphere or globe
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
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_cross_track_box_box
{
public:

    // point-point strategy getters
    struct distance_pp_strategy
    {
        typedef geographic<FormulaPolicy, Spheroid, CalculationType> type;
    };

    // point-segment strategy getters
    struct distance_ps_strategy
    {
        typedef geographic_cross_track
                <
                    FormulaPolicy,
                    Spheroid,
                    CalculationType
                > type;
    };

    template <typename Box1, typename Box2>
    struct return_type : services::return_type
            <
                typename distance_ps_strategy::type,
                typename point_type<Box1>::type,
                typename point_type<Box2>::type
            >
    {};

    //constructor

    explicit geographic_cross_track_box_box(Spheroid const& spheroid = Spheroid())
             : m_spheroid(spheroid)
    {}

    template <typename Box1, typename Box2>
    inline typename return_type<Box1, Box2>::type
    apply(Box1 const& box1, Box2 const& box2) const
    {
/*
#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointSegmentDistanceStrategy
                    <
                        Strategy,
                        typename point_type<Box1>::type,
                        typename point_type<Box2>::type
                    >)
            );
#endif
*/
        typedef typename return_type<Box1, Box2>::type return_type;
        return details::cross_track_box_box_generic
                                       <return_type>::apply(box1, box2,
                                                            typename distance_pp_strategy::type(m_spheroid),
                                                            typename distance_ps_strategy::type(m_spheroid));
    }
private :
    Spheroid m_spheroid;
};



#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Strategy, typename Spheroid, typename CalculationType>
struct tag<geographic_cross_track_box_box<Strategy, Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_box_box type;
};


template <typename Strategy, typename Spheroid, typename CalculationType, typename Box1, typename Box2>
struct return_type<geographic_cross_track_box_box<Strategy, Spheroid, CalculationType>, Box1, Box2>
    : geographic_cross_track_box_box
        <
            Strategy, Spheroid, CalculationType
        >::template return_type<Box1, Box2>
{};

template <typename Strategy, typename Spheroid, typename Box1, typename Box2>
struct return_type<geographic_cross_track_box_box<Strategy, Spheroid>, Box1, Box2>
    : geographic_cross_track_box_box
        <
            Strategy, Spheroid
        >::template return_type<Box1, Box2>
{};

template <typename Strategy, typename Box1, typename Box2>
struct return_type<geographic_cross_track_box_box<Strategy>, Box1, Box2>
    : geographic_cross_track_box_box
        <
            Strategy
        >::template return_type<Box1, Box2>
{};

template <typename Strategy, typename Spheroid, typename CalculationType>
struct comparable_type<geographic_cross_track_box_box<Strategy, Spheroid, CalculationType> >
{
    typedef geographic_cross_track_box_box
        <
            typename comparable_type<Strategy>::type, Spheroid, CalculationType
        > type;
};


template <typename Strategy, typename Spheroid, typename CalculationType>
struct get_comparable<geographic_cross_track_box_box<Strategy, Spheroid, CalculationType> >
{
public:
    static inline geographic_cross_track_box_box<Strategy, Spheroid, CalculationType>
    apply(geographic_cross_track_box_box<Strategy, Spheroid, CalculationType> const& str)
    {
        return str;
    }
};


template <typename Strategy, typename Spheroid, typename CalculationType, typename Box1, typename Box2>
struct result_from_distance
    <
        geographic_cross_track_box_box<Strategy, Spheroid, CalculationType>, Box1, Box2
    >
{
private:
    typedef geographic_cross_track_box_box<Strategy, Spheroid, CalculationType> this_strategy;

    typedef typename this_strategy::template return_type
        <
            Box1, Box2
        >::type return_type;

public:
    template <typename T>
    static inline return_type apply(this_strategy const& strategy,
                                    T const& distance)
    {
        result_from_distance
            <
                Strategy,
                typename point_type<Box1>::type,
                typename point_type<Box2>::type
            >::apply(strategy, distance);
    }
};

template <typename Box1, typename Box2>
struct default_strategy
    <
        box_tag, box_tag, Box1, Box2,
        geographic_tag, geographic_tag
    >
{
    typedef geographic_cross_track_box_box<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_BOX_BOX_HPP

/* distance_cross_track_box_box.hpp
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
*/