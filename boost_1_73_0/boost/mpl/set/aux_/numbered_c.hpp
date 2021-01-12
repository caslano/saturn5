
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
mJ9nj6PZVYEytQGsr/8Sv5w6Anosy6+fdlv4WaXmzixffYTKQAUeurUmIq0RZsPZXiPHPXlZQ2is1UjAIe7mmn9ZuuICvKGxzGV2+aaWvBBp+5N4NJapYWKbTk73h5Gg/1q2whqnrbpOPtfk53N1uK3ZXJZNFgXlRZswBg/bvWaeoJuGFth/uZ+n2UeXU0u34rzsZ6T2lLwn05UWj4ma7jCDusLw9vPPa4PYzLHZL+MpDdbY
*/