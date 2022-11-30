// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_AZIMUTH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_AZIMUTH_HPP


#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/azimuth/cartesian.hpp>
#include <boost/geometry/strategies/azimuth/geographic.hpp>
#include <boost/geometry/strategies/azimuth/spherical.hpp>

#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{
       
} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type
>
struct azimuth : not_implemented<Tag1, Tag2>
{};

template <typename Point1, typename Point2>
struct azimuth<Point1, Point2, point_tag, point_tag>
{
    template <typename Strategy>
    static auto apply(Point1 const& p1, Point2 const& p2, Strategy const& strategy)
    {
        typedef typename decltype(strategy.azimuth())::template result_type
            <
                typename coordinate_type<Point1>::type,
                typename coordinate_type<Point2>::type
            >::type calc_t;

        calc_t result = 0;
        calc_t const x1 = geometry::get_as_radian<0>(p1);
        calc_t const y1 = geometry::get_as_radian<1>(p1);
        calc_t const x2 = geometry::get_as_radian<0>(p2);
        calc_t const y2 = geometry::get_as_radian<1>(p2);

        strategy.azimuth().apply(x1, y1, x2, y2, result);

        // NOTE: It is not clear which units we should use for the result.
        //   For now radians are always returned but a user could expect
        //   e.g. something like this:
        /*
        bool const both_degree = std::is_same
                <
                    typename detail::cs_angular_units<Point1>::type,
                    geometry::degree
                >::value
            && std::is_same
                <
                    typename detail::cs_angular_units<Point2>::type,
                    geometry::degree
                >::value;
        if (both_degree)
        {
            result *= math::r2d<calc_t>();
        }
        */

        return result;
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct azimuth
{
    template <typename P1, typename P2>
    static auto apply(P1 const& p1, P2 const& p2, Strategy const& strategy)
    {
        return dispatch::azimuth<P1, P2>::apply(p1, p2, strategy);
    }
};

template <typename Strategy>
struct azimuth<Strategy, false>
{
    template <typename P1, typename P2>
    static auto apply(P1 const& p1, P2 const& p2, Strategy const& strategy)
    {
        using strategies::azimuth::services::strategy_converter;
        return dispatch::azimuth
            <
                P1, P2
            >::apply(p1, p2, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct azimuth<default_strategy, false>
{
    template <typename P1, typename P2>
    static auto apply(P1 const& p1, P2 const& p2, default_strategy)
    {
        typedef typename strategies::azimuth::services::default_strategy
            <
                P1, P2
            >::type strategy_type;

        return dispatch::azimuth<P1, P2>::apply(p1, p2, strategy_type());
    }
};


} // namespace resolve_strategy


namespace resolve_variant
{
} // namespace resolve_variant


/*!
\brief Calculate azimuth of a segment defined by a pair of points.
\ingroup azimuth
\tparam Point1 Type of the first point of a segment.
\tparam Point2 Type of the second point of a segment.
\param point1 First point of a segment.
\param point2 Second point of a segment.
\return Azimuth in radians.

\qbk{[include reference/algorithms/azimuth.qbk]}

\qbk{
[heading Example]
[azimuth]
[azimuth_output]
}
*/
template <typename Point1, typename Point2>
inline auto azimuth(Point1 const& point1, Point2 const& point2)
{
    concepts::check<Point1 const>();
    concepts::check<Point2 const>();
    
    return resolve_strategy::azimuth
            <
                default_strategy
            >::apply(point1, point2, default_strategy());
}


/*!
\brief Calculate azimuth of a segment defined by a pair of points.
\ingroup azimuth
\tparam Point1 Type of the first point of a segment.
\tparam Point2 Type of the second point of a segment.
\tparam Strategy Type of an umbrella strategy defining azimuth strategy.
\param point1 First point of a segment.
\param point2 Second point of a segment.
\param strategy Umbrella strategy defining azimuth strategy.
\return Azimuth in radians.

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/azimuth.qbk]}

\qbk{
[heading Example]
[azimuth_strategy]
[azimuth_strategy_output]
}
*/
template <typename Point1, typename Point2, typename Strategy>
inline auto azimuth(Point1 const& point1, Point2 const& point2, Strategy const& strategy)
{
    concepts::check<Point1 const>();
    concepts::check<Point2 const>();

    return resolve_strategy::azimuth<Strategy>::apply(point1, point2, strategy);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_AZIMUTH_HPP

/* azimuth.hpp
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
*/