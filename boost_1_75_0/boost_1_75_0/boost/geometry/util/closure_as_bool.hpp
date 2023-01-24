// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP
#define BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

#include <boost/geometry/core/closure.hpp>


namespace boost { namespace geometry
{


template<closure_selector Closure>
struct closure_as_bool
{};


template<>
struct closure_as_bool<closed>
{
    static const bool value = true;
};


template<>
struct closure_as_bool<open>
{
    static const bool value = false;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

/* closure_as_bool.hpp
Lp0Z20EukdX4cbsxM6Lp2fX2XlyLqK+480ozSqqpfpH0RyoCGPp+JBYKXI+Ls08Qixm1oZ+U+XllWMlFhvHNDEdBN1E3ckciEmUmQkt/KyXXKgDXzibNVEX4kdtx37zzisxN4Gb3Tc5NcfBrvD8d4pv+2qq088M71yB/u5TwMtSiOsmPUL1XK5vfwr7FRNMvD/FijdnGfsE1Ljnw7ErqZmT+9JpYYV7WH/OZ65G1+xXQ/6t/REvrvOHshCWczFH+efkG7ZH0kdo3ApGKwHHQgUA5SDeuyT1+FWgV2xqWakFYdhwzemSRokhp5DekPHIv0tkwSEHHOIXkZhNdGFfseAQikn9CelHAtD5lwMUwJaO05Ax0ronnAma1v/wotJrb+q5inGCwcaPfFdZs3BCvZpQN5om1YZq4bNgmVwHDw4PhDYSASUBGA2D581g9lxeYND3vcNKxEU+B94fZ6fPp874rcVSeXdqjHnnnvl3N58CT60wBUiDBFb2NgMpo0H7JnxTLeZ+ktdepKKtSbKYJr2aIVbodNc1eHPHvEuOCj50afOeAVnYM/e37eHffAq9xjjRHKabXtM1qmeTEtp6Ttx5j38kfqaR/w3F8owMyJhcVHLbsW+TbBgKcFZcK4kvcrfXc5yuqgl1ZL460U52jQJNzcm/MsJ2YtzxhjY5jXPbZJWGkRjKjWQNVBwPjWCs8nhaHZIKtYE9NUSxd
*/