
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_APPLY_FWD_HPP_INCLUDED
#define BOOST_MPL_APPLY_FWD_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER apply_fwd.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

// agurt, 15/jan/02: top-level 'apply' template gives an ICE on MSVC
// (for known reasons)
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   define BOOST_MPL_CFG_NO_APPLY_TEMPLATE
#endif

namespace boost { namespace mpl {

// local macro, #undef-ined at the end of the header
#   define AUX778076_APPLY_DEF_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_APPLY_N_COMMA_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   if !defined(BOOST_MPL_CFG_NO_APPLY_TEMPLATE)

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// forward declaration
template<
      typename F, AUX778076_APPLY_DEF_PARAMS(typename T, na)
    >
struct apply;
#else
namespace aux {
template< BOOST_AUX_NTTP_DECL(int, arity_) > struct apply_chooser;
}
#endif

#   endif // BOOST_MPL_CFG_NO_APPLY_TEMPLATE

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/apply_fwd.hpp>))
#include BOOST_PP_ITERATE()


#   undef AUX778076_APPLY_N_COMMA_PARAMS
#   undef AUX778076_APPLY_DEF_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_APPLY_FWD_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply,i_);

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* apply_fwd.hpp
PED0oI/BQqz90ZZuSlCa2Fp1BuL7c4D1CZ0gRqsaDE3fM1GtCCiYqsLA6JFqtmO0IuPdA3Q4DQjOExyjcZX4F+/lO7yIQyRjLRyUsXOOaAwhk5dQOKsna/pOx6z0sOGCOCSSi5qo5fI/W8icajC/PgB0hmpQDjAEH/6y3piqHhrQb/+5Zw45kkCmfdMoV44yqZSTzXZfPO/SSc+/274UcvlpyfLXOv69OGTnrxjM4Qx9S6AOhIGlWZ6HB2oV4SeigztOge5EdhpqmaANnrz2Nhe9/Z4fLiOxTMTGR0rhnYtEfOcAZquKldPhZeXkdf2yf95+S8RKa2z5+F7eJyJhhzeFTF5l5W2mfwNQSwMECgAAAAgALWdKUjKsF85XAgAA+gYAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTEwVVQFAAG2SCRgzVVNT9tAEL2v5P8wDeUjUcnaiasKy0RCAUFVIBG4VU9Fiz3GKxyv5V1Sculv72zWISioVVVxIJd4dua9eTP7nMQGtUmFxhGLZZUr+rrHxU/VZHrEzpJkyubY3CqNUKo7zfJS3C9YzNc1MXcwtgXX2FDxvpYZsrjBulxQOhNGBI6KB/0ABr4Pky8eOxYGI0ge8AP4B3Cp5pQJfAjC
*/