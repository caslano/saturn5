
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_UNPACK_ARGS_HPP_INCLUDED
#define BOOST_MPL_UNPACK_ARGS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
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
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/at.hpp>
#   include <boost/mpl/size.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/lambda_spec.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER unpack_args.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/forwarding.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>


namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header

#   define AUX778076_UNPACK(unused, i, Args) \
    , typename at_c<Args,i>::type \
    /**/

#   define AUX778076_UNPACKED_ARGS(n, Args) \
    BOOST_MPL_PP_REPEAT(n, AUX778076_UNPACK, Args) \
    /**/

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< int size, typename F, typename Args >
struct unpack_args_impl;
#else
template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/unpack_args.hpp>))
#include BOOST_PP_ITERATE()

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        : aux::unpack_args_impl< size<Args>::value,F,Args >
#   else
        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >
#   endif
    {
#else // BOOST_MPL_CFG_NO_NESTED_FORWARDING
    {
        typedef typename aux::unpack_args_impl< 
              size<Args>::value
            , F
            , Args
            >::type type;
#endif
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

#   undef AUX778076_UNPACK
#   undef AUX778076_UNPACKED_ARGS

}}

#endif // BOOST_MPL_CFG_USE_PREPROCESSED_HEADERS
#endif // BOOST_MPL_UNPACK_ARGS_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename F, typename Args >
struct unpack_args_impl<i_,F,Args>
    : BOOST_PP_CAT(apply,i_)<
          F
        AUX778076_UNPACKED_ARGS(i_, Args)
        >
{
};

#else

template<> struct unpack_args_impl<i_>
{
    template< typename F, typename Args > struct apply
        : BOOST_PP_CAT(apply,i_)<
              F
            AUX778076_UNPACKED_ARGS(i_, Args)
            >
    {
    };
};

#endif

#   undef i_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* unpack_args.hpp
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
*/