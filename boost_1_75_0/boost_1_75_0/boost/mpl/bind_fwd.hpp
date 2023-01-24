
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_BIND_FWD_HPP_INCLUDED
#define BOOST_MPL_BIND_FWD_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/aux_/na.hpp>
#endif

#include <boost/mpl/aux_/config/bind.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER bind_fwd.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/config/dmc_ambiguous_ctps.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header

#   if defined(BOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)
#       define AUX778076_DMC_PARAM() , int dummy_ = 0
#   else
#       define AUX778076_DMC_PARAM()
#   endif

#   define AUX778076_BIND_DEFAULT_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    AUX778076_DMC_PARAM() \
    /**/

#   define AUX778076_BIND_N_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) BOOST_MPL_PP_PARAMS(n, param) \
    AUX778076_DMC_PARAM() \
    /**/

#if !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE)
template<
      typename F, AUX778076_BIND_DEFAULT_PARAMS(typename T, na)
    >
struct bind;
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/bind_fwd.hpp>))
#include BOOST_PP_ITERATE()

#   undef AUX778076_BIND_N_PARAMS
#   undef AUX778076_BIND_DEFAULT_PARAMS
#   undef AUX778076_DMC_PARAM
}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_BIND_FWD_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(bind,i_);

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* bind_fwd.hpp
COZAakgG0tvSHNuwp/20lsQgYKzwEnl6SypopH/NZuJSybHzaXmsoqVTEu65/PHdvLrUBJ2Gy4vbqsdTZPJPeUeNxhUF2edZ69d+s5R7eu5/BAXK10BIgDLp3WOnLv+lcJaXoZTemtEfjN/dUN9OGtlql/cVlwmUNbCW96dR1uL74vyFMldvxTj2zwKP7rLVaLouy6C+Yt4DvmJquAZg7ALxT5dXzRQLTtJHAiFuKnWT4F4q+21xR9N9fuERM8Z3VX89ngxRdo9t0Ic8dBsBfUao6SDn279CDj8eETzS2jufXzxA9QpNXBWRG7Zh6yqJ+pU6w+skZ/I6RybJyY6qSIcj+dFEGBUF5UVJ1LlIdIdIo0gjnmkz9evdg8ZahLwUhS9G8yRD8s/t3pcLhXzOPE7WVPpYRgn7/E0rax6OtRgvYYLsiwGU+vfJIsg7bgFLn7ZaiM+7dQLXQmh7785F70/jzHm1xS94Rj3ze3olAcJdr9tXQTDyhix2y+nW1udljk3fK211KqIqLUn5r+ua1yJ5slXiYJD+s1ujg5yYoYaQYjpIF4T4kAyhhxBAyDWgcEkS8gJxu35Pl3/5QTT1GiSLUiVaK6SbCYGoHbwCqYqzf9Nyo3dtpPdkH1jMvrq9MlpMzclDDcbusEt3Uybn5IF7T+sXZjW8Z3/dGF8aj9kkHzt+iKamdZko/sth9VX/u/Xe4wHw8pSxrPWu
*/