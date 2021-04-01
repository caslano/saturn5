// Boost.Geometry

// Copyright (c) 2015-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP
#define BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP


namespace boost { namespace geometry { namespace formula
{

template <typename T>
struct result_inverse
{
    result_inverse()
        : distance(0)
        , azimuth(0)
        , reverse_azimuth(0)
        , reduced_length(0)
        , geodesic_scale(1)
    {}

    T distance;
    T azimuth;
    T reverse_azimuth;
    T reduced_length;
    T geodesic_scale;
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_RESULT_INVERSE_HPP

/* result_inverse.hpp
ecNU2bqCzM7ThhoBzfnyM3956bjetWyL3dyObA1YOKBFpd00XcMJzg3mOBfUt2HJ6O/6M7g6fEC7WViJL4Oi6ydy0TpJFvek76a3Fuo6uFw+tZyRnaELTXHnpcTFurtwGMjXN5y35uN4GwLWGr/R5XCP2xCpJvsWaUADUgdmCioaPXd9gZynwDQueNnrWdIzjwsWIDYIbr/lp5OdnitGyg6S1tJx7bQDRQbounT334kSp2IqKYFtAF+4Uxm3kovyqwDYaMlugbi108AY8WWhfAVeXjjL0yooy0D94iUJbPYbrXbRVfGU2hJ+QHNLwvwfG2rrtiFow8nZdbpLAf+Yoj2DeUBoJWl6je96CymlW1zE8nlYcLtcrep+wLS79iD4Cii5coC9qSCQVXiixkV8AlWeddSszqj1Tf3e9SawCWqq609dyRabzc/SFs0ogAv3HUjb5H88UfS7oKbyQ3I9ohcXwwQlWTlQyADDRHsIMq1/JtJXLEff9fWe6dR1KAf8EnSPw5kDr/98Ne8a/zhuLZqckdpc3mA4DNfXMY5bOws8Cb1AtYqfmisNZA==
*/