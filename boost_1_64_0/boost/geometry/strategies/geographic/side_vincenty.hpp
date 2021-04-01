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
ZymAYx35sMlEecycJoQmQ4reQd69lw21KTaBviIg+B6q4nLSQNKSDT+xO/Q9PY9mQY6liNJguSIIImuGedJWAnE7eJkDwl6WLUDNDBIH0cJvzVIQr0Vm38Srj/XmBYX3U+rB+htPajcPPszflvuXpjf9MyPGXdoNbCLNp/bRrwX1iOscLoR6V/wwsR+bBr49+IAqPY/1MzouvFWY5M8FS4Wq7zfLW1MqWeKsdIda9W276rJ81wdmu4nKed1ZT7mcHpDFG4PQXw+G8KcSZYs+CupgNE9c5rB/d00IRpCIcVWuP100/tTfIuiYTOrln+H6zqcLcjGgwEZYXZ+JHMW+PgVv78JLayazlDySnfZXvAp6YZNimkY5Gjr3oqn/sDlCnPGbcsplQH/WM37UrpZOj8+g7aYRNDjkVbRWpfyUc6kY81gmT0MT23JgsM2ePP2FJkg0HIryo8YfFKEHPQAVik0GQc7dKxiAsBchYpwgQZph4zhNF0qxXqN1DQ4G1ADKG/UxEXKuojuZ7bLIMwcB5tiXJIdyvxSjXGk6yYOAdiumJO3WgRbjygDJlg==
*/