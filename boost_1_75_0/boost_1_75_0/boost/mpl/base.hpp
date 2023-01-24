
#ifndef BOOST_MPL_BASE_HPP_INCLUDED
#define BOOST_MPL_BASE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct base
{
    typedef typename T::base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,base,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, base)

}}

#endif // BOOST_MPL_BASE_HPP_INCLUDED

/* base.hpp
oShtti5RksUtt2tGjN2RatKNQGvqtOpHOYXB3MD7rqX1vYctjCfJPzqoHO3UN12ZO11Umk9SomrFMorBMhRwtaTvPJpPUZM0T+3ET0x3wuhgDJT49kVx3fP7IYWngre7bnAQxWPmppHNk+9OoQ3BeZdc6IoXfPcxhOOcoDM1SC/MN4wz1Sa68UAchVNKfR/4ByX58zE+z6hHN8SpdJWiBoCO3HcNLqJ+41Xouds1c1jyE7XxD6a2Lz7vfSL6bz+6WP6Tu4v70z9ySWsXB1c9G2crNxebf1N1gDP1kD/K1n8olbbY2oD4uBGQlsT2821isrQBJ5x2nPkVc2Ty+5U6yUo/Vs+B9rXjdVpmRW8v5wp+9EB1a30FxzsAh3kjuuVb7wxMyczXzD/eSmbmg3lVoPzF5byeb/kbnXh9LO8Rmdmt0Iu7jyM3ia/Pn3dmt6a77QVMBtZ7PTSH1MPmxP0O17lYFKLLvq+P6Wj4a1D92iymxIi6Q5pypI4J7Isp05V+wcntdvVVEgZoeGbqobGg64Q6dr/ttux+0a3ZbfKiS7Ayrfik7+o4u21Yyke+6K90JhdKjjV8WxXWESP9y1U5YIUBrClE60szORQoCnJbAJNuWNGud2k2+JdlJr38PG+8LNcz4O9u3c5ORFGaWQ/ZUB0tFLXjEKF75qwjDeJ7vHj3s2ntCbTVOmac9epXb0t/YPZ4ylNfqHdySchO
*/