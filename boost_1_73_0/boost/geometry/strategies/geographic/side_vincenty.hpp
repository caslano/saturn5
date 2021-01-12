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
zZUhyXdY0rKN38ubk3OyXuZvJRhrh3QMuzaukzMDz7FLW71ugGKoa3uZN+JfU+r1QKnXvuQ9fNhIB3L2efXhkj9fHndr2xHcbKrw3v/a5a1JWc9QD1yGZQ7IIVw/7Tg+v5YsrIeOhf5L7iqjUt+dtdOKw3Ekjj913oxL+q9H6Wd3f0ZvOMkZvSnljN4SDU2UysOz45BHBWd3HHE8nO+zY6hg1joqNrAiaLeDvx7ItG01ztq7
*/