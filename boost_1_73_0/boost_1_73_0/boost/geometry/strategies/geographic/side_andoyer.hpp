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
kzkMejCTuC2tLtRE6vNNAuiz1dAQZSYZDMnOjkZcbQthmBuqAjSUWbf0KtOuSKNe4Qh0OLzrSWfFdPhMjg4FmkgWCg+zy1noteG9h6wMQDHYuWgky0W6s4FXLbSC64pSm+EdaYpJhcdVmbEp0wjDlh/Z/Fpw8WBaFKvOF6ZbyNw/uLqfZZnKfCdTLTHOGHFa3uZ+mlqOXyboJgHPugQvHQlXnCCRWK3OK9KFzr41I5EXJViQvtqslpTDi5dr2+or8oPYnntzra8+rnNQXcRmMKO+mu2h+XHVCxlLma/c/C+8kJFYkxkg0cjwBV/lsUAZU7T+qUEP+51G/QS/VPaqD0l4ZVWomyjUm2PMtz1iTYCvbseANMlxcdRjskdQkwh8Y2vvkY6xWyiWjFc+uD13xy8us2XX+6pVBEqo230TFKzPny5ZSuLq84H1aypqglNGZOPVVcfQq8xLm6ZF1dDZQx1RQZYzUP0KS2WW/KXescxOdbhieK2eW5b18IyvTV/8WZJzj3AqUFM0BZbX3lDUy13yZO6JUzC6VljwopTZTaVoi12kDQsTbslWO4yGwZTa1uw6vhvfCL4LUo0zFLmMJ7krtnSQXHIk2NKUkhB2SiVEl9bYVxbgDSNosug4J1bBJ8E16PMRqcx87gVM
*/