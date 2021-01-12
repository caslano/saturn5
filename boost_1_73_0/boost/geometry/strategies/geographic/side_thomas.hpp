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
wSsDfdNm8hXF7dmh7WFdIdOgD6U9/yE5GL1JUf5yvntamSeon+SxtzW2W0Ab1AcD72er8Z16ZlvkOdOUc6/WpAz73vgO3+/ua2W84xPj97e6evoxc2MkPg3pPfi8yA5ZBtjRyv48ZZzoG1B+v7I0ygpfulrJ56tPp+OrxtsS/N8t6XOt4buUsNx4zOBfa396kaTtYV5RWn6L2Ce0/Z5W9Z51UfN6sWOlu9nNgf4pb3jCY7/B
*/