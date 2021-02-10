
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
VpqJ/akDoaym0qxQL7oCU2W48BpKsuz0C4QAiev9yXDF0P46H6ZoodTKqkyJgERhEraujliL/O9AtdDLZdZ3/67Cdy935Q9QSwMECgAAAAgALWdKUlS5+uwGAQAAlgEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4OTRVVAUAAbZIJGBNkV9LwzAUxd/zKS4bfZQI80FLKELRWhBbsurriMktLbZNuYmb+/amf+Z8yj3kd05OEuHRea0cJky0Q23D8oXnkyXjElYW5Y6lHSqCCn88k0+VZIJfAcEXD9uyLeyRjkg3rjXIBOHYnSdgHWYi7Voc/EroWQTEzb6EjXbcBcNFghhUj0sJOLW+gVRCO8B3AKadAPCFAKFt36vBLBkx5xMT3ZpnmWdZ/pYddG9ih5rQP0Yvxb7KyziacstCVvz+4S4c+xcRxrXZ3PkDqa3PYJRXoGqPBL5BmF4NGuXgE3GAjWus3zBxnNkkuHrV1ZZ6NPAuX5lAIkvamlB2uuI/KfjFJPj1K34BUEsDBAoAAAAIAC1nSlKuSyTXkwEAAHkCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODk1VVQFAAG2SCRgdVJta9swEP4uyH84XIphYNRsK2ye
*/