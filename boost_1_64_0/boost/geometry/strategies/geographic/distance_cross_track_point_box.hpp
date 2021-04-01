// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_POINT_BOX_HPP

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
12yTNt/LCmYfx26ezAr79Hqe1405JK8n5PBIJLdDOAnQt1u9mTmDAsk+3mAL8JljtBtwyIx843amTwGoRIBdRsx7PsDi5Q08xGz0lxQzZq2CjHYxRwwI1zzRWH3QcGwFGPuPQE+oN9Te/FNrd+/DgKQdyjC3kvGWekK/AM1K33oYwPfULvuPlLrV6TOmKlEDlsL5cORItElbFHZQzYhG7HWq2x0pt3wp433odTrMLkqkjR3Kbs3nfUIabVrfsZzvMDXAqmI+26Sbm/WSdpO1+QFcsSBNLPLzh68rJKxnpNi+6ZAI0h/XcR3VW6mfXNRG0ioXeAceEawp+tXJilMzk05xziD9bMismME2fhFIN2QGA1C1XacdFAyXkL3ZI8M0l1EPv1vGYzo4M/8Bp9wTvIeIbn3QNM6U0HGYv1XODqVR+DheRVNtcJ0v34fZR+2P0QsBo9kRbjRi3oijpSfaECA4dM2d8+mWDmSmTilvTzNzZXBqlI7exmwtnD/aVnFpQglU1iTUeOIZ2NZFmYJe0aHXcyMXRILv18Ty6mA+OXT8N968bnCqyBLPJQ==
*/