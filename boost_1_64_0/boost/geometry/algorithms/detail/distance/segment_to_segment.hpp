// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_SEGMENT_HPP

#include <algorithm>
#include <iterator>

#include <boost/core/addressof.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{



// compute segment-segment distance
template<typename Segment1, typename Segment2, typename Strategy>
class segment_to_segment
{
private:
    typedef typename strategy::distance::services::comparable_type
        <
            Strategy
        >::type comparable_strategy;

    typedef typename strategy::distance::services::return_type
        <
            comparable_strategy,
            typename point_type<Segment1>::type,
            typename point_type<Segment2>::type
        >::type comparable_return_type;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Segment1>::type,
            typename point_type<Segment2>::type
        >::type return_type;

    static inline return_type
    apply(Segment1 const& segment1, Segment2 const& segment2,
          Strategy const& strategy)
    {
        if (geometry::intersects(segment1, segment2, strategy.get_relate_segment_segment_strategy()))
        {
            return 0;
        }

        typename point_type<Segment1>::type p[2];
        detail::assign_point_from_index<0>(segment1, p[0]);
        detail::assign_point_from_index<1>(segment1, p[1]);

        typename point_type<Segment2>::type q[2];
        detail::assign_point_from_index<0>(segment2, q[0]);
        detail::assign_point_from_index<1>(segment2, q[1]);

        comparable_strategy cstrategy =
            strategy::distance::services::get_comparable
                <
                    Strategy
                >::apply(strategy);

        comparable_return_type d[4];
        d[0] = cstrategy.apply(q[0], p[0], p[1]);
        d[1] = cstrategy.apply(q[1], p[0], p[1]);
        d[2] = cstrategy.apply(p[0], q[0], q[1]);
        d[3] = cstrategy.apply(p[1], q[0], q[1]);

        std::size_t imin = std::distance(boost::addressof(d[0]),
                                         std::min_element(d, d + 4));

        if (BOOST_GEOMETRY_CONDITION(is_comparable<Strategy>::value))
        {
            return d[imin];
        }

        switch (imin)
        {
        case 0:
            return strategy.apply(q[0], p[0], p[1]);
        case 1:
            return strategy.apply(q[1], p[0], p[1]);
        case 2:
            return strategy.apply(p[0], q[0], q[1]);
        default:
            return strategy.apply(p[1], q[0], q[1]);
        }
    }
};




}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{



// segment-segment
template <typename Segment1, typename Segment2, typename Strategy>
struct distance
    <
        Segment1, Segment2, Strategy, segment_tag, segment_tag,
        strategy_tag_distance_point_segment, false
    >
    : detail::distance::segment_to_segment<Segment1, Segment2, Strategy>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_SEGMENT_HPP

/* segment_to_segment.hpp
oPkr/nQfYs0XiSduRe9rkc3dT+CLerABUepBpcT123NPFTmOJTZ88jr227bsJ+T/3jR8XDF14InYEmKBaVdSl8QXXncrcSd1twZikCFH4TffQm+wQwMfxXdTG/oXtu3jSmg4JwkPYR8uwvYtQQbHEv+chO0jvz2XusER5K/xv8CzX+CLP8NeDqMdNuzVR9G3ndhD92JLmdPft2CendT1PsefcX4SfpY9i72bOY6+T2UeD9B/hrV/Tpz8EmcmA6gzowc/eQL9n8067yNnw9+8lqK2zVx+h/2J/YYa1yDizXOQF/5l0msh6k/E+ZwdfDOBusEG4hriqvfSzO92xqUuP2APfCVx8QfkotcSO7Ths7Yj1r0J+TzzMjDy0d92M/cQdXDi3S3eQN4J7C5jb8GZ6cvYybvZW2c8Qq3rbPwR7U6/Ff/8CPu4jJj3M3i7Hfkq+/RzapunfkXsMgUdYC8cfwpxPHw6e2fyYfzuAQfhj/Hp4+hj+DHYReL98/DnS5DpffD1N4/Cj4PwH0dhd4dSq8WP7tFOrEg8cRE29TjisI34v9VHsR/o65t3sA3obu/+1KXYD+/eiQ0knjjyOfbgB9RK98a/cB4xax42itrHqEng0bezZlDvAhf+HnaXuvm7xB8J0r1zpmBn/k6bu6lFfob+70h8Po8aNjZsH+Z1ArXzuQcTN+6OnjPm/BrqXyup9S7jfIPc7bKV1Fu2EjqJ3Ylj5/clR65mzshh4rPs2S/RmV2Ej6QOiu37YDRnEPvif4iD3iDPLyKufOss7Bc1wCPAN1M/rW/AlhIbNbZjT2uY7w+oTxAfbElctjN+ZynxdSVxzU9+BK+/x/wOp87AvjjnOmR3D/YcG7E3evM5cdsDP8RPMeaJL7Ce19iP+NE/YltevBwdeJV6P3w+g3n37CDnufRt6nM3cIZ/M/YAm/ghfd+IHWgGv/SKEDked51q8SHg/3IIsf9p6BX2dvxd2OKXOJ8hNn1muxDxMnblM/zNIdgW/Nkw4CcPxVYezd/E8OIsL4pN3EAsPpq9VoHdX8wePPKX5KsTqcEUEb+uZM74oBnkKvdt5PwBHq97Exv3FDn3aHJB8oh1zOmLHuxjmnWjG0Ws5Z8heHoSY1yAXfgZuofvPy5BLgB/zqwnZn4W30+u/NSb7EnihkHYyAPR31NKsenskzE/o/bxb/Yh9fDSPchTlyGrM/Ctv6U++H1kxYXj9oHoEjTLiRP2oz41HZ3cifuVPO9LzIE/3EDMcD39I8+lb9En4762Bj1DJo/C/8Q49vdC6iW340fRnxOfwT59jrwZb9YfiKnL2b9fkBvTfuXByPs0bPBQ/NcdxO3w//40/h//cMez7An86PHzsVNnUb/ZSC3yTPLsh+E3dr/mSvTkVmqzO/B/fNE1e2Mvy6hPr+ce+9/xidvCozh+Mow9/iu1X2TyHPHIuJ1lPXT2MmRA3Hgde+gx7OL6fajTHIfeIKt9TiRGGY5dwAf9mjjjtpPph/h6PLw8ZA2+/hv2HX39Zhi1D2Qa6sVehDhvPh+ar6hVEueeOwB7jz16+RLucywhBpqG/3sMv7cNPMU3PkOccMp5xLgL2HeMu4B/r8MPPDyKPUX/U9hDvycXuuRtbOE0crQf4V+uAr8lNUj82c3zGBCbcwz6+vFfqBPNG4ANQRfqsd/w7bEQth29WH8ieR4x9HXEWM9SC31zM+YFrzuvRQ+xQzsdAm/4+45h9PUFfh2e1qyH9xXYX2z3E/iA24vwT/B79BDqydjA61uQwWpyoKOpV2BPDzkXv3E4+478+lJofw8fbliLzb2ItWTxtefSL+fAbxNnPH4jdgRZ/ZT98zq6tG5rdBJ+9yI=
*/