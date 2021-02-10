
#ifndef BOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED

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

#   include <boost/mpl/aux_/preprocessor/tuple.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION)
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_ADD(i,j) \
    BOOST_MPL_PP_ADD_DELAY(i,j) \
    /**/

#   define BOOST_MPL_PP_ADD_DELAY(i,j) \
    BOOST_PP_CAT(BOOST_MPL_PP_TUPLE_11_ELEM_##i,BOOST_MPL_PP_ADD_##j) \
    /**/
#else
#   define BOOST_MPL_PP_ADD(i,j) \
    BOOST_MPL_PP_ADD_DELAY(i,j) \
    /**/

#   define BOOST_MPL_PP_ADD_DELAY(i,j) \
    BOOST_MPL_PP_TUPLE_11_ELEM_##i BOOST_MPL_PP_ADD_##j \
    /**/
#endif

#   define BOOST_MPL_PP_ADD_0 (0,1,2,3,4,5,6,7,8,9,10)
#   define BOOST_MPL_PP_ADD_1 (1,2,3,4,5,6,7,8,9,10,0)
#   define BOOST_MPL_PP_ADD_2 (2,3,4,5,6,7,8,9,10,0,0)
#   define BOOST_MPL_PP_ADD_3 (3,4,5,6,7,8,9,10,0,0,0)
#   define BOOST_MPL_PP_ADD_4 (4,5,6,7,8,9,10,0,0,0,0)
#   define BOOST_MPL_PP_ADD_5 (5,6,7,8,9,10,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_6 (6,7,8,9,10,0,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_7 (7,8,9,10,0,0,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_8 (8,9,10,0,0,0,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_9 (9,10,0,0,0,0,0,0,0,0,0)
#   define BOOST_MPL_PP_ADD_10 (10,0,0,0,0,0,0,0,0,0,0)

#else

#   include <boost/preprocessor/arithmetic/add.hpp>

#   define BOOST_MPL_PP_ADD(i,j) \
    BOOST_PP_ADD(i,j) \
    /**/
    
#endif 

#endif // BOOST_MPL_AUX_PREPROCESSOR_ADD_HPP_INCLUDED

/* add.hpp
c3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NTRVVAUAAbZIJGDNVm1v0zoU/m4p/+GoE4I7EZzubhPLTStdwbQhGJsuEUJCIDnJSWMtsSPbWRd+Pcdxt07jDhB8oarsunnOcx6ftzZzaF0pLC5ZJlWtabvEca1NZZfsNM8vpgUuzt/l4dPZq7PjcMz4FpnxYMx22A68Q3OFJrayQpYZ7NuRAJVwIjDy+bM57CUJnL+O2EvhMIV8wKeQHMFbfUVP5gnM99P9o5QwJ2d5xAJhCl5rbKcDr8Ulgl3bstUWI/ZCK4Wlk1qlsP3KoXJxPvboba8db1zXRixiDbatJtFB1KStbLC8/MME/lFiQrQ2Ycr4Jq+U7het9IYh3eV0IEBwvGSNcz3Bb4474LRuQVpYN8LRAQaLIJV1KCrQNTwuB9M+ZpmHLVkri8ODfbIPRwaZEh2GNEE19K0sKSSAwo7QCFW1CGvpGuhkh+D1kgUPJpCVuusIEzSlnD86pTJ+dZE+8mwX5//lPPi6xWW1JEJvvpi1esX9kSDP3LWbLVne0C3o7d1AbXQHtBGCGPzmg3QTjakt3qOR9RjgonZowDU4ZYmkWygQFcxso92MZVcT1ofRGdn3whCJ5Z/jB18fRfwliY8+7fKHMf7FiabQg6qEGRc/
*/