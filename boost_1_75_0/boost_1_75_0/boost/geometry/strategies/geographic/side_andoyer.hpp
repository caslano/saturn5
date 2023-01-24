// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP


#include <boost/geometry/strategies/geographic/side.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

/*!
\brief Check at which side of a segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam Spheroid Reference model of coordinate system.
\tparam CalculationType \tparam_calculation
 */
template
<
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class andoyer
    : public side::geographic<strategy::andoyer, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::andoyer, Spheroid, CalculationType> base_t;

public:
    andoyer()
    {}

    explicit andoyer(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_ANDOYER_HPP

/* side_andoyer.hpp
Yt7FTp30lE4vyQQy2kGsxyi8i4pI0ZVFmjUl1Zffwu8zo1tLCTeVNRI6CUZ2i40lu606STezlpckWAihKTSkJYbm2PjXjuKq1/BBqsCR9Wh65MGRAm5mnQR1sfiQtn/RES/2ck6BrOkGOm6y8io72l24sNWqrD28k9mi3EOnZ9XwjmUB6LaX752IYZIrZsRmWElXdiGs32ajx7ycPVFfN26aDGf/NJ6D2eXw3Xg9S2aSy8A1ccSSr6QdLmGukoEK/8jfeN8zkdDOhg9gfJ0KfRRO2UY6OZeBfeHkvxJH+Zr649QovtSL0FsF3rC+pvUuQVeEe0y4R2ftGMlTWwBPdhSbtTyKH8Di3avEPDqi1Cib5Aqd01VMoyHagPGtc/Nbc9vlU0VkRSSa/VvL70EdW3Szxv5a81F7lo1AJVpu02T9a6Jv59CVkQ8cfx6QfqcI26+OUeXJ1BTxkPKQHLAHF81ILkRYI052GXdg0jgHwv0a0OlGV4q8f7av0rLACt7njMYUICnd3azf9b/C9MCweplX2OqpVnnM3F9iIM5IPfuTEAtbOp8IVzDcgFr+YPoHy2juL9O+SEnnc/VCpfSEZvNqHDM7DT2mPnVbsm36Hi3oHLafiie1bZx9gktFUUlOaE2s/s+s/ves/u+M9SvpFVxYXb+wuuax+w15l3xJlsE/qnW0nU79a1U6vOi2P3wUExhmwabVxMvVal/H
*/