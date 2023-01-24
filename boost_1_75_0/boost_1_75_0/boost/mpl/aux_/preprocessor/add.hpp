
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
YxFPBSNTK4G4RzxWac9kII/i4pGdxgPGbuLbK4HJFxGTh+daeUxKDmR9Gv5Bq8053QcEkqqLU8ktcUp1HqjFI2ItemXJGuzPKcSF9cCohHzBuxQ7RVvkq4ZW2XOUWgsiDYisEHeiNLScJcwcQJc1pbHv9pv1OfWC4+dIdQyRUTjjgxkVC7D8wWStsuXO9RmSknsw/gXhTP8A+ROL2RngzhA5/lz2kAjLhs1kP9e9vr1yi+YqPRp1/vhAl+/woHzK5KiaxuhXw/ZtG+8U8oniCRCZWvl8eg38G1io7W5mwXzz32g967+/zPIP/8y/Gl2zhlw2n7CjCSVURhqqWgM1BT8a0MsFpcpm+CZ6c2uwK0Uza6tZEWIkdX/ylgoa6HtbDUahqlS1jtXcq9dqtcBbp6iEqYzb5QjmqGR5r8fzXjS5mNlllihSRtJ/+EmYGJY8WmGZD3nxevXn86/JMPcdtTNrpNg6bOMMdrZxBrxHXtClKSC3cpqXWJhoisR9E1kL5AwcVUJylV6/27kL1WH94aT2whpQMTv0CsPXT/+Yh+7jkg9K3hsNdGZMdkx2FHYMdjTxDxeNc6N2q4E/AtvmsC//9KT4kapN07ec6Y75p0B1wfN4LlTw0nWEuPNFYmYjMc6odROxVwbHGu85qZQ1khTQDBJNohGF9W3tUAtfHnMEuhac5X5HCGox5oi4ba+glml+UL/lov6jEmK1
*/