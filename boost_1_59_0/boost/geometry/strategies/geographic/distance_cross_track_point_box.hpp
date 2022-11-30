// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

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
#include <boost/geometry/strategies/geographic/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>

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
class geographic_cross_track_point_box
{
public:
    // point-point strategy getters
    struct distance_ps_strategy
    {
        typedef geographic_cross_track<FormulaPolicy, Spheroid, CalculationType> type;
    };

    template <typename Point, typename Box>
    struct return_type
        : services::return_type<typename distance_ps_strategy::type,
                                Point, typename point_type<Box>::type>
    {};

    //constructor

    explicit geographic_cross_track_point_box(Spheroid const& spheroid = Spheroid())
             : m_spheroid(spheroid)
    {}

    template <typename Point, typename Box>
    inline typename return_type<Point, Box>::type
    apply(Point const& point, Box const& box) const
    {
/*
#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointSegmentDistanceStrategy
                    <
                        Strategy, Point, typename point_type<Box>::type
                    >)
            );
#endif
*/

        typedef typename return_type<Point, Box>::type return_type;

        return details::cross_track_point_box_generic
                        <return_type>::apply(point, box,
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
struct tag<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_box type;
};


template <typename Strategy, typename Spheroid, typename CalculationType, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy, Spheroid, CalculationType
        >::template return_type<P, Box>
{};

template <typename Strategy, typename Spheroid, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy, Spheroid>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy, Spheroid
        >::template return_type<P, Box>
{};

template <typename Strategy, typename P, typename Box>
struct return_type<geographic_cross_track_point_box<Strategy>, P, Box>
    : geographic_cross_track_point_box
        <
            Strategy
        >::template return_type<P, Box>
{};

template <typename Strategy, typename Spheroid, typename CalculationType>
struct comparable_type<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
    typedef geographic_cross_track_point_box
        <
            Strategy, Spheroid, CalculationType
        > type;
};


template <typename Strategy, typename Spheroid, typename CalculationType>
struct get_comparable<geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> >
{
public:
    static inline geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>
    apply(geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> const& str)
    {
        return str;
    }
};


template <typename Strategy, typename Spheroid, typename CalculationType, typename P, typename Box>
struct result_from_distance
    <
        geographic_cross_track_point_box<Strategy, Spheroid, CalculationType>, P, Box
    >
{
private:
    typedef geographic_cross_track_point_box<Strategy, Spheroid, CalculationType> this_strategy;

    typedef typename this_strategy::template return_type
        <
            P, Box
        >::type return_type;

public:
    template <typename T>
    static inline return_type apply(this_strategy const& strategy,
                                    T const& distance)
    {
        result_from_distance
            <
                Strategy, P, typename point_type<Box>::type
            >::apply(strategy, distance);
    }
};

template <typename Point, typename Box>
struct default_strategy
    <
        point_tag, box_tag, Point, Box,
        geographic_tag, geographic_tag
    >
{
    typedef geographic_cross_track_point_box<> type;
};

template <typename Box, typename Point>
struct default_strategy
    <
        box_tag, point_tag, Box, Point,
        geographic_tag, geographic_tag
    >
{
    typedef typename default_strategy
        <
            point_tag, box_tag, Point, Box,
            geographic_tag, geographic_tag
        >::type type;
};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

/* distance_cross_track_point_box.hpp
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
*/