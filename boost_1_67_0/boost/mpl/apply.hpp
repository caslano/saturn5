
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_APPLY_HPP_INCLUDED
#define BOOST_MPL_APPLY_HPP_INCLUDED

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
#   include <boost/mpl/apply_fwd.hpp>
#   include <boost/mpl/apply_wrap.hpp>
#   include <boost/mpl/placeholders.hpp>
#   include <boost/mpl/lambda.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER apply.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/config/lambda.hpp>
#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_APPLY_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define AUX778076_APPLY_DEF_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        , value \
        ) \
    /**/

#   define AUX778076_APPLY_N_PARAMS(n, param) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_N_COMMA_PARAMS(n, param) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS(n, param, def) \
    BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
    /**/
    
#   define AUX778076_APPLY_N_SPEC_PARAMS(n, param) \
    BOOST_MPL_PP_ENUM(BOOST_PP_INC(n), param) \
    /**/


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/apply.hpp>))
#include BOOST_PP_ITERATE()

#   if !defined(BOOST_MPL_CFG_NO_APPLY_TEMPLATE)
// real C++ version is already taken care of
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// apply_count_args
#define AUX778076_COUNT_ARGS_PREFIX apply
#define AUX778076_COUNT_ARGS_DEFAULT na
#define AUX778076_COUNT_ARGS_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#include <boost/mpl/aux_/count_args.hpp>
}


template<
      typename F, AUX778076_APPLY_DEF_PARAMS(typename T, na)
    >
struct apply
    : aux::apply_chooser< 
          aux::apply_count_args< AUX778076_APPLY_PARAMS(T) >::value
        >::template result_< F, AUX778076_APPLY_PARAMS(T) >::type
{
};

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // BOOST_MPL_CFG_NO_APPLY_TEMPLATE

#   undef AUX778076_APPLY_N_SPEC_PARAMS
#   undef AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS
#   undef AUX778076_APPLY_N_COMMA_PARAMS
#   undef AUX778076_APPLY_N_PARAMS
#   undef AUX778076_APPLY_DEF_PARAMS
#   undef AUX778076_APPLY_PARAMS

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_APPLY_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(apply,i_)
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    : BOOST_PP_CAT(apply_wrap,i_)< 
          typename lambda<F>::type
        AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
        >
{
#else
{
    typedef typename BOOST_PP_CAT(apply_wrap,i_)< 
          typename lambda<F>::type
        AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
        >::type type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          BOOST_PP_INC(i_)
        , BOOST_PP_CAT(apply,i_)
        , (F AUX778076_APPLY_N_COMMA_PARAMS(i_,T))
        )
};


#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
/// workaround for ETI bug
template<>
struct BOOST_PP_CAT(apply,i_)<AUX778076_APPLY_N_SPEC_PARAMS(i_, int)>
{
    typedef int type;
};
#endif

#   if !defined(BOOST_MPL_CFG_NO_APPLY_TEMPLATE)
#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == BOOST_MPL_LIMIT_METAFUNCTION_ARITY
/// primary template (not a specialization!)
template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct apply
    : BOOST_PP_CAT(apply,i_)< F AUX778076_APPLY_N_COMMA_PARAMS(i_, T) >
{
};
#else
template<
      typename F AUX778076_APPLY_N_COMMA_PARAMS(i_, typename T)
    >
struct apply< F AUX778076_APPLY_N_PARTIAL_SPEC_PARAMS(i_, T, na) >
    : BOOST_PP_CAT(apply,i_)< F AUX778076_APPLY_N_COMMA_PARAMS(i_, T) >
{
};
#endif

#   else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if !defined(BOOST_MPL_CFG_NO_APPLY_TEMPLATE)
namespace aux {

template<>
struct apply_chooser<i_>
{
    template<
          typename F, AUX778076_APPLY_PARAMS(typename T)
        >
    struct result_
    {
        typedef BOOST_PP_CAT(apply,i_)<
              F AUX778076_APPLY_N_COMMA_PARAMS(i_, T)
            > type;
    };
};

} // namespace aux
#endif

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#   endif // BOOST_MPL_CFG_NO_APPLY_TEMPLATE

#   undef i_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* apply.hpp
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
*/