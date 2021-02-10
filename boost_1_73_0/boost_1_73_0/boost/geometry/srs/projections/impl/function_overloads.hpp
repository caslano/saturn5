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
f5CpHK+NGOPGbcrs8IITn6PygjIoqpGB4jWegguDMJ5PggVeP7gebzicb1AUekNca0+Y5ycKWfRCJ8aR3ItmDRSl0A+MpRwfOzggh0A0PGDCnIPmcyYuBon8mKRrdVJhVOL7No+JD90bF9MKdIG7J/ZSshrGah1g5uTUlC8ILv6HGIokZz9AH3I3pESglBrz0BicNd+9Pf6zTLrOZOAIdy0jAsqbvnRWeHVpP6CG9Eq8bOJxi2P8+YfvRWQ/GyI98FImqLCnUwmVbbxquYBSOH0lZmOZgjA7Iia94ObXKWvEXmdmFHSeLENqN9kGBzBLy2sQI1a+eMuQoQWStimSwprBlp9ShOUjhq5I1/kEdCF7owGxSNpN7a+9PYGxDZPkSqvqZivasXtF7GzVJ5pd6TgZ942sCde8F41O50U6ORbLO6oe6fJiZWcxpg3HB8DbWpKV0Or0mp+sVmPU4GioH6NrwBCNWd3zjikvSPXwozmVW5UfUu/z8678dTPnUmSVoY/Hkxb/zOb7WjTAab86Ec46V8OLDBVm3iqaq5c6np8HBpMaJ6Rszni628kt7pc0gag7xyzigKpqUzXABiYmVMhAFjoUoi9AIz2XDvc0BJyq2JayxBMQkpgyaCsFipgF78r0IsjrF/OEzMSp
*/