
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/lambda_fwd.hpp>
#   include <boost/mpl/bind_fwd.hpp>
#   include <boost/mpl/protect.hpp>
#   include <boost/mpl/quote.hpp>
#   include <boost/mpl/arg.hpp>
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/int_fwd.hpp>
#   include <boost/mpl/aux_/template_arity.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/config/ttp.hpp>
#   if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
#       include <boost/mpl/if.hpp>
#   endif
#endif

#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER full_lambda.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/default_params.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/config/dmc_ambiguous_ctps.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header
#   define AUX778076_LAMBDA_PARAMS(i_, param) \
    BOOST_MPL_PP_PARAMS(i_, param) \
    /**/

#   define AUX778076_BIND_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY \
        , param \
        ) \
    /**/

#   define AUX778076_BIND_N_PARAMS(i_, param) \
    BOOST_PP_COMMA_IF(i_) \
    BOOST_MPL_PP_PARAMS(i_, param) \
    /**/

#   define AUX778076_ARITY_PARAM(param) \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(param) \
    /**/


#define n_ BOOST_MPL_LIMIT_METAFUNCTION_ARITY
namespace aux {

template<
      BOOST_MPL_PP_DEFAULT_PARAMS(n_,bool C,false)
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< BOOST_MPL_PP_ENUM(n_,false) >
    : false_
{
};

} // namespace aux
#undef n_

template<
      typename T
    , typename Tag
    AUX778076_ARITY_PARAM(typename Arity)
    >
struct lambda
{
    typedef false_ is_le;
    typedef T result_;
    typedef T type;
};

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};


template< int N, typename Tag >
struct lambda< arg<N>,Tag AUX778076_ARITY_PARAM(int_<-1>) >
{
    typedef true_ is_le;
    typedef mpl::arg<N> result_; // qualified for the sake of MIPSpro 7.41
    typedef mpl::protect<result_> type; 
};


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/aux_/full_lambda.hpp>))
#include BOOST_PP_ITERATE()

/// special case for 'protect'
template< typename T, typename Tag >
struct lambda< mpl::protect<T>,Tag AUX778076_ARITY_PARAM(int_<1>) >
{
    typedef false_ is_le;
    typedef mpl::protect<T> result_;
    typedef result_ type;
};

/// specializations for the main 'bind' form
template<
      typename F, AUX778076_BIND_PARAMS(typename T)
    , typename Tag
    >
struct lambda<
          bind<F,AUX778076_BIND_PARAMS(T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)>)
        >
{
    typedef false_ is_le;
    typedef bind<F, AUX778076_BIND_PARAMS(T)> result_;
    typedef result_ type;
};


#if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)

template<
      typename F
    , typename Tag1
    , typename Tag2
    , typename Arity
    >
struct lambda<
          lambda<F,Tag1,Arity>
        , Tag2
        , int_<3>
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;

    typedef typename l1::is_le is_le;
    typedef bind1< quote1<aux::template_arity>, typename l1::result_ > arity_;
    typedef lambda< typename if_<is_le,arity_,Arity>::type,Tag2 > l3;
    
    typedef aux::le_result3<is_le, Tag2, mpl::lambda, l1, l2, l3> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

#elif !defined(BOOST_MPL_CFG_DMC_AMBIGUOUS_CTPS)

/// workaround for MWCW 8.3+/EDG < 303, leads to ambiguity on Digital Mars
template<
      typename F, typename Tag1, typename Tag2
    >
struct lambda<
          lambda< F,Tag1 >
        , Tag2
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;
    
    typedef typename l1::is_le is_le;
    typedef aux::le_result2<is_le, Tag2, mpl::lambda, l1, l2> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

#endif

#   undef AUX778076_ARITY_PARAM
#   undef AUX778076_BIND_N_PARAMS
#   undef AUX778076_BIND_PARAMS
#   undef AUX778076_LAMBDA_PARAMS

#if !defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
BOOST_MPL_AUX_NA_SPEC(2, lambda)
#else
BOOST_MPL_AUX_NA_SPEC2(2, 3, lambda)
#endif

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_FULL_LAMBDA_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1
#define i_ BOOST_PP_FRAME_ITERATION(1)

#if i_ > 0

namespace aux {

#   define AUX778076_RESULT(unused, i_, T) \
    BOOST_PP_COMMA_IF(i_) \
    typename BOOST_PP_CAT(T, BOOST_PP_INC(i_))::result_ \
    /**/

#   define AUX778076_TYPE(unused, i_, T) \
    BOOST_PP_COMMA_IF(i_) \
    typename BOOST_PP_CAT(T, BOOST_PP_INC(i_))::type \
    /**/

template<
      typename IsLE, typename Tag
    , template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename L)
    >
struct BOOST_PP_CAT(le_result,i_)
{
    typedef F<
          BOOST_MPL_PP_REPEAT(i_, AUX778076_TYPE, L)
        > result_;
    
    typedef result_ type;
};

template<
      typename Tag
    , template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename L)
    >
struct BOOST_PP_CAT(le_result,i_)< true_,Tag,F,AUX778076_LAMBDA_PARAMS(i_, L) >
{
    typedef BOOST_PP_CAT(bind,i_)<
          BOOST_PP_CAT(quote,i_)<F,Tag>
        , BOOST_MPL_PP_REPEAT(i_, AUX778076_RESULT, L)
        > result_;

    typedef mpl::protect<result_> type;
};

#   undef AUX778076_TYPE
#   undef AUX778076_RESULT

} // namespace aux


#   define AUX778076_LAMBDA_TYPEDEF(unused, i_, T) \
    typedef lambda< BOOST_PP_CAT(T, BOOST_PP_INC(i_)), Tag > \
        BOOST_PP_CAT(l,BOOST_PP_INC(i_)); \
/**/

#   define AUX778076_IS_LE_TYPEDEF(unused, i_, unused2) \
    typedef typename BOOST_PP_CAT(l,BOOST_PP_INC(i_))::is_le \
        BOOST_PP_CAT(is_le,BOOST_PP_INC(i_)); \
/**/

#   define AUX778076_IS_LAMBDA_EXPR(unused, i_, unused2) \
    BOOST_PP_COMMA_IF(i_) \
    BOOST_PP_CAT(is_le,BOOST_PP_INC(i_))::value \
/**/

template<
      template< AUX778076_LAMBDA_PARAMS(i_, typename P) > class F
    , AUX778076_LAMBDA_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda< 
          F<AUX778076_LAMBDA_PARAMS(i_, T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<i_>)
        >
{
    BOOST_MPL_PP_REPEAT(i_, AUX778076_LAMBDA_TYPEDEF, T)
    BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LE_TYPEDEF, unused)

    typedef typename aux::lambda_or<
          BOOST_MPL_PP_REPEAT(i_, AUX778076_IS_LAMBDA_EXPR, unused)
        >::type is_le;

    typedef aux::BOOST_PP_CAT(le_result,i_)<
          is_le, Tag, F, AUX778076_LAMBDA_PARAMS(i_, l)
        > le_result_;
    
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};


#   undef AUX778076_IS_LAMBDA_EXPR
#   undef AUX778076_IS_LE_TYPEDEF
#   undef AUX778076_LAMBDA_TYPEDEF

#endif // i_ > 0

template<
      typename F AUX778076_BIND_N_PARAMS(i_, typename T)
    , typename Tag
    >
struct lambda<
          BOOST_PP_CAT(bind,i_)<F AUX778076_BIND_N_PARAMS(i_, T)>
        , Tag
        AUX778076_ARITY_PARAM(int_<BOOST_PP_INC(i_)>)
        >
{
    typedef false_ is_le;
    typedef BOOST_PP_CAT(bind,i_)<
          F
        AUX778076_BIND_N_PARAMS(i_, T)
        > result_;
        
    typedef result_ type;
};

#undef i_
#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* full_lambda.hpp
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
*/