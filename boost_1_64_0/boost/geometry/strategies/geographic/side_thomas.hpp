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
O1GzU8RYKoc+D6BkWH7pz75UyhEddYIiKk9h0ng5fmvReG/VusWHkCn0lojAso03KL8biuH8nkfVXyC5WBY4Z509Xl3+jtKWBs81c19LYGVoW4UOxvhZkqVX8RqVOxb3kfJ+eJPIQpVw2A5nxPJe2UbzO6rxCgARv+WA42AybqxM3AHqI9OS1h39cAMBnPkDYg0MCEQJnFG1ZLzfQG3EVcWRKl8Z6n/zXMDax06dw7RxQpARfmP8dx+HDoh+kGZi+RLk2URvN8D2sWwk4WeelQu4veN2ZqCovoGoDri9tNwH7xBcd9muaR5mKhN4Yg3qaTJ6E1HqefiowFKUY6fBwtXBpShJljBOOHoQTg2pVZRk2os+B9/i3ag60gDAQfKP/tSqtaBnew6BT/0kzI68LK/QW4T0PLDgEmH2y4F4BWf/3+bP85QtsCDg/uPwtnJOpXUzi+rjD6tzyWFWxpB2S9aszL9dto98pOfjDVOt1mPh408sAQj9Hnu0FzV+jE2B919VEQy2YYMHbcG9ZhBBza+BWbl2kPcVA93nupJbXXiILFuaXS7zJDpItQ==
*/