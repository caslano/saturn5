// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

#include <cmath>

namespace boost { namespace geometry { namespace projections
{

// Functions to resolve ambiguity when compiling with coordinates of different types
/*
template <typename T>
inline T atan2(T const& a, T const& b)
{
    using std::atan2;
    return atan2(a, b);
}
*/

template <typename T>
inline int int_floor(T const& f)
{
    using std::floor;
    return int(floor(f));
}

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

/* function_overloads.hpp
Pe3utigGbc586BFJDfrDx9RIHxGL1r4f6T61B0zX+A1X5tdAOQmjqTGvg0YNO7TVugkOykHz1R9LObWAz0yyadBdMhlLlVFWH35R9DpOh42UWJC01UBKNWf3dF195ASNLMUPKZPJqchTRk7LHnfIgEQbMZWLRGdtCq0EV6+OCVpnJ6uNuGM3i3kIsXyW+uNwbOLRe3E5pdmPQwcs8OEgjNADAnGl0sOGWeUg6dw+Oa+Ul7ScQuKD1xONXBXeT2w8p6dFCjydgUYyMxslozwf9yPv/raqL0sIkFzHNlQmJYQbiIG4ol2TPx4VfhnO+vh0KW46AEBDDLlOXrJi++oNUAWVT0yOHlE8N0WHEFV4W2VGWxuy5pTrXEwlskqgV9wdaBFS/+UOZPyXTGZvRhfTZSIxavEgY7nlvIZWupYV5RspqlxceGik+g5Dsvy0GJ7cPf/zZszZ2FGQuWFXSgXH5OlCig1Gk+WyvGO5kNTogKJ0LdVD2OSmwnxBtVySzYpN9rzM3rbxLMky1Xh1R56Wfeu5amkT/rI2GYvrI7RRH7bXWHUob31wuYyYQ2iCrZb8Tkwa1iirFDn3EhjvgBbzGNBE0gaNKt7SfgR1jvtTPox/hcUadMkve0/wglT3x5UPVyTL5IZkimPptImh31TrcGe5V6L4QZqY5z0CxIJAmIkmtCVYPUCEUbI3XJ605ohWNvlekPoRXVsd49Ah
*/