// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP


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
class vincenty
    : public side::geographic<strategy::vincenty, Spheroid, CalculationType>
{
    typedef side::geographic<strategy::vincenty, Spheroid, CalculationType> base_t;

public:
    vincenty()
    {}

    explicit vincenty(Spheroid const& model)
        : base_t(model)
    {}
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_VINCENTY_HPP

/* side_vincenty.hpp
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
*/