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
R4dmxDBiGrGWOEZcJ2rUYh4illhJHCS+Idy5eBhIpBBriSPEJaIiA3V3IkKJOcQ2IptwqEP6xDBiPrGNyCRuEx6cAAOIaGIRsZe4SJThx3orIogwEmlEBpFNlOEHfDsimJhGZBC5hEN91oUYRqQQ6cQ+IpdwaEAeiAAimphGlHxKPkX9/LXj/yUkht2j9/8vyfP+v05SxccRbsRY4qua/F+8pe+OjHGRnGgICUqImUz3mAGGqUXoX6TzTLzSL2awk2X8Oxak6u/kIW3u1YQH8RTxNXlJLSgvIb5DB7Yv/JlnGSPN+pwnL6OyTIvWeW7fqPT/jDB/h+mo9IO3+15/H2Q+5XlYz4LWVcbQW8WKueMy/JZ19TEWtK6RbMPC19X03Ovbk+S517gIWXfttojGsub8sVwpD6OqjPKPyRej9L/plH/9VWUyvtD1z5b1/1rq3WXiumn9EzTrP2Sob56qV4Tx3eQ5X836BuM10iDPiWH621En3+q+brtlHL/lhDuxmLjBMo2JuvlWV9NijOWXv05G56uTxruok7YyUK/b3rL6dbJdku66qatlEdbNVC93Jf8z6mWeMlCP7VZO20+1D//RbrKmDEwDRsVExoRTCHdWJy39BPhbxmjMtw0ng2qfqSHj380jahOziB9ZD6cpBeXNXPPuKH/WfSZJqWfSP0RVF/XrnadtvVRjd2TIOrSW8m1GTK1GO7ngdQiPZoxVcz0rwrPtOmM+yHZX1StV2W4rr1v3+eFVYL5MCypSvZ869b9b7/W2ifIOYBlj75ys+xn82bTuj2rWne6KjOBiGn3rDo/DtSx1SuqPanEsT+nbovq3EKpeVFI0/846KX1O6PKkyo56ew6T8ehM1zZbYjya6lnotALWKc/5dZNDwf2J0tHan8iQqt62B3W27bF829ZVNSYy/YxoBNKxRdpIqm2Zf3xXNrpSjsyvX45B9svRPO98B0s/CMqR0bKCGOggJsU6b7Qyb1zyxBAlb4lMsm4D8qTKt3XRSj8k8iX9vWx11lhO0pP1NyrTohkumMap9A3bMN1cnvT3UPcNuy7bdDzhRhiIm6bj3yxlm6rbS8Woo/nHTghWtQF0z6+qfSi7orbteou8rVXydu/brUqe/4Z2qzIeZyXtcfI26xk627qed95m/XyO9hiprOPfcIwsbN3nV9a2Wf8wrfsT1nW/u/aqsq73oL1qPQ6GVsnfXuVj6k8515rnu2+rKvn+G9qqyno56dfDoHnW9bq7dupH8/8ZddG2/upj4U0nbTs1kP8IWmBd/ztvoyrrWYw2qnUf2Stj882X+jab8KlO+3mhNV931z7V5E1V1+RYWYS6pm4L2X4DBbpo26ePm/p1Kvm/N21TZT1026bqMvWvql/XPZ605unO26XPLPrv1vN820L9rgdZ78GECxFI1K/Gei8259n0amM2csf26veY2+9r66GsB3PKNODebr5xJiX9itRbPjwrQbpS/qVMx05L+qp2Y1yEraFUlPeq15L82GsHNytCOzg5XxvMsiWYX8q0uZPq32VEH/7d+u6NcvptOFMf8GOUfXnW/0FW9HPWF/KUl3q7lzctS12GqnKc5ip9eUpRfzEcy1COa5fmL0eGiQw3DUhA//FI2ximKYWUY2oB5Tjffjma856maqtb1t2J9U4hz43JZ44lj0ynzPKWuZS2tNdt6y/LOMIykljGcf4emmYrv1AsW0uWkcj+oGqrx5jXx1/ZP6LDJhtkoKREW5vAz7yuEw2sgrWsVWO/nJDx8jYSHsQ6oiXzZCzPX96JCZNNoyiy+KK8Z0J/bAj9MjEq9Y8u6VJ+KUqdY1qe8Y9SMckyblOsTGO7qcdyolwof/s=
*/