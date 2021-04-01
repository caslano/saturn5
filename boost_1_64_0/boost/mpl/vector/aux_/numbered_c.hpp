
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

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   define AUX778076_VECTOR_TAIL(vector, i_, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c)<T \
          BOOST_PP_COMMA_IF(i_) BOOST_PP_ENUM_PARAMS(i_, C) \
        > \
    /**/

#if i_ > 0
template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c)
    : v_item<
          integral_c<T,BOOST_PP_CAT(C,BOOST_PP_DEC(i_))>
        , AUX778076_VECTOR_TAIL(vector,BOOST_PP_DEC(i_),C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c) type;
    typedef T value_type;
};
#endif

#   undef AUX778076_VECTOR_TAIL

#else // "brute force" implementation

#   define AUX778076_VECTOR_C_PARAM_FUNC(unused, i_, param) \
    BOOST_PP_COMMA_IF(i_) \
    integral_c<T,BOOST_PP_CAT(param,i_)> \
    /**/

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c)
    : BOOST_PP_CAT(vector,i_)< BOOST_PP_REPEAT(i_,AUX778076_VECTOR_C_PARAM_FUNC,C) >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(vector,i_),_c) type;
    typedef T value_type;
};

#   undef AUX778076_VECTOR_C_PARAM_FUNC

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
7Ystx+3ZhIFet4UpprbqtnwHbgkPys89fhyi9DM6oq8IkW2aCoVBET+lZv5hDV7nsP1EJ2aljT7vkykGfXgQpWkSNvVLAymMwqD43k+5ZbjgMVTAVDQ6cnVE6jqTnA+tfEcpI9/aOySEhXU7G3E72c+5+d/70McyBe7fbnkhvY5rm0IsUHZcJWHmP/OvVj3TANY/5gHytiwr4wR+huTGAqN9MsQfNa2lufHRtqNmfufV8SXXe68lj5yKneph6C5WyvzD1+0js+GJD6j2Lnmyhzy0WuzgDqG7DB7aF6sS3ns8yCYkX9gmtU6HsFiaBoATYfk7JEqkTLpEPt859SHd4pGNbZ9MM8saSCr+RzR09XyEUSqLfwOE6XfJVKhNDTokVpvPy5Y7H4BkAjrS69+BzUyfBDC3ZgoAhG5DST3av/4iqATkChfugOhr9kmM6p5KvHNuOAgEqBtDL3ssAbq5qIRAmlwykhz9++znpxbhIR8bKyWEq7d2DdhLNuVY3u8dzYdomLX+Hnb0VysQHi6ytanQWIl/PRkdYnAQPUWPLGFKk+yUrff9mi5yBg==
*/