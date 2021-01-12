
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
fvDwN0YlZVkiYVwhf0eWj0bz3m0GMXxhzyB52Jnl8V7EUrWP7Yq4+phTObuznKmpsaqfTAznZhkO0kKPgXcSULR99pBDfWDdmxG/OfHoYE/6xl7iqWZr1DduYbFc38BvizMDFr8VcVkEu7wZfF+E0/eB4Lcm7t/Eeh2ZcL7ymC3hW+ckxIEuYO0x1u99xdwp1fdlWTwS1FoEL2ZxFI9nP8RLEe7W7oxE4ii34Ng02gTnQMTw
*/