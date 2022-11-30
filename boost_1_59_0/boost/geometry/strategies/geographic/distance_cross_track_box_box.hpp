// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_BOX_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_BOX_BOX_HPP

#include <boost/config.hpp>
#include <boost/concept_check.hpp>

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

    Spheroid model() const
    {
        return m_spheroid;
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