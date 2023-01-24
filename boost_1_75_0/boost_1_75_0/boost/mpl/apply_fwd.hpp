
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
a6KpTGF9oLvLH8UWF84lkVtlGYuCOR+b85Q4dPRa8bfHmjr+kcMnMXFUzOy6aXrmyxxqulG6WdoWJl7gd4RhGoHVo+w+g9L9WYYZ8xzZy++9TatN2qs5UrdS3cxlGE5gkT7Nz+JoWTmdDc8Wj7+ATp11lybq9cuqZ9cwQWEFUPYPolRT874BVmbT5Xs4ezEjCxP8YL9GKTF5FRyRvEX2RDXYi4b7fr4JO+EqH+JY/Dp4WSi6o20X2qUf2TEHUq4Q7nqM6MCEaVRA+9QjO/BNVE/Yp1VPxKblTyg4JU/YkzMBvZY9SicUV3hMz5fJHepBSfN5O9CSC0IWspOL2pvu0nRACEzfRl28AihIEesjj7YT1ePC+fxn/OmTWT0NgTrqTzkQ9TJ5LIlYkzgZ+V41jfQrl0Wz3312sOTg1GNCxzcO0sl3u2VUdapeJrFJl6w4ER1WM/53Lj+u5KxfNYExhaeGiJ4wizbHuV1Z93AwU2X3OZKq9zLCXWE5v/l1n3wYu2d3qd+PTPgp0Tr6NXGXzrY6KTFYvOvcPERFhGM9MKQGZFw4BzMfCLe6IWVTuzXdUxcHdIqFOO+sDPM3WuMPDaR15p0PMezi7+bTPB4/cYB5LWE7DwOZQxPObfRiAEBnwOr3EBpn2EnT1IzP2UEvVYyZWyIYNvrUe9m8XJpSx/qht/rwIqlFTHzm5TX6oRi4AnhwAP+FMiTLrEy1
*/