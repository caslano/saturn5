
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

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

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_SET_C_TAIL(set, i_, T, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c)< \
          T BOOST_PP_ENUM_TRAILING_PARAMS(i_, C) \
        > \
    /**/

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c)
    : s_item<
          integral_c<T,BOOST_PP_CAT(C,BOOST_PP_DEC(i_))>
        , AUX778076_SET_C_TAIL(set,BOOST_PP_DEC(i_), T, C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c) type;
};

#   undef AUX778076_SET_C_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
thiQ45oCclxJ4FeUrsDLCsjrZpG2d3ZmYPRES8+P8T9QSwMECgAAAAgALWdKUitlqnXVAQAACgMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NjdVVAUAAbZIJGCdUlFv2jAQfreU/3Bq1SeEUspYN+RGjYCuaCSkELqxN9e5QCCJI9spDb9+ToJg2+Necrnz5++7+3xUo9KcKXQITfJYmLDH6iBkpBwSzIM+WbrLWfMBdxU+w2jhel1vPCCLp1Hvvv+pjne9r00+uDU5tS8E1G45yTW5hiXKd5RdlURIqMQirQxANUWeRQ75h34SzNatZAeC8WTgH6flPNz0/d3q1jtOP16++T2eHTonZPTTT3ni9r2x92GgPT/cD35li2S9e93740nl7zaD9Y/J0dv5qXe3Oqw3Dw/QmX+HmdgkOaiSc1QqLlPT9B9N0Yhp5pAnKbIhZPioRIaHLUq0SCiGELM9PubiVLHIm4iqOna7FgGoRCkVqCTn5jg1B9Ru6ah9mr8xZpQmmOuTMbxJzs44pBBF/9yTqcfIdCnRuMtlVWhhzi4loDnLsH25s5fASr01pAlnOhG5AdktCigXWcbyqFUZ2vbN83wZToPhTU0QzBeh/eXzPXRLKI3+UCGXqI3g+Zr5
*/