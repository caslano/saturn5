
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