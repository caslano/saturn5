
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
kpG2aYynPKvk9JJ0W8mhRXm2kqPmTeDJBo+nuWbRwn/jvioz4DZm0d7iWlZgfpYfN5DtPFEswuf6/m+EwmgByqnz1AsZiaDOC+QyaC2b8HG2cQ0u7IHZOVH2OLQMdy7wZxTKI1Ke2wIkXcXYIIcpQ/w+/zT9cu/bWl9JB2T2JuT4R+WkzxELewm2QYYksFItjsi1n0ZsNP0pVIyyiR0CfJaeletPyE2F0lJGviX59DM/+OSouglOSTsJBUZAeUhhPxzQeuR/xGNjOjpDuKhSGxhbl0QD6e6remP92ceqXnzZgTB0Y4XfUdRkCi0aehmopE4ijEJTOsvZBfXBmeV6D3YsVxuw5MxyuR/GU6osML3kJFXgIkqVBa4tyVAFBgdTQE7pdoZgE7UPl7eZ/DziP+BXSVzefKewXjDXrlTeCHoZIoXU6ZIhA/cY83+Pn46qmnjDPln837fs9wdk3y72BzYSPEqB5uKYPPxxHoQ/ziSz6v6ayArxI1ZDo7yTSCWPO/TehFvh+Npbgvbg3tZxJyUFT9iSiC/0Z8y4va9v+UG4/nT8hcHhuYO6ll3VfsjEQOv+OWXjhSfYmxz5cuMmMzmNx9A0rCHPdRgTD1B8un3vo/gKxwZMgD4ZJRdR1QCNX5R59QCXcaOM+FQB6Je7qRPJdX+mRkXEPSSWJMVDWXzZz35OZ4nTGPCgwor3derrAlSO+9PYd0DpizoDDo6rbpaaKE8t0xmINzxuMWUg+tafdMZ16FvMQ/Jn31KORi8r7ySGzvhnHBEmWmP3Ydn+XU+rxFMMxyOy7TJdcqBR9Rfp3uAqPA9YQdYxX1b/HY8CEnyvWfmt5EyTpX4nxwas9l04I1sSAWYM1C0Gap58p8xwy4y2u8w7oj/r/b8jVj/ESP04w0fmRoIRvBUvKF8FeQky0kWyy+z9Z9BhzKF48804ORTUXyRlxj6xhRewYz9VKdb+n8ZjDAhJoq+GXQVVkIyXmEMd6dwSsl5S1dfHmJojZPdPFNrRNVLtf+Kbdh43u92j+hCmUAtQaUALtLx4Fl75I8UYMAaplkAEfvwMz5Su9GHG8ZwFfctfmPdiXD6zH83FOFHXgnr1M9+FjYG+bwe/Af4Mbq+xXjpgkcKecFTDgwkEZpo+HgyBIyuBDqhXH9A1bynGsVDsi6QUMc1KiqFsGapMOjKMAapBNlqdCX9E3Oa7xDqEYKqWRK6DtzpUdLpOydcvQbjoWnLHNKs0Db4EAIHV/ZXeV6jchcc4MVwA0c93KhuD0JWUA3Ss8t618gqQV89WrE/00a2NpXRjrBqqoA7MJ3m1FS9hlHEKZ1te1Y95GiXADK0rm+CH74VVao0Xfg1nm+GexqkapuPF/JHuk/yE0CsgV3yCjusP5mk6ic/J0w74p+kyZX8kcijCKeFMq5SzUalvZSlE6tmuhvJ1A4YSOpd9ywvbGY8Mc2dSGQDjbVlmmBjsT6Ig8ciuKEj0ZZtMuG3noH2eA7KRJQ1qzhdEzXlrg33O4HEDaj7yp6Hi8A04ILf5GdwIwkIrWaXZLlGv1c0OPYtJmVKA6nMWCQ8ICSX9jat0z1dRz1PQGHujeHCzUiuboepnhE8LOKVnd1o+7usTsLQRBmyAKuijOV2nW76aWq7/yj4ndDBxs5aHsB+k1wid19D/kQVpvr7Xpfmup/+fpN+P0b8+2thD6H8n5W2i32/R/0fR998v+N/yiST5JcbPPpHadmd8ifWXRjzXGqe1A9ilxQ7xWx95gnXJT1cZyjZ/icyYxBmWX6FrZMaPo5pKzTMvkBmTVQZGMOmJ+Ex9WpH/EvPGOEE1HBhuFr4RdX+kGcPbWYfkYnPFFxIxhk9BAAifZNc=
*/