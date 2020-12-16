// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POINT_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{

template
<
    typename Point1, typename Point2,
    typename CSTag = typename cs_tag<Point1>::type
>
struct point_in_point
    : strategy::within::cartesian_point_point
{};

template <typename Point1, typename Point2>
struct point_in_point<Point1, Point2, spherical_equatorial_tag>
    : strategy::within::spherical_point_point
{};

template <typename Point1, typename Point2>
struct point_in_point<Point1, Point2, spherical_polar_tag>
    : strategy::within::spherical_point_point
{};

template <typename Point1, typename Point2>
struct point_in_point<Point1, Point2, geographic_tag>
    : strategy::within::spherical_point_point
{};


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POINT_HPP

/* point_in_point.hpp
ZV+E5E1NbwnJbV/SHnb4K+bu65Acoj7h5eBJ0lvgx7+hjsb/bUh2+C4k8zR+eNKqkDyiYwJvt5o/0KduFJ79Q0i6qv0jY/4TY4cd/pl6Xp6s0RgCefLbLfLkG+y6/Dy5YKs8CWmZrfPkg3Z50vZI/Zw9T0Zvmye9sfmjBTkW9BhKeXgVWKrl2+MHDCQ9Dj8A2g6l7/Au2+VJV+wieDkYii0d8mQOOHkoMcNbdMyTlfiJwGPAGu07/CJ4E7sFvrMTMQylrc55cjwIaVvww6CjtgXvun2edNO24AXg/SNJh08soI/qE34eLNO+dKG/4JChrB/Y24H4NQb4KFB+FGMLXwiqjtL9ln6BGuxG+FMwHFt2zJNfgZOPwj/8OJiG3QwP3YkY1D88cmf86LjB3SJ5MlttePgueTJPbXgVWKR93DVPGnbLk1nYkW55cuBv8mSGjtW/2jv3uDavMo4/tE1Ia9WoU/E2M50atdaUtZNdnFCgho5CBrSyqQuBBJI2JGkS2lDrFrvq4pwaa52odQYIECBAprPDOTXOOnHOGeecOKeyOifqnLibWOvld97zvOENtH78+IeXj3n7Of0+5znnPdfnPOe8J9WB979OR0mhN6Nfb0R7IFs26Oizb0a9Is8mHV1UjvJF+8H3Idx6OcoHb0FIQs6CP0I4BnkOLLkAdUE2gpcgpCHbwF6Eo+Jd8BaEO8S74K8RTkCmzZhfhHrIFvBKhBbIAfB6BK94F7wF4V3iXfC3CIch0xYdvREhDLkSdCAcFO+Cn0JwQs6Aey5BfjGel+po31vRZsgJ8Ny3oV/obxS8q1pHBpGnRkeNtbAZYRtge4OOKkV+m462XwEbE/nB85p0ZITeBs7sxJiKOdqlo+e6YSfiXS/0ftg25ERAR3v36siM/Bnw1v06skCu7NXRqw/qKCfqBddfC/sWdYED1+loXuQ/jHG+HmMu9DEdvfkjOpoW8kd19KWP6WhOlHNER1s/qaMyyPE+9Hsc4yzmN4P3Pq8jk2jnF3T0klt1VCFk8PbjOrI1YH5vw9h+SUdWyLbbMX53Ye2Icr6towe/i75Dv3CvjppzKB9yBhz7vo5ahR587v1Yy5AT4JEfYUxEObNoM4IbMv1YRz6EAOQ4+AhCm9A/iLlFiAg9eNtPdRSHHP2Zjp5AyEA2/hxzixAVecBn5tB3Uf7DWHcndRSDPAe++xfwBeJd8CWP6CgBuRLci5ASevB1v8R8NOJd8I8I85Cjj+roOwgpyHPgpl+hDZDj4B8RKiEb5+GXEDKQA+BtCAHIOfC8X6NtkCvBWYRpyPQbtAVhFnIWLP0t+gvZBO5FsInywbrHkE+0AbwLwS3aAL7xdxgTUSZ4BCEGOQOWPY4xF3rwwwhWUT647ffor2gbeBuCWbQNvHsB8y7a/wcdveIJvA+5DbwFwSjygK97Euv0CpQJPolQ04R2PqWj655GG6C3PAN7WcTahD4L/ghhUYw5WPInjCFkI3gJgkGMLfgeBBJ9BL+EsIA8OfAPCBbo6ZSOXo9QIfoC7kHIiTkC+xGykDPgjxFmIC+Az/szxhOyCaxDmIPcBr7pRXpqsaE9L9fTxAY9vQtywqKnl2zSk7sJ5YM3leup9QqUA27ZrKeYDW0DP7lFTw9BPweee5Ge2kQecO2leroUchxcf5menkL+AJgVssgPfvBtegpAnwU7KvUUh5wDD+zQ02PIk7Hp6aXv1tNpMbZtelrjgGyDDL6pHXHoA+BzO1COaCdY7dRTBHIcfMylp83IY+vU06Eu6EX5YJ0H7YCcAR/q1tMG0Wafnu7xo62QjQHkRViDchKgbi/0kE1gD8K06Du4Oqinc4QeHA/p6eWQjWE=
*/