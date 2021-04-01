
#ifndef BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/preprocessor.hpp>

// BOOST_MPL_PP_ENUM(0,int): <nothing>
// BOOST_MPL_PP_ENUM(1,int): int
// BOOST_MPL_PP_ENUM(2,int): int, int
// BOOST_MPL_PP_ENUM(n,int): int, int, .., int

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_ENUM(n, param) \
    BOOST_PP_CAT(BOOST_MPL_PP_ENUM_,n)(param) \
    /**/
    
#   define BOOST_MPL_PP_ENUM_0(p)
#   define BOOST_MPL_PP_ENUM_1(p) p
#   define BOOST_MPL_PP_ENUM_2(p) p,p
#   define BOOST_MPL_PP_ENUM_3(p) p,p,p
#   define BOOST_MPL_PP_ENUM_4(p) p,p,p,p
#   define BOOST_MPL_PP_ENUM_5(p) p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_6(p) p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_7(p) p,p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_8(p) p,p,p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_9(p) p,p,p,p,p,p,p,p,p

#else

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>

#   define BOOST_MPL_PP_AUX_ENUM_FUNC(unused, i, param) \
    BOOST_PP_COMMA_IF(i) param \
    /**/

#   define BOOST_MPL_PP_ENUM(n, param) \
    BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_PP_AUX_ENUM_FUNC \
        , param \
        ) \
    /**/

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

/* enum.hpp
Lv+eLQaFqblRbGmz0+mWnrA9h84h3AAowYTXMXSQ4d0af4KtyNdpOOJ0i9w+bo+GTfFBQ9NFNnROvLLMGy+fkdurYyIMKpzlpHK3/6glwtAhyuz3uG32iZ521F+//icQAzQ2Dhy3qEHGEUUvFJD9BE2xET4LAF9aTksJ8b+3pvoqFhxn1l4r2MAG1GoC7qN19fuzvqS/zvgFyYg3oLu8AT5rK1dCsE/q1D8di+ye1Ng8s0dp3XSRTLQTfs02XrqQ/4edxvYfqCckvioaXeVJVAwKOxKOtz/HzYOzoegOnI5d6y7I6XQiyQwPBf0OVX5nOMsB/sdsWSXuRT9OaV7CUKgEFd26BQvBDorGY6rd28ruoFFU92XyVEfYHZcFT5PPfi4PKyBz8a1ExoO+Xmew9lvKYtUouri9+y1wo2HL9fM34TURaRn4cGsmP0toNTqj0GG8g9X0oG7rScduBmRzwVjMc+bEGeSAmnkveuJH7wIcXzGCyT3CLfRu0Y9175v56189KBIt3dUl4Ut7MZ/aSxcaHXI3RtLSEbAemKp6zTXY8w1YExo4kecqSg==
*/