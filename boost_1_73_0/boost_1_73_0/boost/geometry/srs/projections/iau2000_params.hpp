// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct iau2000
{
    explicit iau2000(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_iau2000
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP

/* iau2000_params.hpp
DLGYW1ewsAXuZXYJOvahckbL6AfHsbKyRY6k4BpTgmbIPo0/JaWI7LjFcSdxpBUZxVluVXAbkCJbW5peZ8GqESfXqhrXCZMKKIlrgq0SEpZJjcwmHeHaMJ0omVfW6xQ2Gh1h49s+7fJVeVrHlihz7yO+7Zjy4CUlHXtG5FfAGjvgg8DvolVjyg20Ts7Qw1r4k4j1IAjGbgD8UOGvhxl+1/EPc77L6AupZZLgtogPBxVeM7kfkOu4oxHhyb/F0/X8tia42u49yMbHq7yOs4MKLyFbr/Cb7OTANUwn48U7UdaXYM1QOrGvT4+7Nnr3JbkJ2X6nue8jWZqiRAymQqmrXUfl1Ilg8LabXHwx7miP9bVrVe2Arqb0W/d2Q3sbhL1Yz/b2tQM/ZqwX/wFQSwMECgAAAAgALWdKUiHd8dqTRgAA0F0BABgACQBjdXJsLW1hc3Rlci9saWIvc2V0b3B0LmNVVAUAAbZIJGDtfXl/28iR6P/+FLCzP5v0yJLsOZLIY+dRJCTxmSIZkrLGm8wPC5KgiBUIMACoY3dmP/urqj7QABogeMgzeRvvZiSRfVRVV3dXVddx9Hp//54Zr421/yz6nwX/4Cf16IfBfzqTWN/asn4x2P9Br7/Dz3WTHBlJl1+surG+yy9GjbpY
*/