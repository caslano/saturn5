
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
xBq5gGfYD4gwUpiK5BVumBNy3mKFG+rKvmimhdGmuXIYtR5ue/0pYFyABm3HQNKgXf2udOhoAlr35yCuNPFcMEQFU6hg5+SCpaZgOrCJcAMKGzg2aWgZX3UAZ/xdlZEFkNns9cgdghvcDm7Er3FVdA2hf/VEzBFAAW/ahrK4lTayAM9E1QWgKiqqp3JUC553o9IwvdYdDV8um2bpzuElNbPJc2snZawaF2jGhI8VYGYX2HSP85yh1ujkFv30HbTIOkk/cZQ+u9vvgXldD0IYA9sGhjtiBcvAFsKxknsJSVpVfTOgKa9kW1bFfAz/bRV2YDid/ylBf9YTYtSlaPzO2UOtwmRMsg0mk/UTu//Zy14TTH6QzkBr+hOYgpp4SIHWAKh3DFrnanmMn3ruDXt6fatDa6g1LZA045e+LbhM9+GSZnBpD1wAHF29rEgAY5ZHKrAlJAhSSl4Bj1V9ixVsqCy8t2I41zszmQYRU+/FvnqXvir1fi8N9eIC7nsxTJYTsKrIAvTGslSmzbK6y2gqWJf7uvM0AWBd7YLdWJV2K9OryM7/yIzSrRXlW5kDXptMj7m1Mu4zGYPCjZUlW7ekLTGxUcmndh/ccPYFinEtYYyYq8hYUI3FqLoFzjK8oFqi29obXzA7qLUcs7y2YhhPohhiqtZCJq2NPxmvpMYQGsRThhfW0rRdkkzWZ94S9CfrzV7fFsCxggcqyh9goMenthS0GCvX5uGFxNO7EFQM8MjswWhRNve9uyA38bSMLKtM60juwVCU5BqWPwYJ4jcqC1cWP4W8z4nLxG5qcWUkMMVe6MnLd7ID9i4amYGsm+6UZb/lWioLHxCNcPZmrPyAcDl4WXWgTTQeU1nIroEPTDE9RAOK8k66sanYVMTsproy7RYRrV5+3g1TkM6t+knd72ioiba6lfJsFHxuaHDxeSMg4iFGyoYKm7BZxaNkFWESo3/LV6VkLb0SkcbXppQdIbBCrrZ7O+oUWLcEWu6iprxCYjp9A771YVXWTVma0oiGrMp6Nq1TrGBdRfk6WiX2EBR+KqcV9DJafUCxjvKMcV3FT7Eqi/6teIb/5WsNStZ9+odYybrKRZyQV3Bn6QTg3QOEVIvMQuES0n5Uc2dKGVUzw60Gz1INP8UK72Q4pYOogu2fm95IW0BoA6p9/gZ3jFSKwA0qDBIbwLrtn3lGxhJQz8Em8pz2Gm2m1r1AHVZXTv+gvmyHzi+JLwByDYjnMsql3QBdczwiLAQ5OorILr26tMi+G/il8Yi073saz5atsxDe6i9XCwOq01TEaV2LVBG/TkU46RUsrK+oeI6k1xWVBSsqhhEa1ocuL1vBtwWUS7H4q1a9foFX/kwFtzWllM72bCX2wOBqAa5W+EcpAallILueMtqr9YkCQZznXINpo6YiimxHSa1Eu7+K5vb/3/9///+1ZH+4AfY/kphhR/CYGjb6LAeLnTNLfxLFFmtT/INmNySBmIHOTTdrfXajWeuXVZQvY/mmV9BVxDeIgHDn70VA+FEaIsGzmn/WGlbzSbLYqJdepNfNpc9wK91UD5iAf8iLeJbA3pzrLMqF+NF/fdQNHTLYqfQqrfQoU2lfQN1GRxNeRX7YPmsz5KbFNBwFb4JeSMrcKiiFF1BKbqqkrIFGeCqlDAhIylqog8eRvQvq4DpVB5ugDm5QdXCDqB8beEErWBcrWFtZuDZWuKayZE2sZFVlwaq8gh1zrvVUvSKp6juTql7pr/pef9UPaNUPiFnggVjhvSzJlqysLFgZK7izsvBOWgJoAYiV7CB2TUu7KjK1OHe0g6SGpyC/vBMrYQNM1qNQB6xJSlzWfdQ+cImok+7dS5OdLsjXLrg=
*/