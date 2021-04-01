
#ifndef BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED

// Copyright Paul Mensonides 2003
// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/preprocessor/is_seq.hpp>

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/cat.hpp>

// compares tokens 'a' and 'b' for equality:
//
//   #define BOOST_MPL_PP_TOKEN_EQUAL_apple(x) x
//   #define BOOST_MPL_PP_TOKEN_EQUAL_orange(x) x
//
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(apple, abc) ) )
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(abc, apple) ) )
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(apple, orange) ) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_TOKEN_EQUAL(apple, apple) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_TOKEN_EQUAL(orange, orange) )

#define BOOST_MPL_PP_TOKEN_EQUAL(a, b) \
    BOOST_PP_IIF( \
        BOOST_PP_BITAND( \
              BOOST_MPL_PP_IS_SEQ( BOOST_PP_CAT(BOOST_MPL_PP_TOKEN_EQUAL_, a)((unused)) ) \
            , BOOST_MPL_PP_IS_SEQ( BOOST_PP_CAT(BOOST_MPL_PP_TOKEN_EQUAL_, b)((unused)) ) \
            ) \
        , BOOST_MPL_PP_TOKEN_EQUAL_I \
        , 0 BOOST_PP_TUPLE_EAT(2) \
        )(a, b) \
/**/

#define BOOST_MPL_PP_TOKEN_EQUAL_I(a, b) \
    BOOST_PP_COMPL(BOOST_MPL_PP_IS_SEQ( \
        BOOST_MPL_PP_TOKEN_EQUAL_ ## a( \
            BOOST_MPL_PP_TOKEN_EQUAL_ ## b \
            )((unused)) \
        )) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED

/* token_equal.hpp
O1bFZRvITFwBQ2KYq4q5z1+uSBYrQ0hyxypGBDMmntDflCNB0xroV0h3vjXe4qSZNvUSq1Ja8952vEAIV6/QdQSoXMW2JrnS788iqRf/e5WyG3i0AuZ+Gasee9Z3Lz7v9REjX6yWkpA+J9AtkISHBMvhZ87Zt0dfBGuP03m0agSq2yjuivEblWktRNGC9XO6LV8clE6Ms20Q92SkcEwj0LbI36SPjcteYMBg6A9QYfUHl0kbbjErNgiM9DoLgrX+ABhmaDHCSycdVvknZlHIJJHzZP6xj80imnu7IWW0MDNf9VezDw0LBD21THbLP9txHNOqPw3kzM2P4Mb0DXpB8eoP7cSykF1hrUYpc4h1L+m8jqXY8xj8MhHK4zUDemxaVCLFqYeuFNrAiBFcR+NsQPOIsr2DH/12BMieEvLqoQvr+KGma/3exY9MA7RTGE93Qe8E6HbdwyRv6P0afI5Y3P4uQJUkDlkmUoCOG2e9xMrWb2DpTn74pwOvMr+Z9TkgbsLtJNC0jIYbdhmoovzgFp58gSVgx4ysRWF5UUKzkrKU3mAFVEYc5TJcsA==
*/