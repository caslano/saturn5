// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2016 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_DETAIL_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_DETAIL_HPP


#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{


/*!
\brief Point-point distance approximation taking flattening into account
\ingroup distance
\tparam Spheroid The reference spheroid model
\tparam CalculationType \tparam_calculation
\author After Andoyer, 19xx, republished 1950, republished by Meeus, 1999
\note Although not so well-known, the approximation is very good: in all cases the results
are about the same as Vincenty. In my (Barend's) testcases the results didn't differ more than 6 m
\see http://nacc.upc.es/tierra/node16.html
\see http://sci.tech-archive.net/Archive/sci.geo.satellite-nav/2004-12/2724.html
\see http://home.att.net/~srschmitt/great_circle_route.html (implementation)
\see http://www.codeguru.com/Cpp/Cpp/algorithms/article.php/c5115 (implementation)
\see http://futureboy.homeip.net/frinksamp/navigation.frink (implementation)
\see http://www.voidware.com/earthdist.htm (implementation)
\see http://www.dtic.mil/docs/citations/AD0627893
\see http://www.dtic.mil/docs/citations/AD703541
*/
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class andoyer
    : public strategy::distance::geographic
        <
            strategy::andoyer, Spheroid, CalculationType
        >
{
    typedef strategy::distance::geographic
        <
            strategy::andoyer, Spheroid, CalculationType
        > base_type;

public :
    inline andoyer()
        : base_type()
    {}

    explicit inline andoyer(Spheroid const& spheroid)
        : base_type(spheroid)
    {}
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Spheroid, typename CalculationType>
struct tag<andoyer<Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct return_type<andoyer<Spheroid, CalculationType>, P1, P2>
    : andoyer<Spheroid, CalculationType>::template calculation_type<P1, P2>
{};


template <typename Spheroid, typename CalculationType>
struct comparable_type<andoyer<Spheroid, CalculationType> >
{
    typedef andoyer<Spheroid, CalculationType> type;
};


template <typename Spheroid, typename CalculationType>
struct get_comparable<andoyer<Spheroid, CalculationType> >
{
    static inline andoyer<Spheroid, CalculationType> apply(andoyer<Spheroid, CalculationType> const& input)
    {
        return input;
    }
};

template <typename Spheroid, typename CalculationType, typename P1, typename P2>
struct result_from_distance<andoyer<Spheroid, CalculationType>, P1, P2>
{
    template <typename T>
    static inline typename return_type<andoyer<Spheroid, CalculationType>, P1, P2>::type
        apply(andoyer<Spheroid, CalculationType> const& , T const& value)
    {
        return value;
    }
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_DETAIL_HPP

/* distance_andoyer.hpp
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
*/