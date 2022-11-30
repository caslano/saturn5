
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED
#define BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/aux_/template_arity_fwd.hpp>
#   include <boost/mpl/int.hpp>
#   if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
#       include <boost/mpl/aux_/type_wrapper.hpp>
#   endif
#   else
#       include <boost/mpl/aux_/has_rebind.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER template_arity.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/range.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/seq/fold_left.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define AUX778076_ARITY BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)

namespace boost { namespace mpl { namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(int, N) > struct arity_tag
{
    typedef char (&type)[N + 1];
};

#   define AUX778076_MAX_ARITY_OP(unused, state, i_) \
    ( BOOST_PP_CAT(C,i_) > 0 ? BOOST_PP_CAT(C,i_) : state ) \
/**/

template<
      BOOST_MPL_PP_PARAMS(AUX778076_ARITY, BOOST_MPL_AUX_NTTP_DECL(int, C))
    >
struct max_arity
{
    BOOST_STATIC_CONSTANT(int, value = 
          BOOST_PP_SEQ_FOLD_LEFT(
              AUX778076_MAX_ARITY_OP
            , -1
            , BOOST_MPL_PP_RANGE(1, AUX778076_ARITY)
            )
        );
};

#   undef AUX778076_MAX_ARITY_OP

arity_tag<0>::type arity_helper(...);

#   define BOOST_PP_ITERATION_LIMITS (1, AUX778076_ARITY)
#   define BOOST_PP_FILENAME_1 <boost/mpl/aux_/template_arity.hpp>
#   include BOOST_PP_ITERATE()

template< typename F, BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct template_arity_impl
{
    BOOST_STATIC_CONSTANT(int, value = 
          sizeof(::boost::mpl::aux::arity_helper(type_wrapper<F>(),arity_tag<N>())) - 1
        );
};

#   define AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION(unused, i_, F) \
    BOOST_PP_COMMA_IF(i_) template_arity_impl<F,BOOST_PP_INC(i_)>::value \
/**/

template< typename F >
struct template_arity
{
    BOOST_STATIC_CONSTANT(int, value = (
          max_arity< BOOST_MPL_PP_REPEAT(
              AUX778076_ARITY
            , AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION
            , F
            ) >::value
        ));
        
    typedef mpl::int_<value> type;
};

#   undef AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION

#   undef AUX778076_ARITY

}}}

#   endif // BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING
#   else // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_<-1>
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
template<>
struct template_arity<int>
    : mpl::int_<-1>
{
};
#endif

}}}

#   endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      template< BOOST_MPL_PP_PARAMS(i_, typename P) > class F
    , BOOST_MPL_PP_PARAMS(i_, typename T)
    >
typename arity_tag<i_>::type
arity_helper(type_wrapper< F<BOOST_MPL_PP_PARAMS(i_, T)> >, arity_tag<i_>);

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* template_arity.hpp
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
*/