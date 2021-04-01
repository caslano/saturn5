// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2017 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace azimuth { namespace services
{

/*!
\brief Traits class binding a default azimuth strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};

}}} // namespace strategy::azimuth::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

/* azimuth.hpp
d9PoNB2T+oghbCfwrSTqbkIzrbvwgf+227u2B82yQwXhgLvSWWUSocXvDqULosqq/ufSMq1rPjtfk6KRKD3c1dZGIvrplhwSPwy1hNqLHCIQmELVDjV7ooV2tbOkGRGTUUzhCt3rVnaMyfShl6AaEd3b11CV5mffkTerhBqnLRnLjSYPYb4MzSShQ1ttKtOsvVQt410J0HdvKsFgpW0VtooBVwc9luBY90Ii3YhzGuimntGO60IciRyeRyzQ5C6HHkAkMI2pvaiYirsYeSSZORSyI//Ru2hBxdaMXSSCEVZ4+PacNKV7iAkabCrc5vE3KDgVLXadzwPyCAOA0ZkcO6a/asSQXcXik754TRxFkLgWYdyJ+Z5UsY1ckJ5NVQpaHP/ccLj8CFaf3iyP3t498NOTUfjo+iq04/m9BE/e/Yn4UgnJ7+OzedoHDc2pwi+ljaoPWZYZfNfJ3nAVbrPlGCTQpQqsAQ25pvaqZk0/dC3hTggMkY5Zi2n1REeFfLAtuQEUrdO+X5iwCwQMEwEYYaLIazgEwKCjn1BXcOsNC+frhKRlzYySgJqF+Q==
*/