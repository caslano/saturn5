// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP


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
class thomas
    : public side::geographic<strategy::thomas, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::thomas, Spheroid, CalculationType> base_t;

public:
    thomas()
    {}

    explicit thomas(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_THOMAS_HPP

/* side_thomas.hpp
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
*/