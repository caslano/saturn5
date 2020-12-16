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
M3AlcAbnV43gdSPg33F+B6i+6L/XBcIHPi4QrpxjAA8B/qW0Z+BfAc+SbRvwJ4B/zfXtN9J+gU8CPwD8JvAPgP8gVLy8zkLrPbHxPg8+WW5fBb4S+AWu398AniH7F+CVwIdksy7bSeDPA38HGLzi+8Dv6HOMpvdkf8LxThS8ViFtgueCHmqveE7G/eTPgB3APwdO5HzozPlwmcwHDm+HTAuH9xqnI5X6U/03BPmcJuPUdL3HaHo7NE7T82c88GPAk4Fflu0i8Luy3dX09nEGMN1xBh4JPAv4FuDZwKXAc4CXA88F/iTwTcDPAt8M/ALwLcBfB55nljfPU8kWYvK9K/g6AXcHvha4J7CcZ1+h6fadC/wk8JXA3wfux3bbH/gscB6wDHwgsMzbQWa8PPeivI2Jt0jT+5sFMn2y3QWulnLAdwAvAb4XuJb1KNf09voO4EeBGzS9fV4u083+zS6Z8Rh3AIYDygBbAIcAZwF9RyPfAM2A3aPhDzg+GjRAcAzogImAYsAKwPYx4AGcBrjGIm8AwwHzAI2AFsABwFHAKcBZQNo4tEmAiYAawEbAdsBBwEnAO+PAcz14AMMB8wBNgC2AvYBjgHOA5PGIDzAKUAioAWwF7AAcBpwBpE9AGIB5gCZAM6AFsBdwFPAOIDgRZQSYBagErABsAewDnACISYgHMA4waxLogI2A7YADkxAO4CwgbTJ0BkwEzAU0AbYB9gOOAU4BxBToDegLGAcoB2wE7AYcBBwFnAWkT4VOgImAYkAToAWwF3AIcBqQPA1pA8wFlAMaARsBuwEHAEcBZwHB6ShvQB5gFqAMsGE6+KYjrOkICyAKoDtgFKCsQG/wmwE7APsBxwBnAZmF4AEUA2oAGwG7AQcBZwCuGeAB9AUMB8wD1APWALYCdgD2Aw4BTgNcM5FvgJ6AwYCpgDJAE2ALYB/gyEyEPVMf6GQDxgHKARsBOwCHAacAybOQRkAhoBhQD1gD2AbYPwvhAE4AfDcirYDhgEJAPWALYB/gIOAI4BQgOBvxAYYCigErANtngw9wCHAMcAbgmwP9AaMAcwErABsBLYB9gIOAkwDfXPABxgHKAVsAuwEvAU4AzgCSb0KcgMGAQsAKwFbAbsBhwBlA+s3QCTAXUAloAmwD7AYcAJwEnAOk34JwAOMAswBlgI2AHYD9gEOA44BzgLR54AWMAxQDVgC2AfYBDgJOzNMHkj0BEwE1gO2Aw4B3AJm3ouwATYAWwEuA44CzgMwi5A2gHLAFcAhwApBcDP9icel36Xfpd+l36fd//Pu3nv8fWFSPkC7K+f/nQ4L2Jk457NaW7dai27+2HH+N2m6Pw26N3W4Nv/17De1d646/d2O3Bm63F2O312O3B2G3R2O3F2O3B2G3B2S3N2G3B2S3J2K3B2S3V2W312O3J2K3p9P+vYYWZ6tzRZ5Pxp8fHoqaF5pzQjUfbN9c8GLOAy/mHPCjzP/iz/3s53zJ8eZ6PMfLa8O8rr1zOTmPc/2b5nIXcx4XPYfj+Zs5d7OZt/W8SPO1iLnaxzxH4/nZpd+l36Xfpd+l36Xfpd+l3//czwVY8O+b/9OTxLQAIMQFrwHsCwnjnPgO3kPvpk5sA0owT867h85vFo4eO+X6WXQVaCCdv/xEGt1pWFRvni9m3m5Eb/BIOj1FS/QpFnpITKNvIw2H31Py/HJInlx20hnjDKbNA20XaAHh8QS93qAzKIje1jPmUr8CDfqxnxSCTvCTOvFdRE77MUfsGflFkC+OSfv8ZfXhOrv0M38m0fskx6bfSu8hQLecvy406ZQ/u+Ge5+D8STHzR9EaQduj8sfjueC8gb6cN+RH55ihI/xIx4j82sY=
*/