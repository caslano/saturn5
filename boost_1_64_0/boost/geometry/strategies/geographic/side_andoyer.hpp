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
BRfglaDBOgmN0/W14LKulWLkDpPeuB/ZhIRZwIN5OGEXkTWlHdZs7HzZFKzgJNWczY4OOXq2sxPdPXEy3JEfu9hrK0tTGsml1OhMh/Xj95Zy5qiJf2/hg7VI/bJWRClU6O416jJJ2bIdu7o5Wdm9oN5TgecfDTgDxZAgXbTqc+9EgqGGxoVaK6MpyGGbsuAuGuopkWE0uGRmVNbpDhwwXFXDhsk1MK0Ic/sS3HQHgyUqqbaa/LgdKyRC9sseMEFMZPcJQTfKDF5ncKwLvXqUx/BVRR9L0noXB7B3Mrqj2qqhM5JD0epCS7b8iCY9FwdaNPxFKCxRNipJQvqEb5piH8akkfjGlfhlYtEg1XMZ1CI1btOymAo6P2YIcj/L4L70eAM3kOrIw+mGvYHkSLXPTNtw00xtI6KKNAJLm4TNaNRMh6Ne+RexR1ItcpGnEQZAOVfGMUdetzLaecTYL2Mt+1dTN68vuEmY47Z46s7AHcyDyGg1zFHnhCmpOZlgf7voUmbVzYjfINq5uc9SZW4PtpgqxB4lM8fe8KIOsrswnuGUbZ3k7TzWPUwOxw==
*/