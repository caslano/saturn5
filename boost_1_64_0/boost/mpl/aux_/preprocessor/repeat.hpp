
#ifndef BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
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

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_REPEAT(n,f,param) \
    BOOST_PP_CAT(BOOST_MPL_PP_REPEAT_,n)(f,param) \
    /**/
    
#   define BOOST_MPL_PP_REPEAT_0(f,p)
#   define BOOST_MPL_PP_REPEAT_1(f,p) f(0,0,p)
#   define BOOST_MPL_PP_REPEAT_2(f,p) f(0,0,p) f(0,1,p)
#   define BOOST_MPL_PP_REPEAT_3(f,p) f(0,0,p) f(0,1,p) f(0,2,p)
#   define BOOST_MPL_PP_REPEAT_4(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p)
#   define BOOST_MPL_PP_REPEAT_5(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p)
#   define BOOST_MPL_PP_REPEAT_6(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p)
#   define BOOST_MPL_PP_REPEAT_7(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p)
#   define BOOST_MPL_PP_REPEAT_8(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p)
#   define BOOST_MPL_PP_REPEAT_9(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p) f(0,8,p)
#   define BOOST_MPL_PP_REPEAT_10(f,p) f(0,0,p) f(0,1,p) f(0,2,p) f(0,3,p) f(0,4,p) f(0,5,p) f(0,6,p) f(0,7,p) f(0,8,p) f(0,9,p)

#else 

#   include <boost/preprocessor/repeat.hpp>

#   define BOOST_MPL_PP_REPEAT(n,f,param) \
    BOOST_PP_REPEAT(n,f,param) \
    /**/

#endif 

#define BOOST_MPL_PP_REPEAT_IDENTITY_FUNC(unused1, unused2, x) x

#endif // BOOST_MPL_AUX_PREPROCESSOR_REPEAT_HPP_INCLUDED

/* repeat.hpp
qkYuy+ubUW0RuD1xsnRFJzPBF5scGenzjsvp96a/N1k5qOayDJNHORwvXCm4yMHZ6iXKY7j48BC9pmPkNOZtKO53Es5389IRxV47gUvVotYfp/sag0vt4wgXM/v+V5I48aSEBATfSoMypVQO2Z18ZCM9/u3AWWrlf/65EJT+Z3b+xpdIsb8jmL+zPCHyNuPCG6sEg3J2DQ/vmcBRtFel/bD2Jb7xyX6XcktxTKL+l0Vta/isUHAA7aT4pO0NZ6ONaXF4uos7QecY+D1x9uM8Vzm7uugRGMjMojVMbQkeEOEiPXoJA3T1PLPRpnR0DkaE37G65ViPNtLCS7/A7xXmCzkB4uxjWTzwaiXPTe3yMoF+AQOw3QjH/vfNtEt/xQ2oUAw1vg98wIm5pDMajnDPag69u3FMAAHWU0QhsEX0xY6R9ICR2jvE1VbsBZArrtlbtGkfESqbgT3YkBKe1AQdvyfANBbSteeUOAMWUUPyn4FgRPsA81jVG9aWmkNHyjELcFHFeprgx93J8bXps/uZNNEtNef+wsitvgv74xIrjxJyhnk/wj6wWDed7g==
*/