
#ifndef BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED

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
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER iter_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) iter
#   define AUX778076_FOLD_IMPL_NAME_PREFIX iter_fold
#   include <boost/mpl/aux_/fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED

/* iter_fold_impl.hpp
P/RufqCf9lHZXMmVqil0pKKCbq8/PZrOEZlnG8FDuZr5MISpYoeKx3plCGz2PAFi4ZCiWMKIa8PcrY1+uzbW5Zb/Qe1N+rh24f+leH71/pPPuZFbvSuTppiW1zEnnPQHJSOZVXT6W6TpVOuEgJnxOklqSs+PiHYndqpCDbA2JXL10bQp/q/9VO1o0OduuUcrwyEbLU0oOHm6/zpH16j1sa7eObp9tNcCY4F67lSPgmAlv95eQlsQksDlAdrtDEVJuVS/4HayK46O70gdqBaJsxK4f74gdLTGeS74OAnDUGq687U4ziK6w/NU9yRa4+mfXuHNKcR6FLkKmdKuerNYCxauMW6IdbE/WPXOzEGDG1cuuPtefF5Jxj1K7966VlLeBAAZp2+ok+zuMYMk2Rt0HYhsTQRVioApwLWD+ThAumTOoKWOV79fNfxX8SM1zv/hT1ZYQpBymfM5g5BtbXRE909rSj5RrYrPuTgqlEZ6BR1XGhqEwKwxPN4YRxgpHTRwpB6+BV1vvnOh3NRHZFXP2Rj7z9k9d7NCVWSRzcU/+miO/qDy48LpxcOkbQ==
*/