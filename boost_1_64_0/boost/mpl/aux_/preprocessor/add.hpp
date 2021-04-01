
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
Ti8k9KdQ7kJ93vgEWOelpzKyP0Ax2pPOH7Ac8Jn4D8XWpWqbjhxWU2cSAZ8oxLd7QLMwnxPDOyBk4WtKnqNsCAU6ZxdXmA4utUvgO7Rtuo3Lie+JDuhqCDf1MKFv8x7gUYy+S9xZ5o4uTXsgNNlZY+kW8prOHnWPIRucAaW0r3u3uTDxrjJxNN+8LDtS/qi/p/0YumUl1/5ir0dtzFWWetf42J0LdFDPH1TcSD1FT+zD4nV/K4yktCtlMj0FCmsXq0/wItlezJRv2MjLVBr/GxS2CM3/gxsskgBfUtbcFA/8xsxMkUbZ8WcZURUPpEuxPy74Hhml322AglOVYCKDg7Hj+UpcofVu9Z6mZKlIDA387Qi1/jPLVYKytqK57pJMoQpD+4BU1ViAh+86daDvktVbEt9hlJCfE8s3siuexmwAFLJDuTIFU2Q48QqUnddwXYHEBEMdB7BPZfGCNxiCjxtr/tah2GaHg10mj+BP+scDIG7YhtFH7yxxkb26fEC4+Vh4sc+eJvPNSB0RWzHNp2D1ZKC099TTOdyjlwxivdmC3aiqDZJxTZoWXQ==
*/