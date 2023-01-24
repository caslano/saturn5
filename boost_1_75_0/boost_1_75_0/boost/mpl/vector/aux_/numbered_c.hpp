
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
TJj8tQSkN3lj5RRPVHcFd1QQgySe4kxNAjWHUyQ31WidAu5a/ygkkVXIltxKpxUkO/eZFF/xnxSe+J8U1rwas0GHpToPmzTfJMiiMZkki5Dfub9QFUZL7ybRs7aeLvfUM4H0AgmmPXI1Pt4jP34fvX2IXerh4oGndVx6Vd3HHB3E/oaYWnm1Maa2zRhTq6/8TVvfycrfm0LnK0gvcfm9aGHx4NA8vpaEuKC1Ir6WtPI9tpYU4zLETcFWuJakbNLWkm7S1pL2Pdn5WlK2iuiul5Q+yGDeWeI7LZyX0Gy9i1B33t0MZcMZ1sffi5ijtR6aqYM0sqvLp4UB5JQPq4pNtloLNF+10iTYan9G0/NlT9poENbfwr3UAtI3vSa+8rz8+Ogq28vpYWvk00sbP7UmBkY+HdL4aV7jIXt2i+3lcabGQ9ZsLJwGheBGaUI5hnQemZ9fJvDIHVw2fmYdiMG9Igi2MppqMhsUXslN7wHUoG1qj66ujI03+ee1ke3pO/ZPsbmR256NaB3+wcICFdA+mxzLuJAcQPK9aDNiCxNSWiilWERs4er30NVTyQIPgr/nawJ75F3pFg1E0sIhCl4qJMWK85IDMUaDhvVnJMEFq5LCulkUrtEuBIHGLFZvkSKiH/a2dIEHF9Ra0RisVUKzQSNeGpppiAOZED5aGsvxpnHKctIqZfNW9I0pQZqAT4T7143vqY9NWzP0IudC
*/