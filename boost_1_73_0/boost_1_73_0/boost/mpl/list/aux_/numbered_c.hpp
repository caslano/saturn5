
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

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

#if defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i BOOST_PP_FRAME_ITERATION(1)

#if i == 1

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i, T C)
    >
struct list1_c
    : l_item<
          long_<1>
        , integral_c<T,C0>
        , l_end
        >
{
    typedef list1_c type;
    typedef T value_type;
};

#else

#   define MPL_AUX_LIST_C_TAIL(list, i, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(list,BOOST_PP_DEC(i)),_c)<T, \
      BOOST_PP_ENUM_SHIFTED_PARAMS(i, C) \
    > \
    /**/
    
template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(list,i),_c)
    : l_item<
          long_<i>
        , integral_c<T,C0>
        , MPL_AUX_LIST_C_TAIL(list,i,C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(list,i),_c) type;
    typedef T value_type;
};

#   undef MPL_AUX_LIST_C_TAIL

#endif // i == 1

#undef i

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
6s8vFnhBtLMgfgw83FgQbX57/KZWlnk5g/Vju4ktLvAaXtiXnPb1ab4BUEsDBAoAAAAIAC1nSlKEhhQVXwEAAEADAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NzE2VVQFAAG2SCRg5VPLbsIwELz7K1ZFnCqIWokiIitqxYWqB1CDeq2MvSEWiR3Z5pG/78YJj39ocki8Ozs79qx5QB+k8Jgxrk1h6XPA9myd8hlbbbcblq+XX/mMiar6bZy9tIwndwRP+qIRG0GO7oRu4rVCxh02VUtxqDGUVsEraA89FQh/0GYPhXVw9OieG+F9x8e4jxSyVhm71lGLhyhPBuLYcVlpNGHoKOMiu5JkzFt58LNbPWUKFOHokHSXITTsup17mBtR00kMOmMezjqUEKyFypLoTjB0KKrrwaRDB/ClPVYKDFInkNYYlIGqIJQIQbg9EiTKYMClrWthVK8iTZLSdu8UL6JuKpxSOl0skvnLG0wu0O+CUB///El37+PVOt9+btJxNGiz/t6SC7fTpN9hBOJw/KDTRQtKBAGiCGRL9ILGHUrhYYdo4IlsC0+MnyKWKNA566RV5OtiTowPa57cUMn90vwBUEsDBAoAAAAIAC1nSlIj4NJFRAIAAL8DAAAeAAkA
*/