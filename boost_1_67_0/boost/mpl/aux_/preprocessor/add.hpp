
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
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
*/